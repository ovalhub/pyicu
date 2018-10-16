# -*- coding: utf-8 -*-
# ====================================================================
# Copyright (c) 2018 Open Source Applications Foundation.
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

class TestNumberFormatter(TestCase):

    def testBasic(self):

        if ICU_VERSION >= '60.0':
            text = NumberFormatter.withLocale(Locale.getUS()).formatInt(1234)
            self.assertEqual(text, u'1,234')

            text = LocalizedNumberFormatter(Locale.getUS()).formatInt(1234)
            self.assertEqual(text, u'1,234')

    def testFancy(self):

        if ICU_VERSION >= '60.0':
            text = NumberFormatter.with_() \
                .notation(Notation.compactShort()) \
                .unit(CurrencyUnit('EUR')) \
                .rounding(Rounder.maxDigits(2)) \
                .locale(Locale.getFrance()) \
                .formatInt(1234)
            self.assertEqual(text, u'1,2\xa0k\xa0€')

    def testUnit(self):

        if ICU_VERSION >= '60.0':
            formatter = UnlocalizedNumberFormatter() \
                .sign(UNumberSignDisplay.ALWAYS) \
                .unit(MeasureUnit.createMeter()) \
                .unitWidth(UNumberUnitWidth.FULL_NAME)

            text = formatter.locale(Locale.getUS()).formatInt(1234)
            self.assertEqual(text, u'+1,234 meters')

            text = formatter.locale(Locale.getFrance()).formatInt(1234)
            if ICU_VERSION >= '63.0':
                self.assertEqual(text, u'+1\u202f234\xa0mètres')
            else:
                self.assertEqual(text, u'+1\xa0234 mètres')


if __name__ == "__main__":
    if ICU_VERSION >= '60.0':
        main()
