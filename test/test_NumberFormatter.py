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

    def setUp(self):
        if ICU_VERSION < '60.0':
            self.skipTest(ICU_VERSION)

    def testBasic(self):

        text = NumberFormatter.withLocale(Locale.getUS()).formatInt(1234)
        self.assertEqual(text, u'1,234')

        text = LocalizedNumberFormatter(Locale.getUS()).formatInt(1234)
        self.assertEqual(text, u'1,234')

    def testFormattedNumber(self):

        if ICU_VERSION >= '64.0':
            value = NumberFormatter.withLocale(Locale.getUS()) \
                .formatIntToValue(1234)
            self.assertEqual(str(value), u'1,234')
            self.assertEqual(repr(value), u'<FormattedNumber: 1,234>')

            self.assertEqual([(x.getStart(), x.getLimit()) for x in value],
                             [(1, 2), (0, 5)])

    def testFancy(self):

        if ICU_VERSION < '64.0':
            text = NumberFormatter.with_() \
                .notation(Notation.compactShort()) \
                .unit(CurrencyUnit('EUR')) \
                .rounding(Rounder.maxDigits(2)) \
                .locale(Locale.getFrance()) \
                .formatInt(1234)
            self.assertEqual(text, u'1,2\xa0k\xa0€')

        if ICU_VERSION >= '62.0':
            text = NumberFormatter.with_() \
                .notation(Notation.compactShort()) \
                .unit(CurrencyUnit('EUR')) \
                .precision(Precision.maxSignificantDigits(2)) \
                .locale(Locale.getFrance()) \
                .formatInt(1234)
            self.assertEqual(text, u'1,2\xa0k\xa0€')

    def testUnit(self):

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

        if ICU_VERSION >= '61.0':
            formatter = UnlocalizedNumberFormatter() \
                .sign(UNumberSignDisplay.ALWAYS) \
                .unit(MeasureUnit.createMeter()) \
                .perUnit(MeasureUnit.createSecond()) \
                .unitWidth(UNumberUnitWidth.FULL_NAME)

            text = formatter.locale(Locale.getUS()).formatInt(1234)
            self.assertEqual(text, u'+1,234 meters per second')

    def testFromDecimalFormat(self):

        if ICU_VERSION >= '68.0':
            text = NumberFormat.createScientificInstance(Locale("de", "at")) \
                .toNumberFormatter() \
                .formatInt(1234)
            self.assertEqual(text, u'1,234E3')


    def testUsage(self):

        if ICU_VERSION >= '68.0':
            formatter = NumberFormatter.with_().usage("person-height").unit(MeasureUnit.createMeter()).locale(Locale("en-US"))

            self.assertEqual(formatter.formatDouble(0.25), '9.8 in')
            self.assertEqual(formatter.formatDouble(1.5), '4 ft, 11 in')
            unit = formatter.formatDoubleToValue(1.5).getOutputUnit()
            self.assertEqual(unit.getComplexity(), UMeasureUnitComplexity.MIXED)
            self.assertEqual(unit.getIdentifier(), "foot-and-inch")


class TestNumberRangeFormatter(TestCase):

    def setUp(self):
        if ICU_VERSION < '63.0':
            self.skipTest(ICU_VERSION)

    def testBasic(self):

        text = NumberRangeFormatter.withLocale(Locale.getItaly()) \
            .formatIntRange(1234, 5678)
        self.assertEqual(text, u'1.234-5.678')

        text = LocalizedNumberRangeFormatter(Locale.getItaly()) \
            .formatIntRange(1234, 5678)
        self.assertEqual(text, u'1.234-5.678')

    def testFormattedNumberRange(self):

        if ICU_VERSION >= '64.0':
            p2_formatter = NumberFormatter.with_() \
                .precision(Precision.maxSignificantDigits(2))
            p3_formatter = NumberFormatter.with_() \
                .precision(Precision.maxSignificantDigits(3))
            it_formatter = NumberRangeFormatter.withLocale(Locale.getItaly())

            text = it_formatter.numberFormatterBoth(p2_formatter) \
                .formatDoubleRange(1/3.0, 1/4.0)
            self.assertEqual(text, u'0,33-0,25')

            text = it_formatter \
                .numberFormatterFirst(p3_formatter) \
                .numberFormatterSecond(p2_formatter) \
                .formatFormattableRange(Formattable(1/3.0), Formattable(1/4.0))
            self.assertEqual(text, u'0,333-0,25')

            value = it_formatter \
                .numberFormatterFirst(p3_formatter) \
                .numberFormatterSecond(p2_formatter) \
                .formatDoubleRangeToValue(1/3.0, 1/4.0)
            self.assertEqual(str(value), u'0,333-0,25')
            self.assertEqual(repr(value), u'<FormattedNumberRange: 0,333-0,25>')

            self.assertEqual(value.getFirstDecimal(), u'3.33E-1')
            self.assertEqual(value.getSecondDecimal(), u'2.5E-1')
            if ICU_VERSION >= '68.0':
                self.assertEqual(value.getDecimalNumbers(), (b'0.333', b'0.25'))

            self.assertEqual([(x.getStart(), x.getLimit()) for x in value],
                             [(0, 1), (1, 2), (2, 5), (6, 7), (7, 8), (8, 10)])


if __name__ == "__main__":
    if ICU_VERSION >= '60.0':
        main()
