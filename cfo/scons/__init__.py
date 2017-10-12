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

"""cfo.scons

Tools for building carefree-objects based C++ projects with SCons.

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = ['Environment']

import os
import sysconfig

import Boost.Cons

import jinja2
from jinjatools.scons import JinjaBuilder

import cfo.jinja
import cfo.jinja.macros

from .vars import Variables


class Environment(Boost.Cons.Environment):
    """
    CareFREE SCons environment.

    Based on pyboost's ``Boost.Cons.Environment``

    Reads common system environment variables for C++ compiler/linker

    Adds a ``Jinja`` template builder with pre-loaded ``cfo.jinja.macros``
    and a ``jinja2.FileSystemLoader`` based on current working directory
    """

    def __init__(self, project, python=True, **options):
        jinja_loader = jinja2.ChoiceLoader([
            cfo.jinja.macros.LOADER,
            jinja2.FileSystemLoader('.'),
        ])
        options.setdefault('BUILDERS', {}).update(
            Jinja=JinjaBuilder(jinja_loader),
        )
        super(Environment, self).__init__(**options)

        # add the common carefree-objects variables
        Variables(project, python).Update(self)

        self['PROJECT'] = project
        self['JINJALOADER'] = jinja_loader

        self.Prepend(
            CPPPATH=[sysconfig.get_path('include')],
        )
        self.Append(
            CPPDEFINES=[self['DEBUG'] and 'DEBUG' or 'NDEBUG'],
            JINJACONTEXT=cfo.jinja.CONTEXT,
        )

        if cfo.TOOLSET == 'gcc':
            # add Linux/GCC style flags from os.environ or custom overrides
            for var in ['CPPFLAGS', 'CXXFLAGS', 'LDFLAGS']:
                flags = self.get(var) or os.environ.get(var)
                if flags:
                    self.MergeFlags(flags)

        elif cfo.TOOLSET == 'msvc':
            # add VC style search paths from os.environ or custom overrides
            # (explicitly setting PATH is often needed to find VC binaries)
            for var in ['PATH', 'INCLUDE', 'LIB']:
                paths = self.get(var) or os.environ.get(var)
                if paths:
                    self.Append(ENV={var: paths})

        # look for custom C++ compiler binary
        cxx = self.get('CXX') or os.environ.get('CXX')
        if cxx:
            self.Replace(CXX=cxx)
