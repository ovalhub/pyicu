# -*- coding: utf-8 -*-
# ====================================================================
# Copyright (c) 2009-2010 Open Source Applications Foundation.
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


class TestNormalizer2(TestCase):

    def assertNorm(self, normalizer2, expected, source):
        self.assertEqual(expected, normalizer2.normalize(source))
        a = UnicodeString()
        normalizer2.normalize(source, a)
        self.assertEqual(UnicodeString(expected), a)

    def testNormalize(self):

        try:
            from icu import Normalizer2
        except ImportError:
            return

        self.assertNorm(Normalizer2.getInstance(None, "nfkc_cf",
                                                UNormalizationMode2.COMPOSE),
                        u'hi there', "Hi There")
        self.assertNorm(Normalizer2.getNFCInstance(),
                        u"äßáＷ", u"äßa\u0301Ｗ")
        self.assertNorm(Normalizer2.getNFDInstance(),
                        u"a\u0308ßa\u0301Ｗ", u"äßa\u0301Ｗ")
        self.assertNorm(Normalizer2.getNFKCInstance(),
                        u"äßáW", u"äßa\u0301Ｗ")
        self.assertNorm(Normalizer2.getNFKDInstance(),
                        u"a\u0308ßa\u0301W", u"äßa\u0301Ｗ")
        self.assertNorm(Normalizer2.getNFKCCasefoldInstance(),
                        u"ässáw", u"äßa\u0301Ｗ")


if __name__ == "__main__":
    main()
