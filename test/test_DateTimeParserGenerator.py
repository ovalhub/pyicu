# -*- coding: utf-8 -*-
# ====================================================================
# Copyright (c) 2009-2015 Open Source Applications Foundation.
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

from unittest import TestCase, main
from icu import *


# These tests were lifted from the examples in ``dtptngsample.cpp`` in icu4c

class TestDateTimePatternGenerator(TestCase):

    def setUp(self):
        cal = Calendar.createInstance()
        cal.set(2016, 4, 10, 0, 30, 0)  # month value is 0-based
        self.date = cal.getTime()

    def testAddPattern(self):
        """Test overwriting a pattern with the same skeleton."""
        locale = Locale.getFrance()
        dtpg = DateTimePatternGenerator.createInstance(locale)

        sdf = SimpleDateFormat(dtpg.getBestPattern('MMMMddHmm'), locale)
        self.assertEqual(sdf.format(self.date), u'10 mai à 00:30')
        self.assertEqual(sdf.toPattern(), u"dd MMMM 'à' HH:mm")

        dtpg.addPattern("dd'. von' MMMM", True)
        sdf.applyPattern(dtpg.getBestPattern('MMMMddHmm'))
        self.assertEqual(sdf.format(self.date), u'10. von mai à 00:30')
        self.assertEqual(sdf.toPattern(), u"dd'. von' MMMM 'à' HH:mm")

    def testGetBestPattern(self):
        """Test a few different languages and common patterns."""
        skeletons = ('yQQQQ',  # year + full name of quarter, i.e., 4th quarter 1999
                     'yMMMM',  # year + full name of month, i.e., October 1999
                     'MMMMd',  # full name of month + day of the month, i.e., October 25
                     'hhmm',   # 12-hour-cycle format, i.e., 1:32 PM
                     'jjmm')   # preferred hour format for the given locale, i.e., 24-hour-cycle format for fr_FR
        locales = ((Locale('en_US'), (u'2nd quarter 2016', u'May 2016', u'May 10',
                                      u'12:30 AM', u'12:30 AM')),
                   (Locale('fr_FR'), (u'2e trimestre 2016', u'mai 2016', u'10 mai',
                                      u'12:30 AM', u'00:30')),
                   (Locale('zh_CN'), (u'2016年第2季度', u'2016年5月', u'5月10日',
                                      u'上午12:30', u'上午12:30')),)
        for locale, locale_data in locales:
            dtpg = DateTimePatternGenerator.createInstance(locale)
            for index, skeleton in enumerate(skeletons):
                pattern = dtpg.getBestPattern(skeleton)
                sdf = SimpleDateFormat(pattern, locale)
                self.assertEqual(sdf.format(self.date), locale_data[index])

    def testReplaceFieldType(self):
        """Test replacing an element of a pattern."""
        locale = Locale.getFrance()
        tz = TimeZone.createTimeZone('Europe/Paris')
        dtpg = DateTimePatternGenerator.createInstance(locale)
        sdf = SimpleDateFormat('EEEE d MMMM y HH:mm:ss zzzz', locale)
        sdf.setTimeZone(tz)
        pattern = sdf.toPattern()
        self.assertEqual(pattern, u'EEEE d MMMM y HH:mm:ss zzzz')
        self.assertEqual(sdf.format(self.date), u'lundi 9 mai 2016 23:30:00 heure d’été d’Europe centrale')

        newPattern = dtpg.replaceFieldTypes(pattern, 'vvvv')
        sdf.applyPattern(newPattern)
        self.assertEqual(sdf.toPattern(), u'EEEE d MMMM y HH:mm:ss vvvv')
        self.assertEqual(sdf.format(self.date), u'lundi 9 mai 2016 23:30:00 heure d’Europe centrale')


if __name__ == '__main__':
    main()
