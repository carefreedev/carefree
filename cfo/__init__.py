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

"""cfo

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""

from zetup import find_zetup_config

zfg = find_zetup_config(__name__)

__distribution__ = zfg.DISTRIBUTION.find(__path__[0])
__description__ = zfg.DESCRIPTION

__version__ = zfg.VERSION

__requires__ = zfg.REQUIRES.checked
