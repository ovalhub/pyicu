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

import sys, os

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

        # Do not test sort key byte sequences directly:
        # They are unstable, that is, likely to change
        # with every UCA/CLDR/ICU release.
        # Instead, test that compare() is consistent with
        # comparing the equivalent sort keys.
        collator = Collator.createInstance(Locale.getJapanese())
        collator.setAttribute(UCollAttribute.NORMALIZATION_MODE,
                              UCollAttributeValue.ON)
        collator.setAttribute(UCollAttribute.ALTERNATE_HANDLING,
                              UCollAttributeValue.SHIFTED)
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.TERTIARY)

        # In Japanese, the following characters should be different
        # only on quaternary level.
        hira_ge = u'\u3052'  # Hiragana letter Ge
        kana_ge = u'\u30B2'  # Katakana letter Ge
        self.assertEqual(0, collator.compare(hira_ge, kana_ge))
        hira_ge_key = collator.getSortKey(hira_ge)
        kana_ge_key = collator.getSortKey(kana_ge)
        self.assertEqual(hira_ge_key, kana_ge_key)

        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.QUATERNARY)
        self.assertEqual(-1, collator.compare(hira_ge, kana_ge))
        hira_ge_key = collator.getSortKey(hira_ge)
        kana_ge_key = collator.getSortKey(kana_ge)
        self.assertTrue(hira_ge_key < kana_ge_key)

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

        rules = u"&z<\u00e6 &h<ch"
        collator = RuleBasedCollator(rules)
        self.setupCollator(collator)

        return collator

    def LoadCollatorFromBinaryBuffer(self, bin):

        root = Collator.createInstance(Locale.getRoot())
        collator = RuleBasedCollator(bin, root)
        self.setupCollator(collator)

        return collator

    def testCollatorLoading(self):

        if ICU_VERSION >= '4.6':
            collator = self.LoadCollatorFromRules()
            s = u'hchz\u00e6'

            key0 = collator.getSortKey(s)
            bin = collator.cloneBinary()

            collator = self.LoadCollatorFromBinaryBuffer(bin)
            key1 = collator.getSortKey(s)

            self.assertTrue(key0 == key1)


if __name__ == "__main__":
    main()
