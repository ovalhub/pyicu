# ====================================================================
# Copyright (c) 2004-2010 Open Source Applications Foundation.
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

from icu import *


def processCollator(options):

    if options.rules is not None:
        rules = unicode(options.rules, 'unicode-escape')
        collator = RuleBasedCollator(rules, Collator.TERTIARY,
                                     UCollAttributeValue.OFF)
    else:
        collator = Collator.createInstance(Locale(options.locale))

    if options.norm:
        collator.setAttribute(UCollAttribute.NORMALIZATION_MODE,
                              UCollAttributeValue.ON)
    if options.french:
        collator.setAttribute(UCollAttribute.FRENCH_COLLATION,
                              UCollAttributeValue.ON)
    if options.lower:
        collator.setAttribute(UCollAttribute.CASE_FIRST,
                              UCollAttributeValue.LOWER_FIRST)
    if options.upper:
        collator.setAttribute(UCollAttribute.CASE_FIRST,
                              UCollAttributeValue.UPPER_FIRST)
    if options.case:
        collator.setAttribute(UCollAttribute.CASE_LEVEL,
                              UCollAttributeValue.ON)
    if options.shifted:
        collator.setAttribute(UCollAttribute.ALTERNATE_HANDLING,
                              UCollAttributeValue.SHIFTED)
    if options.level == 1:
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.PRIMARY)
    elif options.level == 2:
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.SECONDARY)
    elif options.level == 3:
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.TERTIARY)
    elif options.level == 4:
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.QUATERNARY)
    elif options.level == 5:
        collator.setAttribute(UCollAttribute.STRENGTH,
                              UCollAttributeValue.IDENTICAL)
    else:
        raise ValueError, "--level must be between 1 and 5"

    return collator


def processStringSearch(options, collator):

    source = unicode(options.source, "unicode-escape")
    pattern = unicode(options.pattern, "unicode-escape")

    search = StringSearch(pattern, source, collator)
    if options.overlap:
        search.setAttribute(USearchAttribute.OVERLAP,
                            USearchAttributeValue.ON)
    if options.canonical:
        search.setAttribute(USearchAttribute.CANONICAL_MATCH,
                            USearchAttributeValue.ON)
    return search


def findPattern(search):

    found = False
    for offset in search:
        print("Pattern found at offset", offset, "size", search.getMatchedLength())
        found = True

    if not found:
        print("Pattern not found in source")


if __name__ == "__main__":
    from optparse import OptionParser

    parser = OptionParser(usage='''
strsrch [options*] --source source_string --pattern pattern_string

Example:
python strsrch.py --rules \\u0026b\\u003ca 
                  --source a\\u0020b\\u0020bc --pattern b
The format \\uXXXX is supported for the rules and comparison strings''')

    parser.add_option('-l', "--locale", dest='locale', default='en_US',
                      help="ICU locale to use.  Default is en_US")
    parser.add_option('-r', "--rules", dest='rules', default=None,
                      help="Collation rules file (overrides locale)")
    parser.add_option('-f', "--french", dest='french', default=False,
                      action="store_true", help="French accent ordering")
    parser.add_option('-n', "--norm", dest='norm', default=False,
                      action="store_true", help="Normalizing mode on")
    parser.add_option('-s', "--shifted", dest='shifted', default=False,
                      action="store_true", help="Shifted mode")
    parser.add_option('-L', "--lower", dest='lower', default=False,
                      action="store_true", help="Lower case first")
    parser.add_option('-U', "--upper", dest='upper', default=False,
                      action="store_true", help="Upper case first")
    parser.add_option('-C', "--case", dest='case', default=False,
                      action="store_true", help="Enable separate case level")
    parser.add_option('-S', "--sort", dest='level', default='1',
                      help="Sort level, 1 to 5, for Primary, Secondary, Tertiary, Quaternary, Identical")
    parser.add_option('-u', "--source", dest='source',
                      default="International Components for Unicode",
                      help="Source string")
    parser.add_option('-p', "--pattern", dest='pattern',
                      default="Unicode",
                      help="Pattern string to look for in source")
    parser.add_option('-o', "--overlap", dest='overlap', default=False,
                      action="store_true", help="Enable searching to be done on overlapping patterns")
    parser.add_option('-c', "--canonical", dest='canonical', default=False,
                      action="store_true", help="Enable searching to be done matching canonical equivalent patterns")

    options, args = parser.parse_args()
    options.level = int(options.level)

    collator = processCollator(options)
    search = processStringSearch(options, collator)

    print("Finding pattern", options.pattern, "in source", options.source)

    findPattern(search)
    del search
    del collator
