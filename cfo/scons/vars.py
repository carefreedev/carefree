# carefree-objects
#
# a thread-safe object manager extension for c++
#
# Copyright (C) 2011-2014 Stefan Zimmermann <zimmermann.code@gmail.com>
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

"""cfo.scons.vars

Provides a wrapper for SCons.Variables.Variables
which auto generates useful options
for building carefree-objects based C++ projects.

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""
__all__ = ['Variables']

from SCons.Variables import *
from SCons.Variables import Variables as SConsVariables

from SCons.Script import ARGUMENTS


class Variables(SConsVariables):
    """Auto generates common Variables for:

    - Overriding os.environ's compiler/linker flags and search paths.
    - Switch DEBUG building.
    - Control SHARED/STATIC library building.
    - Switch building of TESTS.
    - Enable building of carefree-python based extensions.
    """
    def __init__(self, project, python=True):
        SConsVariables.__init__(self, args=ARGUMENTS)

        for var in [
          # Linux/GCC style compiler/linker flags.
          'CPPFLAGS', 'CXXFLAGS', 'LDFLAGS',
          # Windows/VC style path lists.
          'PATH', 'INCLUDE', 'LIB',
          ]:
            self.Add(var, "Override os.environ['%s']." % var)

        self.Add(BoolVariable(
          'DEBUG', "build %s with debugging symbols" % project,
          'no'))
        self.Add(BoolVariable(
          'SHARED', "build shared %s libraries" % project,
          'yes'))
        self.Add(BoolVariable(
          'STATIC', "build static %s libraries" % project,
          'yes'))
        self.Add(BoolVariable(
          'TESTS', "Build %s test programs" % project,
          'yes'))

        if python: # Want to build carefree-python based extensions?
            self.Add(PackageVariable(
              'PYTHON',
              "List of python(-config) binary names to build %s for"
              % project,
              'yes'))
