# carefree-objects
#
# a thread-safe object manager extension for c++
#
# Copyright (C) 2011-2013 Stefan Zimmermann <zimmermann.code@googlemail.com>
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

import os
from subprocess import Popen, PIPE

opts = Variables()
opts.Add(BoolVariable(
  'DEBUG', 'build carefree-python with debugging symbols',
  'no'))
opts.Add(BoolVariable(
  'SHARED', 'build a shared carefree-python library',
  'yes'))
opts.Add(BoolVariable(
  'STATIC', 'build a static carefree-python library',
  'no'))
opts.Add(PackageVariable(
  'PYTHON',
  'list of python(-config) binary names to build carefree-python for',
  'python'))

env = Environment(variables = opts)
for varname in 'CPPFLAGS', 'CXXFLAGS', 'LDFLAGS':
  try:
    env.MergeFlags(os.environ[varname])
  except KeyError:
    pass

env.Append(
  CPPDEFINES = [
    env['DEBUG'] and 'DEBUG' or 'NDEBUG',
    ],
  CPPPATH = [
    'include',
    ],
  CXXFLAGS = [
    '-std=c++11',
    '-Wall', '-Wextra', '-Werror', '-pedantic',
    env['DEBUG'] and '-ggdb3' or '-O3',
    ],
  )

PYTHON = env['PYTHON']
if PYTHON is True:
  PYTHON = 'python'
for pybin in PYTHON and PYTHON.split(',') or []:
  pyversion = Popen([pybin, '--version'], stderr = PIPE).communicate(
    )[1].split()[-1].split('.', 2)

  pyversionsuffix = ''.join(pyversion[:2])

  pybuildpath = 'build/python' + pyversionsuffix
  Mkdir(pybuildpath)

  pyenv = env.Clone()
  pyenv.MergeFlags(
    Popen([pybin + '-config', '--includes', '--libs'], stdout = PIPE)
    .communicate()[0])

  pyenv.Append(
    LIBS = [
      'boost_python-py' + pyversionsuffix,
      ],
    )

  OBJECTS = [
    pyenv.SharedObject(
      '%s/%s' % (pybuildpath, name),
      source = ['python/%s.cpp' % name],
      )
    for name in (
      'import',
      'functions',
      )]
  if env['SHARED']:
    pyenv.SharedLibrary(
      'carefree-python-py' + pyversionsuffix,
      source = OBJECTS,
      )
  if env['STATIC']:
    pyenv.StaticLibrary(
      'carefree-python-py' + pyversionsuffix,
      source = OBJECTS,
      )
