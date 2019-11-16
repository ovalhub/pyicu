# -*- coding: utf-8 -*-
# ====================================================================
# Copyright (c) 2019 Open Source Applications Foundation.
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

import sys, os, six

from unittest import TestCase, main
from icu import *


class _Replaceable(object):

    def __init__(self, buffer):
        self.buffer = buffer

    def getLength(self):
        return len(self.buffer)

    def getCharAt(self, offset):
        return self.buffer[offset]

    def getChar32At(self, offset):
        return self.buffer[offset]

    def extractBetween(self, start, limit):
        return self.buffer[start:limit]

    def handleReplaceBetween(self, start, limit, text):
        self.buffer = ''.join((self.buffer[:start], text, self.buffer[limit:]))

    def copy(self, start, limit, dest):
        self.buffer = ''.join((self.buffer[:dest], self.buffer[start:limit],
                               self.buffer[dest:]))

    def hasMetaData(self):
        return False


class TestPythonReplaceable(TestCase):

    def setUp(self):
        if ICU_VERSION < '55.0':
            self.skipTest(ICU_VERSION)

    def testAccess(self):

        _rep = _Replaceable('abcd')    # the python implementation
        rep = PythonReplaceable(_rep)  # the wrapper to pass to ICU

        self.assertEqual(4, rep.length())
        self.assertEqual(ord('b'), rep.charAt(1))
        self.assertEqual(ord('c'), rep.char32At(2))
        self.assertEqual('bc', rep.extractBetween(1, 3))

        rep.handleReplaceBetween(1, 3, 'pqrs')
        self.assertEqual('apqrsd', _rep.buffer)

    def testTransliterate(self):

        trans = Transliterator.createInstance('Accents-Any')
        inverse = trans.createInverse()

        string = u'\xe9v\xe9nement'
        if ICU_VERSION < '4.0':
            result = u"e<'>ve<'>nement"
        else:
            result = u"e\u2190'\u2192ve\u2190'\u2192nement"

        _rep = _Replaceable(string)    # the python implementation
        rep = PythonReplaceable(_rep)  # the wrapper to pass to ICU

        trans.transliterate(rep)
        self.assertEqual(result, _rep.buffer)

        inverse.transliterate(rep)
        self.assertEqual(string, _rep.buffer)


if __name__ == "__main__":
    main()
