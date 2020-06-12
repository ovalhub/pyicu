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

from icu import UnicodeString, BreakIterator, Locale


def printTextRange(iterator, start, end):

    s = iterator.getText().getText()
    print("%2d %2d  %s|%s|%s" %(start, end, s[:start], s[start:end], s[end:]))

#def printTextRange(iterator, start, end):
#
#    u = iterator.getText().getText(UnicodeString())
#    print "%2d %2d  %s|%s|%s" %(start, end,
#                                UnicodeString(u, 0, start),
#                                UnicodeString(u, start, end-start),
#                                UnicodeString(u, end))


def printEachForward(boundary):

    start = boundary.first()
    for end in boundary:
        printTextRange(boundary, start, end)
        start = end


# Print each element in reverse order:
def printEachBackward(boundary):

    end = boundary.last()
    while True:
        start = boundary.previous()
        if start == BreakIterator.DONE:
            break
        printTextRange(boundary, start, end)
        end = start


# Print the first element
def printFirst(boundary):

    start = boundary.first()
    end = boundary.next()
    printTextRange(boundary, start, end)


# Print the last element
def printLast(boundary):

    end = boundary.last()
    start = boundary.previous()
    if start != BreakIterator.DONE:
        printTextRange(boundary, start, end)


# Print the element at a specified position
def printAt(boundary, pos):

    end = boundary.following(pos)
    start = boundary.previous()
    printTextRange(boundary, start, end)


def main():

    print("ICU Break Iterator Sample Program")
    print("C++ Break Iteration in Python")
    
    stringToExamine = u"Aaa bbb ccc. Ddd eee fff."
    print("Examining: ", stringToExamine)

    # print each sentence in forward and reverse order
    boundary = BreakIterator.createSentenceInstance(Locale.getUS())
    boundary.setText(stringToExamine)

    print()
    print("Sentence Boundaries... ")
    print("----- forward: -----------")
    printEachForward(boundary)
    print("----- backward: ----------")
    printEachBackward(boundary)

    # print each word in order
    print()
    print("Word Boundaries...")
    boundary = BreakIterator.createWordInstance(Locale.getUS())
    boundary.setText(stringToExamine)
    print("----- forward: -----------")
    printEachForward(boundary)
    # print first element
    print("----- first: -------------")
    printFirst(boundary)
    # print last element
    print("----- last: --------------")
    printLast(boundary)
    # print word at charpos 10
    print("----- at pos 10: ---------")
    printAt(boundary, 10)

    print()
    print("End C++ Break Iteration in Python")


if __name__ == "__main__":
    main()
