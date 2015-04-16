# ====================================================================
# Copyright (c) 2006-2010 Open Source Applications Foundation.
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
from datetime import datetime
from icu import *

class TestUDate(TestCase):

    def testConvertNaiveDatetime(self):

        def formatNaiveDatetime():
            # Make a naive datetime
            dt = datetime(2006, 4, 18, 5, 12)
            # ... and format it
            return DateFormat.createTimeInstance(DateFormat.SHORT).format(dt)

        before = formatNaiveDatetime()
        # Change ICU's default timezone
        TimeZone.setDefault(ICUtzinfo.getInstance('US/Eastern').timezone)
        after = formatNaiveDatetime()

        self.assertTrue(before == after)


if __name__ == "__main__":
    main()
