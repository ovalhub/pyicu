# ====================================================================
# Copyright (c) 2014-2014 Open Source Applications Foundation.
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

class TestSpoofChecker(TestCase):
    def setUp(self):
        self.checker = SpoofChecker()

    def testCheck(self):
        checks = self.checker.check("xyz")
        self.assertEqual(checks, 0)

    def testAreConfusable(self):
        checks = self.checker.areConfusable("cxs", u"\u0441\u0445\u0455")
        self.assertEqual(checks, (USpoofChecks.MIXED_SCRIPT_CONFUSABLE |
                                  USpoofChecks.WHOLE_SCRIPT_CONFUSABLE))

        checks = self.checker.areConfusable(
            "A long string that will overflow stack buffers.  A long string that will overflow stack buffers. A long string that will overflow stack buffers.  A long string that will overflow stack buffers. ",
            "A long string that wi11 overflow stack buffers.  A long string that will overflow stack buffers. A long string that wi11 overflow stack buffers.  A long string that will overflow stack buffers. ")
        self.assertEqual(checks, USpoofChecks.SINGLE_SCRIPT_CONFUSABLE)

    def testGetSkeleton(self):
        ML = 0
        SL = USpoofChecks.SINGLE_SCRIPT_CONFUSABLE
        MA = USpoofChecks.ANY_CASE
        SA = USpoofChecks.SINGLE_SCRIPT_CONFUSABLE | USpoofChecks.ANY_CASE

        def checkSkeleton(checks, string, result):
            skeleton = self.checker.getSkeleton(checks, string)
            self.assertEqual(skeleton, result)

        checkSkeleton(MA, "I1l0O", "lllOO")

        # A long "identifier" that will overflow implementation stack buffers,
        # forcing heap allocations.
        checkSkeleton(SL, u" A 1ong \u02b9identifier' that will overflow implementation stack buffers, forcing heap allocations. A 1ong 'identifier' that will overflow implementation stack buffers, forcing heap allocations. A 1ong 'identifier' that will overflow implementation stack buffers, forcing heap allocations. A 1ong 'identifier' that will overflow implementation stack buffers, forcing heap allocations.",
                      u" A long 'identifier' that vvill overflovv irnplernentation stack buffers, forcing heap allocations. A long 'identifier' that vvill overflovv irnplernentation stack buffers, forcing heap allocations. A long 'identifier' that vvill overflovv irnplernentation stack buffers, forcing heap allocations. A long 'identifier' that vvill overflovv irnplernentation stack buffers, forcing heap allocations.")

        checkSkeleton(SL, "nochange", "nochange")
        checkSkeleton(MA, "love", "love")
        checkSkeleton(MA, "1ove", "love")   # Digit 1 to letter l
        checkSkeleton(ML, "OOPS", "OOPS")

        if ICU_VERSION < '55.1':
            # Digit 0 unchanged in lower case mode.
            checkSkeleton(ML, "00PS", "00PS")
        else:
            checkSkeleton(ML, "00PS", "OOPS")

        checkSkeleton(MA, "OOPS", "OOPS")
        checkSkeleton(MA, "00PS", "OOPS")   # Digit 0 to letter O in any case mode only
        checkSkeleton(SL, u"\u059c", u"\u0301")
        checkSkeleton(SL, u"\u2A74", u"\u003A\u003A\u003D")
        checkSkeleton(SL, u"\u247E", u"\u0028\u006C\u006C\u0029")  # "(ll)"

        if ICU_VERSION < '55.1':
            checkSkeleton(SL, u"\uFDFB",
                          u"\u062C\u0644\u0020\u062C\u0644\u0627\u0644\u0647")
        else:
            checkSkeleton(SL, u"\uFDFB",
                          u"\u062C\u0644\u0020\u062c\u0644l\u0644o")

        # This mapping exists in the ML and MA tables, does not exist in SL, SA
        # 0C83 ;	0C03 ;	
        if ICU_VERSION < '55.1':
            checkSkeleton(SL, u"\u0C83", u"\u0C83")
            checkSkeleton(SA, u"\u0C83", u"\u0C83")
        else:
            checkSkeleton(SL, u"\u0C83", u"\u0983")
            checkSkeleton(SA, u"\u0C83", u"\u0983")

        checkSkeleton(ML, u"\u0C83", u"\u0983")
        checkSkeleton(MA, u"\u0C83", u"\u0983")
        
        # 0391 ; 0041 ;
        # This mapping exists only in the MA table.
        checkSkeleton(MA, u"\u0391", "A")
        if ICU_VERSION < '55.1':
            checkSkeleton(SA, u"\u0391", u"\u0391")
            checkSkeleton(ML, u"\u0391", u"\u0391")
            checkSkeleton(SL, u"\u0391", u"\u0391")
        else:
            checkSkeleton(SA, u"\u0391", u'A')
            checkSkeleton(ML, u"\u0391", u'A')
            checkSkeleton(SL, u"\u0391", u'A')

        # 13CF ;  0062 ; 
        # This mapping exists in the ML and MA tables
        checkSkeleton(ML, u"\u13CF", "b")
        checkSkeleton(MA, u"\u13CF", "b")

        if ICU_VERSION < '55.1':
            checkSkeleton(SL, u"\u13CF", u"\u13CF")
            checkSkeleton(SA, u"\u13CF", u"\u13CF")
        else:
            checkSkeleton(SL, u"\u13CF", u'b')
            checkSkeleton(SA, u"\u13CF", u'b')

        # 0022 ;  0027 0027 ; 
        # all tables.
        checkSkeleton(SL, u"\u0022", u"\u0027\u0027")
        checkSkeleton(SA, u"\u0022", u"\u0027\u0027")
        checkSkeleton(ML, u"\u0022", u"\u0027\u0027")
        checkSkeleton(MA, u"\u0022", u"\u0027\u0027")

        # 017F ;  0066 ;
        # This mapping exists in the SA and MA tables
        checkSkeleton(MA, u"\u017F", "f")
        checkSkeleton(SA, u"\u017F", "f")

    def testInvisible(self):
        
        checks = self.checker.check(u"abcd\u0301ef")
        self.assertEquals(checks, 0)

        checks = self.checker.check(u"abcd\u0301\u0302\u0301ef")
        self.assertEquals(checks, USpoofChecks.INVISIBLE)

        # Two acute accents, one from the composed a with acute accent, \u00e1,
        # and one separate.
        checks = self.checker.check(u"abcd\u00e1\u0301xyz")
        self.assertEquals(checks, USpoofChecks.INVISIBLE)
        

if __name__ == "__main__":
    main()
