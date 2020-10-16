# ====================================================================
# Copyright (c) 2020 Open Source Applications Foundation.
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

class TestBidi(TestCase):

    input_text = [
        UnicodeString(b'\xd9\x83\xd8\xa7\xd9\x86 Windows 10 \xd8\xa3\xd9\x88\xd9\x84 \xd9\x86\xd8\xb8\xd8\xa7\xd9\x85 \xd8\xaa\xd8\xb4\xd8\xba\xd9\x8a\xd9\x84 \xd8\xa8\xd8\xaa\xd9\x82\xd9\x86\xd9\x8a\xd8\xa9 4K.', 'utf-8'),
        UnicodeString(b'\xd9\x83\xd8\xa7\xd9\x86\xd8\xaa Microsoft Windows \xd8\xa7\xd9\x84\xd9\x85\xd8\xa7\xd9\x84\xd9\x83 \xd8\xa7\xd9\x84\xd8\xa3\xd9\x88\xd8\xad\xd8\xaf \xd9\x84\xd8\xb9\xd9\x84\xd8\xa7\xd9\x85\xd8\xa9 XP.', 'utf-8')]

    def testDefault(self):

        Locale.setDefault(Locale.getUS())
        layout = Bidi()
        layout.setPara(self.input_text[0])

        self.assertEqual(layout.getParaLevel(), 1)
        self.assertEqual(layout.getDirection(), UBiDiDirection.MIXED)
        self.assertEqual(layout.getLevels(), (1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1))
        self.assertEqual(layout.getVisualRun(0), (39, 1, 1))
        self.assertEqual(layout.getVisualRun(3), (4, 10, 0))

    def testForcedDirection(self):

        Locale.setDefault(Locale.getUS())
        layout = Bidi()
        layout.setPara(self.input_text[0], 0)

        self.assertEqual(layout.getParaLevel(), 0)
        self.assertEqual(layout.getDirection(), UBiDiDirection.MIXED)
        self.assertEqual(layout.getLevels(), (1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0))
        self.assertEqual(layout.getVisualRun(0), (0, 3, 1))
        self.assertEqual(layout.getVisualRun(3), (15, 22, 1))

    def testLines(self):

        Locale.setDefault(Locale.getUS())
        layout = Bidi()
        layout.setPara(self.input_text[1])

        line_layout_0 = layout.setLine(0, 15)

        self.assertEqual(line_layout_0.getLevels(), (1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1))
        self.assertEqual(line_layout_0.getVisualRun(0), (14, 1, 1))
        self.assertEqual(line_layout_0.getVisualRun(2), (0, 5, 1))

        line_layout_1 = layout.setLine(15, 47)

        self.assertEqual(line_layout_1.getLevels(), (2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1))
        self.assertEqual(line_layout_1.getVisualRun(0), (31, 1, 1))
        self.assertEqual(line_layout_1.getVisualRun(2), (7, 22, 1))

    def testTransform(self):

        if ICU_VERSION >= '58.0':
            Locale.setDefault(Locale.getUS())
            transform = BidiTransform()

            result = transform.transform(
                self.input_text[0],
                UBiDiDirection.LTR, UBiDiOrder.VISUAL,
                UBiDiDirection.RTL, UBiDiOrder.LOGICAL,
                UBiDiMirroring.OFF, Shape.DIGITS_EN2AN)

            self.assertEqual(result, UnicodeString(b'.\xd9\xa4K \xd8\xa9\xd9\x8a\xd9\x86\xd9\x82\xd8\xaa\xd8\xa8 \xd9\x84\xd9\x8a\xd8\xba\xd8\xb4\xd8\xaa \xd9\x85\xd8\xa7\xd8\xb8\xd9\x86 \xd9\x84\xd9\x88\xd8\xa3 \xd9\xa1\xd9\xa0 Windows \xd9\x86\xd8\xa7\xd9\x83', 'utf-8'))


if __name__ == "__main__":
    main()
