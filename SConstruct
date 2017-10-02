# carefree-objects
#
# a thread-safe object manager extension for c++
#
# Copyright (C) 2011-2015 Stefan Zimmermann <zimmermann.code@gmail.com>
#
# carefree-objects is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# carefree-objects is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with carefree-objects.  If not, see <http://www.gnu.org/licenses/>.

import imp
import os
import re
import sys
from subprocess import Popen, PIPE

import jinja2
from jinjatools.scons import JinjaBuilder
from path import Path

sys.path.insert(0, Path('.').realpath().dirname())

import cfo.jinja
import cfo.jinja.macros
from cfo.scons import Environment


env = Environment('carefree-objects')

env.Prepend(
    CPPPATH = [
        'include',
    ],
)
env.Append(
    JINJACONTEXT = cfo.jinja.CONTEXT,

    CPPDEFINES = [
        env['DEBUG'] and 'DEBUG' or 'NDEBUG',
    ],
)


conf = Configure(env)

BOOST_LIBS = []
for lib in [
        'boost_system',
        'boost_thread',
]:
    lib_mt = lib + '-mt'
    if conf.CheckLib(lib_mt):
        BOOST_LIBS.append(lib_mt)
        break
    if not conf.CheckLib(lib):
        raise RuntimeError("Can't find %s or %s library."
                           % (repr(lib_mt), repr(lib)))
    BOOST_LIBS.append(lib)
del lib

env = conf.Finish()
del conf


SOURCE_PATH = Path('src')

INCLUDE_SOURCE_PATH = SOURCE_PATH / 'include'
INCLUDE_PATH = Path('include')

BUILD_PATH = Path('build')

LIB_PATH = Path('lib')


SOURCE_DEPENDS = [SOURCE_PATH / 'context.py']

from src import context
context = {name: getattr(context, name) for name in context.__all__}
env.Append(JINJACONTEXT=context)


INCLUDES = []
for path in INCLUDE_SOURCE_PATH.walkfiles():
    if path.ext in ['.hpp', '.inl']:
        subpath, ext = path.splitext()
        subpath /= ext.strip('.')

        incenv = env.Clone()
        try:
            modinfo = imp.find_module('context', [subpath])
        except ImportError:
            depends = []
        else:
            depends = [subpath / 'context.py']
            context = imp.load_module('context', *modinfo)
            context = {name: getattr(context, name)
                       for name in context.__all__}
            incenv.Append(
                JINJACONTEXT=context,
            )

        loader = jinja2.ChoiceLoader([
            incenv['JINJALOADER'],
            jinja2.FileSystemLoader(subpath),
        ])
        target = INCLUDE_PATH / INCLUDE_SOURCE_PATH.relpathto(path)

        INCLUDES.append(
            incenv.Depends(
                incenv.Jinja(
                    target, source=path,

                    JINJALOADER=loader,
                ),
                SOURCE_DEPENDS + depends))


OBJECTS = []
for path in SOURCE_PATH.walkfiles():
    if not 'python' in path and path.ext == '.cpp':
        OBJECTS.append(env.Requires(
            env.SharedObject(
                env.Jinja(
                    BUILD_PATH / SOURCE_PATH.relpathto(path),
                    source=path,
                )),
            INCLUDES))


if env['SHARED']:
    LIB_CAREFREE_TYPES = env.SharedLibrary(
        LIB_PATH / 'carefree-types',
        source=OBJECTS,

        LIBS=BOOST_LIBS,
    )

if env['STATIC']:
    env.StaticLibrary(
        LIB_PATH / 'carefree-types',
        source=OBJECTS,
    )


if env['TESTS']:
    TEST_OBJECTS = []
    for path in (SOURCE_PATH / 'test').walkfiles():
        if path.ext == '.cpp':
            TEST_OBJECTS.append(env.Requires(
                env.SharedObject(
                    env.Jinja(
                        BUILD_PATH / SOURCE_PATH.relpathto(path),
                        source=path,
                    )),
                INCLUDES))

    if env['SHARED']:
        LIB_CAREFREE_TYPES_TEST = env.SharedLibrary(
            LIB_PATH / 'carefree-types-test',
            source=TEST_OBJECTS,
        )

    if env['STATIC']:
        env.StaticLibrary(
            LIB_PATH / 'carefree-types-test',
            source=TEST_OBJECTS,
        )

    env.Requires(
        env.Program(
            'test', source='test.cpp',

            LIBPATH=[LIB_PATH],
            LIBS=BOOST_LIBS + [
                LIB_CAREFREE_TYPES,
                LIB_CAREFREE_TYPES_TEST,
            ],
        ),
        [LIB_CAREFREE_TYPES,
         LIB_CAREFREE_TYPES_TEST,
        ])


CAREFREE_PYTHON_SOURCE_NAMES = [
    'import',
    'functions',
    'convert',
    'object/iterator',
    'object/check',
]

CAREFREE_PYTHON_SOURCES = [
    env.Jinja(
        'build/python/%s.cpp' % name,
        source = ['src/python/%s.cpp' % name]
    )
    for name in CAREFREE_PYTHON_SOURCE_NAMES]

PYTHON = env['PYTHON']
if PYTHON is True:
    PYTHON = 'python'

for pybin in PYTHON and PYTHON.split(',') or []:
    out = (Popen([pybin, '--version'],
                 stdout=PIPE, stderr=PIPE, universal_newlines=True)
           .communicate())
    out = out[0] or out[1]
    pyversion = out.split()[1].split('.', 2)

    pyversionsuffix = ''.join(pyversion[:2])

    pybuildpath = 'build/python' + pyversionsuffix
    Mkdir(pybuildpath)

    pyenv = env.Clone()
    pyenv.MergeFlags(
        Popen([pybin + '-config', '--includes', '--libs'],
              stdout = PIPE, universal_newlines=True)
        .communicate()[0])
    pyconf = Configure(pyenv)

    BOOST_PYTHON_LIB = 'boost_python'

    suffixes = [
        '-py%s' % pyversionsuffix,
        str(pyversion[0]) + '-mt',
        str(pyversion[0]),
        '']
    for suffix in suffixes:
        if pyconf.CheckLib(BOOST_PYTHON_LIB + suffix):
            BOOST_PYTHON_LIB += suffix
            break
    else:
        raise RuntimeError("Can't find %s library."
                           % ' or '.join(map(repr, suffixes)))

    pyenv = pyconf.Finish()

    pyenv.Append(
        LIBS=BOOST_LIBS + [
            BOOST_PYTHON_LIB,
        ],
    )

    OBJECTS = [
        env.Requires(
            pyenv.SharedObject(
                '%s/%s' % (pybuildpath, name),
                source=['build/python/%s.cpp' % name],
            ),
            [CAREFREE_PYTHON_SOURCES,
             INCLUDES,
            ])
        for name in CAREFREE_PYTHON_SOURCE_NAMES]

    if env['SHARED']:
        pyenv.SharedLibrary(
            'lib/carefree-python-py' + pyversionsuffix,
            source=OBJECTS,
        )
    if env['STATIC']:
        pyenv.StaticLibrary(
            'lib/carefree-python-py' + pyversionsuffix,
            source=OBJECTS,
        )
