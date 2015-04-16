# -*- coding: utf-8 -*-
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
from icu import *


class TestMessageFormat(TestCase):

    def testFormatMessage(self):

        x = 'x'
        f = Formattable(UnicodeString(x))

        text = MessageFormat.formatMessage("This is a string: {0}.", [f])
        self.assertTrue(text == "This is a string: x.")

    def testFormat(self):

        x = 'x'
        f = Formattable(UnicodeString(x))
        msgFormat = MessageFormat("This is a string: {0}")

        text = msgFormat.format([f], FieldPosition())
        self.assertTrue(text == "This is a string: x")

        if (sys.version_info < (3,) and 'PyPy' not in sys.version):
            # Reduced features of % operator might be intentional
            f = UnicodeString(x)
            text = msgFormat % f
            self.assertTrue(text == "This is a string: x")

    def testFormatAppend(self):

        x = 'x'
        f = Formattable(UnicodeString(x))
        msgFormat = MessageFormat("This is a string: {0}")

        text = msgFormat.format([f], UnicodeString("x"), FieldPosition())
        self.assertTrue(text == "xThis is a string: x")

    def testFormats(self):

        orig = TimeZone.createDefault().getID()
        tzid = 'America/Indiana/Vevay'        
        msgFormat = MessageFormat("{0,time,short} {0,time,z}")
        formats = msgFormat.getFormats()

        formats[0].setTimeZone(TimeZone.createTimeZone(tzid))
        self.assertTrue(msgFormat.getFormats()[0].getTimeZone().getID() == orig)

        msgFormat.setFormats(formats)
        self.assertTrue(msgFormat.getFormats()[0].getTimeZone().getID() == tzid)

    def testSelectFormat(self):

        try:
            from icu import SelectFormat
        except ImportError:
            return

        format = u"{0} est {1, select, female {allée} other {allé}} à Paris."
        msgFormat = MessageFormat(format, Locale("fr"))
        args = [Formattable("Kirti"), Formattable("female")]

        self.assertTrue(msgFormat.format(args) == u"Kirti est allée à Paris.")

    def testNamedArgs(self):

        if ICU_VERSION >= '4.0':
            msg = \
                '{num_emails_to_send, plural, ' \
                '=0 {unused plural form} ' \
                '=1 {One email will be sent.} ' \
                'other {# emails will be sent.}}'

            messageFormat = MessageFormat(msg, Locale("en"))

            name0 = "num_emails_to_send"
            arg0 = Formattable(5)

            result = messageFormat.format([name0], [arg0])
            self.assertTrue(result == u'5 emails will be sent.')


if __name__ == "__main__":
    main()
