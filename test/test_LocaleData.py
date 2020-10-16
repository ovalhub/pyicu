# ====================================================================
# Copyright (c) 2007-2013 Open Source Applications Foundation.
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
# This is a python translation of ICU's LocaleDataTest.java

import sys, os, six

from unittest import TestCase, main
from icu import *

NOT_FOUND_ERR = 'The requested resource cannot be found, error code: 2'

def print_output(string):
  pass

class ExemplarGroup:
    def __init__(_self, s, scriptCodes):
        _self.set = s
        _self.scs = scriptCodes
    def __hash__(_self):
        hash = 0
        for i in range(len(_self.scs) if len(_self.scs) < 4 else 4):
            hash = (hash << 8) + _self.scs[i]
        return hash
    def __eq__(_self, other):
        return (_self.set == other.set) and (_self.scs == other.scs)


class TestLocaleData(TestCase):
    def setUp(self):
        self.availableLocales = Locale.getAvailableLocales()

    def testPapersize(self):
        for locale in self.availableLocales.keys():
            papersize = LocaleData(locale).getPaperSize()
            #language = Locale(locale).getLanguage()
            country = Locale(locale).getCountry()

            if (['BZ','CA','CL','CO','CR','GT','MX','NI','PA','PH','PR','SV','US','VE'].count(country) > 0):
                self.assertTrue(papersize == (279, 216))
            elif country:
                self.assertTrue(papersize == (297, 210))

    def testMeasurementSystem(self):
        for locale in self.availableLocales.keys():
            measurementSystem = LocaleData(locale).getMeasurementSystem()
            #language = Locale(locale).getLanguage()
            country = Locale(locale).getCountry()

            # 0 means SI, 1 means US, 2 mean UK
            if (country in ['LR', 'US']):
                self.assertTrue(measurementSystem == 1)
            elif country in ['GB']:
                self.assertTrue(measurementSystem in [0, 2])
            elif country in ['MM']:
                self.assertTrue(measurementSystem in [1, 2])
            elif country:
                self.assertTrue(measurementSystem == 0)

    def testExemplarSet(self):
        testedExemplars = set()
        equalCount = 0

        for locale in self.availableLocales:
            scriptCodes = Script.getCode(locale)
            exemplarSets = []
            for k in range(2):
                # it seems USET_CASE_INSENSITIVE = 2
                option = 0 if k == 0 else 2
                # standard = 0, auxiliary = 1, index = 2, count = 3
                exemplarSet = LocaleData(locale).getExemplarSet(option, 0)
                exemplarSets.append(exemplarSet)
                exGrp = ExemplarGroup(exemplarSet, scriptCodes)
                if (not exGrp in testedExemplars):
                    testedExemplars.add(exGrp)
                    sets = []
                    for j in range(len(scriptCodes)):
                        sets.append(UnicodeSet('[:' + Script(scriptCodes[j]).getShortName() + ':]'))
                    existsInScript = False
                    iter = UnicodeSetIterator(exemplarSet)
                    while (not existsInScript and iter.nextRange()):
                        if (not iter.isString()):
                            for j in range(len(sets)):
                                if sets[j].contains(iter.getCodepoint(), iter.getCodepointEnd()):
                                    existsInScript = True
                                    break
                        else:
                            for j in range(len(sets)):
                                if sets[j].contains(iter.getString()):
                                    existsInScript = True
                                    break
                    if existsInScript == False:
                        print_output("ExemplarSet containment failed for locale : "+ locale)
            print_output(locale + " exemplar " + repr(six.text_type(exemplarSets[0])))
            print_output(locale + " exemplar(case-folded) " + repr(six.text_type(exemplarSets[1])))
            self.assertTrue(locale + " case-folded is a superset", exemplarSets[1].containsAll(exemplarSets[0]))
            if (exemplarSets[1] == exemplarSets[0]):
                ++equalCount
        self.assertTrue("case-folded is sometimes a strict superset, and sometimes equal",\
                        equalCount > 0 and equalCount < len(self.availableLocales))

    def testExemplarSet2(self):
        testedExemplars = set()
        equalCount = 0

        for locale in self.availableLocales:
            ld = LocaleData(locale)
            scriptCodes = Script.getCode(locale)
            exemplarSets = []
            for k in range(2): # for casing option in (normal, uncased)
                # it seems USET_CASE_INSENSITIVE = 2
                option = 0 if k == 0 else 2
                for h in range(2):
                    esType = 0 if h == 0 else 1
                    # standard = 0, auxiliary = 1, index = 2, count = 3
                    exemplarSet = LocaleData(locale).getExemplarSet(option, esType)
                    exemplarSets.append(exemplarSet)
                    exGrp = ExemplarGroup(exemplarSet, scriptCodes)
                    if (not exGrp in testedExemplars):
                        testedExemplars.add(exGrp)
                        sets = []
                        for j in range(len(scriptCodes)):
                            sets.append(UnicodeSet('[:' + Script(scriptCodes[j]).getShortName() + ':]'))
                            existsInScript = False
                            iter = UnicodeSetIterator(exemplarSet)
                            while (not existsInScript and iter.nextRange()):
                                if (not iter.isString()):
                                    for j in range(len(sets)):
                                        if sets[j].contains(iter.getCodepoint(), iter.getCodepointEnd()):
                                            existsInScript = True
                                            break
                                else:
                                    for j in range(len(sets)):
                                        if sets[j].contains(iter.getString()):
                                            existsInScript = True
                                            break
                            if existsInScript == False and h == 0:
                                print_output("ExemplarSet containment failed for locale,option,type : " \
                                      + locale + "," + str(option) + "," + str(esType))
            print_output(locale + " exemplar(ES_STANDARD)" + repr(six.text_type(exemplarSets[0])))
            print_output(locale + " exemplar(ES_AUXILIARY)" + repr(six.text_type(exemplarSets[1])))
            print_output(locale + " exemplar(case-folded,ES_STANDARD)" + repr(six.text_type(exemplarSets[2])))
            print_output(locale + " exemplar(case-folded,ES_AUXILIARY)" + repr(six.text_type(exemplarSets[3])))
            self.assertTrue(locale + " case-folded is a superset", exemplarSets[2].containsAll(exemplarSets[0]))
            self.assertTrue(locale + " case-folder is a superset", exemplarSets[3].containsAll(exemplarSets[1]))
            if (exemplarSets[2] == exemplarSets[0]):
                ++equalCount
            if (exemplarSets[3] == exemplarSets[1]):
                ++equalCount
        self.assertTrue("case-folded is sometimes a strict superset, and sometimes equal",\
                        equalCount > 0 and equalCount < len(self.availableLocales) * 2)

    def testCoverage(self):
        ld = LocaleData(Locale().getName())
        t = ld.getNoSubstitute()
        ld.setNoSubstitute(t)
        self.assertEqual(t, ld.getNoSubstitute())
        for i in range(4):
            print_output(repr(ld.getDelimiter(i)))

    def testLocaleDisplayPattern(self):
        ld = LocaleData(Locale().getName())
        print_output("Default locale LocaleDisplayPattern:" + ld.getLocaleDisplayPattern());
        print_output("Default locale LocaleSeparator:" + ld.getLocaleSeparator());
        for locale in self.availableLocales:
            ld = LocaleData(locale)
            try:
                print_output(locale + " LocaleDisplayPattern:" + repr(ld.getLocaleDisplayPattern()))
                getLocaleDisplayPattern = True
            except ICUError as e:  # resource not found
                getLocaleDisplayPattern = str(e) == NOT_FOUND_ERR
            except:
                getLocaleDisplayPattern = False
            self.assertTrue(getLocaleDisplayPattern)
            try:
                print_output(locale + " LocaleSeparator:" + repr(ld.getLocaleSeparator()))
                getLocaleSeparator = True
            except ICUError as e:  # resource not found
                getLocaleSeparator = str(e) == NOT_FOUND_ERR
            except:
                getLocaleSeparator = False
            self.assertTrue(getLocaleSeparator)


if __name__ == "__main__":
    main()
