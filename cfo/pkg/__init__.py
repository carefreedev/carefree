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

"""cfo.pkg

.. moduleauthor:: Stefan Zimmermann <zimmermann.code@gmail.com>
"""

import os
import re

from path import path as Path

class Source(list):
    def __init__(self, rootpath, ignore = [r'\.pyc$']):
        self.rootpath = Path(rootpath).abspath()
        self.ignore = [re.compile(pattern) for pattern in ignore]
        self.extend(
          path for path in self.rootpath.walkfiles()
          if not any(r.search(path.ext) for r in self.ignore))
