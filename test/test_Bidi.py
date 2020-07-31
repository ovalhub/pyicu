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
        UnicodeString(u"\u0643\u0627\u0646 \u0057\u0069\u006e\u0064\u006f\u0077\u0073 \u0031\u0030 \u0623\u0648\u0644 \u0646\u0638\u0627\u0645 \u062a\u0634\u063a\u064a\u0644 \u0628\u062a\u0642\u0646\u064a\u0629 \u0034\u004b\u002e"),
        UnicodeString(u"\u0643\u0627\u0646\u062a \u004d\u0069\u0063\u0072\u006f\u0073\u006f\u0066\u0074 \u0057\u0069\u006e\u0064\u006f\u0077\u0073 \u0627\u0644\u0645\u0627\u0644\u0643 \u0627\u0644\u0623\u0648\u062d\u062f \u0644\u0639\u0644\u0627\u0645\u0629 \u0058\u0050\u002e")]

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

if __name__ == "__main__":
    main()
