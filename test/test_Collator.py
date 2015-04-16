# ====================================================================
# Copyright (c) 2005-2010 Open Source Applications Foundation.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions: 
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software. 
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
# ====================================================================
#

import sys, os

from unittest import TestCase, main
from PyICU import *


class TestCollator(TestCase):

    def testSort(self):

        collator = Collator.createInstance(Locale.getFrance())
        module = sys.modules[TestCollator.__module__].__file__
        input = file(os.path.join(os.path.dirname(module), 'noms.txt'))
        names = [unicode(n.strip(), 'utf-8') for n in input.readlines()]
        input.close()
        ecole = names[0]

        names.sort()
        self.assert_(names[-1] is ecole)

        names.sort(collator.compare)
        self.assert_(names[2] is ecole)


if __name__ == "__main__":
    main()
