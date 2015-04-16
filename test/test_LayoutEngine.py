# -*- coding: utf-8 -*-
# ====================================================================
# Copyright (c) 2011-2011 Open Source Applications Foundation.
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

try:
    from fontTools.ttLib import TTFont
except ImportError, e:
    print >>sys.stderr, "\nfontTools package not found, skipping LayoutEngine tests\n"


class TTXLEFont(LEFontInstance):

    def __init__(self, fname, size=12):
        super(TTXLEFont, self).__init__()

        self.ttx = TTFont(fname)
        self.size = size
        self.upem = self.ttx['head'].unitsPerEm
        self.cmap = self.ttx['cmap'].getcmap(3, 1).cmap

    def getFontTable(self, table):
        return self.ttx.getTableData(table)

    def getAscent(self):
        self.ttx['hhea'].ascent * self.size * 1. / self.upem

    def getDescent(self):
        self.ttx['hhea'].descent * self.size * 1. / self.upem

    def getLeading(self):
        self.ttx['hhea'].lineGap * self.size * 1. / self.upem

    def getUnitsPerEm(self):
        return self.upem

    def mapCharToGlyph(self, code):
        return self.ttx.getGlyphID(self.cmap[code])

    def getGlyphAdvance(self, glyph):

        if glyph >= self.ttx['maxp'].numGlyphs:
            return (0., 0.)

        name = self.ttx.getGlyphName(glyph)
        x = self.ttx['hmtx'][name][0] * self.size * 1. / self.upem

        if 'vmtx' in self.ttx:
            y = self.ttx['vmtx'][name][0] * self.size * 1. / self.upem
        else:
            y = 0.

        return (x, y)

    def getGlyphPoint(self, glyph, point):
        return (0., 0.)

    def getXPixelsPerEm(self):
        return self.size

    def getYPixelsPerEm(self):
        return self.size

    def getScaleFactorX(self):
        return 1.

    def getScaleFactorY(self):
        return 1.


try:
    import fontTools
except ImportError:
    pass
else:
    class TestLayoutEngine(TestCase):

        def filePath(self, name):

            module = sys.modules[TestLayoutEngine.__module__].__file__
            return os.path.join(os.path.dirname(module), name)

        def setUp(self):

            self.font = TTXLEFont(self.filePath("lohit_hi.ttf"))
            self.layout = LayoutEngine.layoutEngineFactory(self.font,
                                                           ScriptCode.deva,
                                                           LanguageCode.nul)

        def testHello(self):

            self.layout.layoutChars(u"नमस्ते दुनिया")
            self.assertEqual(self.layout.getGlyphCount(), 13)


if __name__ == "__main__":
    try:
        import fontTools
    except ImportError:
        pass
    else:
        main()
