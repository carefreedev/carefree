# CareFREE_objects :: MODELED C++ w/Python @<3
#
# Copyright (C) 2011-2017 Stefan Zimmermann <user@zimmermann.co>
#
# CareFREE_objects is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CareFREE_objects is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CareFREE_objects.  If not, see <http://www.gnu.org/licenses/>.

"""
The CareFREE C++ library sources in a Python package.
"""

from path import Path
import zcons


class Source(Path):
    """
    Build interface for a CareFREE source directory.
    """

    def build(self, prefix=None):
        """
        Build the source by running SCons in its parent directory.
        """
        options = {'DEBUG': True}
        if prefix is not None:
            options['PREFIX'] = prefix
        with self.dirname():
            zcons.scons(**options)
