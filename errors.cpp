/* ====================================================================
 * Copyright (c) 2004-2010 Open Source Applications Foundation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * ====================================================================
 */

#include "common.h"
#include "structmember.h"

#include "errors.h"

static void _setMsg(PyObject *messages, UErrorCode code, const char *msg)
{
    PyObject *pycode = PyInt_FromLong((long) code);
    PyObject *pymsg = PyString_FromString(msg);

    PyObject_SetItem(messages, pycode, pymsg);
    Py_DECREF(pycode);
    Py_DECREF(pymsg);
}

static void registerErrors(PyObject *messages)
{
    _setMsg(messages, U_USING_FALLBACK_WARNING, "A resource bundle lookup returned a fallback result (not an error)");
    _setMsg(messages, U_ERROR_WARNING_START, "Start of information results (semantically successful)");
    _setMsg(messages, U_USING_DEFAULT_WARNING, "A resource bundle lookup returned a result from the root locale (not an error)");
    _setMsg(messages, U_SAFECLONE_ALLOCATED_WARNING, "A SafeClone operation required allocating memory (informational only)");
    _setMsg(messages, U_STATE_OLD_WARNING, "ICU has to use compatibility layer to construct the service. Expect performance/memory usage degradation. Consider upgrading");
    _setMsg(messages, U_STRING_NOT_TERMINATED_WARNING, "An output string could not be NUL-terminated because output length==destCapacity.");
    _setMsg(messages, U_SORT_KEY_TOO_SHORT_WARNING, "Number of levels requested in getBound is higher than the number of levels in the sort key");
    _setMsg(messages, U_AMBIGUOUS_ALIAS_WARNING, "This converter alias can go to different converter implementations");
    _setMsg(messages, U_DIFFERENT_UCA_VERSION, "ucol_open encountered a mismatch between UCA version and collator image version, so the collator was constructed from rules. No impact to further function");
    _setMsg(messages, U_ERROR_WARNING_LIMIT, "This must always be the last warning value to indicate the limit for UErrorCode warnings (last warning code +1)");
    _setMsg(messages, U_ZERO_ERROR, "No error, no warning.");
    _setMsg(messages, U_ILLEGAL_ARGUMENT_ERROR, "Illegal argument");
    _setMsg(messages, U_MISSING_RESOURCE_ERROR, "The requested resource cannot be found");
    _setMsg(messages, U_INVALID_FORMAT_ERROR, "Data format is not what is expected");
    _setMsg(messages, U_FILE_ACCESS_ERROR, "The requested file cannot be found");
    _setMsg(messages, U_INTERNAL_PROGRAM_ERROR, "Indicates a bug in the library code");
    _setMsg(messages, U_MESSAGE_PARSE_ERROR, "Unable to parse a message (message format)");
    _setMsg(messages, U_MEMORY_ALLOCATION_ERROR, "Memory allocation error");
    _setMsg(messages, U_INDEX_OUTOFBOUNDS_ERROR, "Trying to access the index that is out of bounds");
    _setMsg(messages, U_PARSE_ERROR, "Equivalent to Java ParseException");
    _setMsg(messages, U_INVALID_CHAR_FOUND, "Character conversion: Unmappable input sequence. In other APIs: Invalid character.");
    _setMsg(messages, U_TRUNCATED_CHAR_FOUND, "Character conversion: Incomplete input sequence.");
    _setMsg(messages, U_ILLEGAL_CHAR_FOUND, "Character conversion: Illegal input sequence/combination of input units..");
    _setMsg(messages, U_INVALID_TABLE_FORMAT, "Conversion table file found, but corrupted");
    _setMsg(messages, U_INVALID_TABLE_FILE, "Conversion table file not found");
    _setMsg(messages, U_BUFFER_OVERFLOW_ERROR, "A result would not fit in the supplied buffer");
    _setMsg(messages, U_UNSUPPORTED_ERROR, "Requested operation not supported in current context");
    _setMsg(messages, U_RESOURCE_TYPE_MISMATCH, "an operation is requested over a resource that does not support it");
    _setMsg(messages, U_ILLEGAL_ESCAPE_SEQUENCE, "ISO-2022 illegal escape sequence");
    _setMsg(messages, U_UNSUPPORTED_ESCAPE_SEQUENCE, "ISO-2022 unsupported escape sequence");
    _setMsg(messages, U_NO_SPACE_AVAILABLE, "No space available for in-buffer expansion for Arabic shaping");
    _setMsg(messages, U_CE_NOT_FOUND_ERROR, "Currently used only while setting variable top, but can be used generally");
    _setMsg(messages, U_PRIMARY_TOO_LONG_ERROR, "User tried to set variable top to a primary that is longer than two bytes");
    _setMsg(messages, U_STATE_TOO_OLD_ERROR, "ICU cannot construct a service from this state, as it is no longer supported");
    _setMsg(messages, U_TOO_MANY_ALIASES_ERROR, "There are too many aliases in the path to the requested resource. It is very possible that a circular alias definition has occurred");
    _setMsg(messages, U_ENUM_OUT_OF_SYNC_ERROR, "UEnumeration out of sync with underlying collection");
    _setMsg(messages, U_INVARIANT_CONVERSION_ERROR, "Unable to convert a UChar* string to char* with the invariant converter.");
    _setMsg(messages, U_INVALID_STATE_ERROR, "Requested operation can not be completed with ICU in its current state");
    _setMsg(messages, U_COLLATOR_VERSION_MISMATCH, "Collator version is not compatible with the base version");
    _setMsg(messages, U_USELESS_COLLATOR_ERROR, "Collator is options only and no base is specified");
    _setMsg(messages, U_STANDARD_ERROR_LIMIT, "This must always be the last value to indicate the limit for standard errors");
    _setMsg(messages, U_BAD_VARIABLE_DEFINITION, "Missing '$' or duplicate variable name");
    _setMsg(messages, U_PARSE_ERROR_START, "Start of Transliterator errors");
    _setMsg(messages, U_MALFORMED_RULE, "Elements of a rule are misplaced");
    _setMsg(messages, U_MALFORMED_SET, "A UnicodeSet pattern is invalid");
    _setMsg(messages, U_MALFORMED_SYMBOL_REFERENCE, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_MALFORMED_UNICODE_ESCAPE, "A Unicode escape pattern is invalid");
    _setMsg(messages, U_MALFORMED_VARIABLE_DEFINITION, "A variable definition is invalid");
    _setMsg(messages, U_MALFORMED_VARIABLE_REFERENCE, "A variable reference is invalid");
    _setMsg(messages, U_MISMATCHED_SEGMENT_DELIMITERS, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_MISPLACED_ANCHOR_START, "A start anchor appears at an illegal position");
    _setMsg(messages, U_MISPLACED_CURSOR_OFFSET, "A cursor offset occurs at an illegal position");
    _setMsg(messages, U_MISPLACED_QUANTIFIER, "A quantifier appears after a segment close delimiter");
    _setMsg(messages, U_MISSING_OPERATOR, "A rule contains no operator");
    _setMsg(messages, U_MISSING_SEGMENT_CLOSE, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_MULTIPLE_ANTE_CONTEXTS, "More than one ante context");
    _setMsg(messages, U_MULTIPLE_CURSORS, "More than one cursor");
    _setMsg(messages, U_MULTIPLE_POST_CONTEXTS, "More than one post context");
    _setMsg(messages, U_TRAILING_BACKSLASH, "A dangling backslash");
    _setMsg(messages, U_UNDEFINED_SEGMENT_REFERENCE, "A segment reference does not correspond to a defined segment");
    _setMsg(messages, U_UNDEFINED_VARIABLE, "A variable reference does not correspond to a defined variable");
    _setMsg(messages, U_UNQUOTED_SPECIAL, "A special character was not quoted or escaped");
    _setMsg(messages, U_UNTERMINATED_QUOTE, "A closing single quote is missing");
    _setMsg(messages, U_RULE_MASK_ERROR, "A rule is hidden by an earlier more general rule");
    _setMsg(messages, U_MISPLACED_COMPOUND_FILTER, "A compound filter is in an invalid location");
    _setMsg(messages, U_MULTIPLE_COMPOUND_FILTERS, "More than one compound filter");
    _setMsg(messages, U_INVALID_RBT_SYNTAX, "A '::id' rule was passed to the RuleBasedTransliterator parser");
    _setMsg(messages, U_INVALID_PROPERTY_PATTERN, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_MALFORMED_PRAGMA, "A 'use' pragma is invalid");
    _setMsg(messages, U_UNCLOSED_SEGMENT, "A closing ')' is missing");
    _setMsg(messages, U_ILLEGAL_CHAR_IN_SEGMENT, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_VARIABLE_RANGE_EXHAUSTED, "Too many stand-ins generated for the given variable range");
    _setMsg(messages, U_VARIABLE_RANGE_OVERLAP, "The variable range overlaps characters used in rules");
    _setMsg(messages, U_ILLEGAL_CHARACTER, "A special character is outside its allowed context");
    _setMsg(messages, U_INTERNAL_TRANSLITERATOR_ERROR, "Internal transliterator system error");
    _setMsg(messages, U_INVALID_ID, "A '::id' rule specifies an unknown transliterator");
    _setMsg(messages, U_INVALID_FUNCTION, "A '&fn()' rule specifies an unknown transliterator");
    _setMsg(messages, U_PARSE_ERROR_LIMIT, "The limit for Transliterator errors");
    _setMsg(messages, U_UNEXPECTED_TOKEN, "Syntax error in format pattern");
    _setMsg(messages, U_FMT_PARSE_ERROR_START, "Start of format library errors");
    _setMsg(messages, U_MULTIPLE_DECIMAL_SEPARATORS, "More than one decimal separator in number pattern");
    _setMsg(messages, U_MULTIPLE_EXPONENTIAL_SYMBOLS, "More than one exponent symbol in number pattern");
    _setMsg(messages, U_MALFORMED_EXPONENTIAL_PATTERN, "Grouping symbol in exponent pattern");
    _setMsg(messages, U_MULTIPLE_PERCENT_SYMBOLS, "More than one percent symbol in number pattern");
    _setMsg(messages, U_MULTIPLE_PERMILL_SYMBOLS, "More than one permill symbol in number pattern");
    _setMsg(messages, U_MULTIPLE_PAD_SPECIFIERS, "More than one pad symbol in number pattern");
    _setMsg(messages, U_PATTERN_SYNTAX_ERROR, "Syntax error in format pattern");
    _setMsg(messages, U_ILLEGAL_PAD_POSITION, "Pad symbol misplaced in number pattern");
    _setMsg(messages, U_UNMATCHED_BRACES, "Braces do not match in message pattern");
    _setMsg(messages, U_UNSUPPORTED_PROPERTY, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_UNSUPPORTED_ATTRIBUTE, "UNUSED as of ICU 2.4");
    _setMsg(messages, U_FMT_PARSE_ERROR_LIMIT, "The limit for format library errors");
    _setMsg(messages, U_BRK_ERROR_START, "Start of codes indicating Break Iterator failures");
    _setMsg(messages, U_BRK_INTERNAL_ERROR, "An internal error (bug) was detected.");
    _setMsg(messages, U_BRK_HEX_DIGITS_EXPECTED, "Hex digits expected as part of a escaped char in a rule.");
    _setMsg(messages, U_BRK_SEMICOLON_EXPECTED, "Missing ';' at the end of a RBBI rule.");
    _setMsg(messages, U_BRK_RULE_SYNTAX, "Syntax error in RBBI rule.");
    _setMsg(messages, U_BRK_UNCLOSED_SET, "UnicodeSet witing an RBBI rule missing a closing ']'.");
    _setMsg(messages, U_BRK_ASSIGN_ERROR, "Syntax error in RBBI rule assignment statement.");
    _setMsg(messages, U_BRK_VARIABLE_REDFINITION, "RBBI rule $Variable redefined.");
    _setMsg(messages, U_BRK_MISMATCHED_PAREN, "Mis-matched parentheses in an RBBI rule.");
    _setMsg(messages, U_BRK_NEW_LINE_IN_QUOTED_STRING, "Missing closing quote in an RBBI rule.");
    _setMsg(messages, U_BRK_UNDEFINED_VARIABLE, "Use of an undefined $Variable in an RBBI rule.");
    _setMsg(messages, U_BRK_INIT_ERROR, "Initialization failure.  Probable missing ICU Data.");
    _setMsg(messages, U_BRK_RULE_EMPTY_SET, "Rule contains an empty Unicode Set.");
    _setMsg(messages, U_BRK_UNRECOGNIZED_OPTION, "!!option in RBBI rules not recognized.");
    _setMsg(messages, U_BRK_MALFORMED_RULE_TAG, "The {nnn} tag on a rule is mal formed");
    _setMsg(messages, U_BRK_ERROR_LIMIT, "This must always be the last value to indicate the limit for Break Iterator failures");
    _setMsg(messages, U_REGEX_ERROR_START, "Start of codes indicating Regexp failures");
    _setMsg(messages, U_REGEX_INTERNAL_ERROR, "An internal error (bug) was detected.");
    _setMsg(messages, U_REGEX_RULE_SYNTAX, "Syntax error in regexp pattern.");
    _setMsg(messages, U_REGEX_INVALID_STATE, "RegexMatcher in invalid state for requested operation");
    _setMsg(messages, U_REGEX_BAD_ESCAPE_SEQUENCE, "Unrecognized backslash escape sequence in pattern");
    _setMsg(messages, U_REGEX_PROPERTY_SYNTAX, "Incorrect Unicode property");
    _setMsg(messages, U_REGEX_UNIMPLEMENTED, "Use of regexp feature that is not yet implemented.");
    _setMsg(messages, U_REGEX_MISMATCHED_PAREN, "Incorrectly nested parentheses in regexp pattern.");
    _setMsg(messages, U_REGEX_NUMBER_TOO_BIG, "Decimal number is too large.");
    _setMsg(messages, U_REGEX_BAD_INTERVAL, "Error in {min,max} interval");
    _setMsg(messages, U_REGEX_MAX_LT_MIN, "In {min,max}, max is less than min.");
    _setMsg(messages, U_REGEX_INVALID_BACK_REF, "Back-reference to a non-existent capture group.");
    _setMsg(messages, U_REGEX_INVALID_FLAG, "Invalid value for match mode flags.");
    _setMsg(messages, U_REGEX_LOOK_BEHIND_LIMIT, "Look-Behind pattern matches must have a bounded maximum length.");
    _setMsg(messages, U_REGEX_SET_CONTAINS_STRING, "Regexps cannot have UnicodeSets containing strings.");
    _setMsg(messages, U_REGEX_ERROR_LIMIT, "This must always be the last value to indicate the limit for regexp errors");
    _setMsg(messages, U_ERROR_LIMIT, "This must always be the last value to indicate the limit for UErrorCode (last error code +1)");
}

void _init_errors(PyObject *m)
{
    PyObject *messages = PyObject_GetAttrString(PyExc_ICUError, "messages");

    registerErrors(messages);
    Py_DECREF(messages);
}
