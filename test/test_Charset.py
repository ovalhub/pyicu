# ====================================================================
# Copyright (c) 2007-2010 Open Source Applications Foundation.
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
from icu import *

# We use u'stuff'.encode('encoding') instead of b'stuff' to represent
# bytes using literals. This is to ensure 2to3 doesn't turn things
# into unicode literals, but also to keep compatibility with Python
# pre 2.6, which didn't know about the b prefix to literals.

class TestCharset(TestCase):

    def testDetect(self):

        detector = CharsetDetector()
        detector.setText(u'foo'.encode('ascii'))

        match = detector.detect()
        self.assertTrue(match.getName() == 'UTF-8')

    def testDetectAll(self):

        detector = CharsetDetector(u'foo'.encode('ascii'))

        matches = detector.detectAll()
        self.assertTrue(matches[0].getName() == 'UTF-8')

    def testDeclared(self):

        bytes = u'beaut\xe9 probable'.encode('iso-8859-1')
        detector = CharsetDetector(bytes, 'iso-8859-1')

        self.assertTrue("ISO-8859-1" in (m.getName()
                                         for m in detector.detectAll()))

    def testUnicode(self):

        bytes = u'beaut\xe9 probable'.encode('iso-8859-1')
        ustring = unicode(CharsetDetector(bytes).detect())

        self.assertTrue(ustring.encode('iso-8859-1') == bytes)
        
        

if __name__ == "__main__":
    main()
