# ====================================================================
# Copyright (c) 2005-2011 Open Source Applications Foundation.
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

import sys, os, codecs

from unittest import TestCase, main
from icu import *

class TestCollator(TestCase):

    def filePath(self, name):

        module = sys.modules[TestCollator.__module__].__file__
        return os.path.join(os.path.dirname(module), name)

    def assertIsInstance(self, obj, cls):
        if hasattr(TestCase, 'assertIsInstance'):
            TestCase.assertIsInstance(self, obj, cls)
        else:
            self.assertTrue(isinstance(obj, cls),
                            u'%s is not an instance of %s' % (obj, cls))

    def testSort(self):

        collator = Collator.createInstance(Locale.getFrance())
        input = open(self.filePath('noms.txt'), 'rb')
        names = [unicode(n.strip(), 'utf-8') for n in input.readlines()]
        input.close()
        ecole = names[0]

        names.sort()
        self.assertTrue(names[-1] is ecole)

        if (sys.version_info >= (3,)):
            names.sort(key=collator.getSortKey)
        else:
            names.sort(collator.compare)
        self.assertTrue(names[2] is ecole)

    def testCreateInstancePolymorph(self):

        collator = Collator.createInstance(Locale("epo")) # Esperanto
        self.assertIsInstance(collator, RuleBasedCollator)
        rules = collator.getRules()

    def testGetSortKey(self):

        rules = UnicodeString("");
        collator = RuleBasedCollator(rules)
        collator.setAttribute(UCollAttribute.NORMALIZATION_MODE,
                              UCollAttributeValue.ON)
        collator.setAttribute(UCollAttribute.ALTERNATE_HANDLING,
                              UCollAttributeValue.SHIFTED)
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.QUATERNARY)
        collator.setAttribute(UCollAttribute.HIRAGANA_QUATERNARY_MODE,
                              UCollAttributeValue.ON)
        s = u'\u3052'
        k = collator.getSortKey(s)
        if (sys.version_info >= (3,)):
            byte2int = lambda c: c
        else:
            byte2int = ord

        if ICU_VERSION < '4.6':
            key = "AC300186DC9D019B0501282800"
        elif ICU_VERSION < '49.0':
            key = "791C0186DCFD019B05010D0D00"
        else:
            key = "791C0186DA95019B05010D0D00"

        self.assertTrue(key == ''.join(['%02X' %(byte2int(c)) for c in k]))

    def setupCollator(self, collator):

        collator.setAttribute(UCollAttribute.NORMALIZATION_MODE,
                              UCollAttributeValue.ON)
        collator.setAttribute(UCollAttribute.CASE_FIRST,
                              UCollAttributeValue.UPPER_FIRST)
        collator.setAttribute(UCollAttribute.ALTERNATE_HANDLING,
                              UCollAttributeValue.SHIFTED)
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.QUATERNARY)
        collator.setAttribute(UCollAttribute.HIRAGANA_QUATERNARY_MODE,
                              UCollAttributeValue.ON)

    def LoadCollatorFromRules(self):

        f = codecs.open(self.filePath("collation-rules.txt"), 'r', 'utf-8')
        rulelines = f.readlines()
        f.close()

        rules = UnicodeString("".join(rulelines));
        collator = RuleBasedCollator(rules)
        self.setupCollator(collator)

        return collator

    def LoadCollatorFromBinaryBuffer(self, bin):

        collator = RuleBasedCollator(bin, RuleBasedCollator(""))
        self.setupCollator(collator)

        return collator

    def testCollatorLoading(self):

        if ICU_VERSION >= '4.6':
            collator = self.LoadCollatorFromRules()
            key0 = collator.getSortKey(u'\u3069\u3052\u3056')
            bin = collator.cloneBinary()

            collator = self.LoadCollatorFromBinaryBuffer(bin)
            key1 = collator.getSortKey(u'\u3069\u3052\u3056')

            self.assertTrue(key0 == key1)


if __name__ == "__main__":
    main()
