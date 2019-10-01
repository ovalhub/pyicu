# ====================================================================
# Copyright (c) 2016-2019 Open Source Applications Foundation.
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

import sys, os, six

from unittest import TestCase, main
from icu import *

# python2 can be built with 16- or 32-bit unicode chars (UCS2 or UCS4)
# python3 uses 32-bit unicode chars (logically)
def is_unicode_32bit():
    return len(u'\U0001f600') == 1

class TestScript(TestCase):

    def testSurrogatePairs(self):
        pairs = u'a\u0950\u4e2d\U00029efa'
        unicode_32bit = is_unicode_32bit()
        names = [Script.getScript(cp).getShortName() for cp in pairs]
        if unicode_32bit:
            self.assertEqual(['Latn', 'Deva', 'Hani', 'Hani'], names)
        else:
            self.assertTrue(
                (['Latn', 'Deva', 'Hani', 'Zzzz', 'Zzzz'] == names) or
                (['Latn', 'Deva', 'Hani', 'Zyyy', 'Zyyy'] == names))

        pairs = UnicodeString(pairs)
        # iterating UChar, not codepoints
        names = [Script.getScript(c).getShortName() for c in pairs]
        self.assertTrue(
            (['Latn', 'Deva', 'Hani', 'Zzzz', 'Zzzz'] == names) or
            (['Latn', 'Deva', 'Hani', 'Zyyy', 'Zyyy'] == names))

        # iterating codepoints not UChar
        names = [Script.getScript(cp).getShortName()
                 for cp in six.text_type(pairs)]
        if unicode_32bit:
            self.assertEqual(['Latn', 'Deva', 'Hani', 'Hani'], names)
        else:
            self.assertTrue(
                (['Latn', 'Deva', 'Hani', 'Zzzz', 'Zzzz'] == names) or
                (['Latn', 'Deva', 'Hani', 'Zyyy', 'Zyyy'] == names))

        # iterating codepoints, not UChar
        names = [Script.getScript(pairs.char32At(i)).getShortName()
                 for i in range(pairs.countChar32())]
        self.assertEqual(['Latn', 'Deva', 'Hani', 'Hani'], names)

        iterator = StringCharacterIterator(pairs)
        names = []
        while iterator.hasNext():
            desc = Script.getScript(iterator.next32PostInc()).getShortName()
            names.append(desc)
        self.assertEqual(['Latn', 'Deva', 'Hani', 'Hani'], names)

    def testSmileyFace(self):
        char = u'\U0001f600'
        u = UnicodeString(char)
        self.assertEqual(u.countChar32(), 1)

        if sys.version_info >= (3,):
            self.assertEqual(len(char), 1)
            self.assertEqual(str(u), char)
        elif is_unicode_32bit():
            self.assertEqual(len(char), 1)
            self.assertEqual(six.text_type(u), char)
        else:
            self.assertEqual(len(char), 2)
            self.assertEqual(six.text_type(u), char)

if __name__ == "__main__":
    main()
