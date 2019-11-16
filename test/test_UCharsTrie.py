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

class TestUCharsTrie(TestCase):

    def setUp(self):
        if ICU_VERSION < '4.8':
            self.skipTest(ICU_VERSION)

    def testBuildAndIterate(self):

        mappings = { 'ab': 3, 'abc': 6, 'abcd': 2, 'abcef': 11,
                     'abcp': 88, 'abcqr': 20 }

        builder = UCharsTrie.Builder()
        for key, value in mappings.items():
            builder.add(key, value)
        trie = builder.build(UStringTrieBuildOption.FAST)

        for key, value in trie:
            self.assertEqual(mappings[key], value)

    def testAccess(self):

        mappings = { 'ab': 3, 'abc': 6, 'abcd': 2, 'abcef': 11,
                     'abcp': 88, 'abcqr': 20 }

        builder = UCharsTrie.Builder()
        for key, value in mappings.items():
            builder.add(key, value)
        trie = builder.build(UStringTrieBuildOption.FAST)

        self.assertEqual((3, 6), (trie.next('abc'), trie.getValue()))
        state = trie.saveState()

        self.assertEqual(u'depq', trie.getNextUChars())

        self.assertEqual((2, 2), (trie.next('d'), trie.getValue()))
        self.assertEqual((0, None), (trie.next('e'), trie.getValue()))

        trie.resetToState(state)
        self.assertEqual((2, 11), (trie.next('ef'), trie.getValue()))

        trie.resetToState(state)
        self.assertEqual((2, 88), (trie.next('p'), trie.getValue()))


if __name__ == "__main__":
    if ICU_VERSION >= '4.8':
        main()
