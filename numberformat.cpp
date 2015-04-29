/* ====================================================================
 * Copyright (c) 2004-2011 Open Source Applications Foundation.
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

#include "bases.h"
#include "locale.h"
#include "format.h"
#include "numberformat.h"
#include "macros.h"

#if U_HAVE_RBNF
    DECLARE_CONSTANTS_TYPE(URBNFRuleSetTag);
#endif

#if U_ICU_VERSION_HEX >= 0x04080000
    DECLARE_CONSTANTS_TYPE(UCurrencySpacing);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    DECLARE_CONSTANTS_TYPE(UNumberCompactStyle);
#endif

/* DecimalFormatSymbols */

class t_decimalformatsymbols : public _wrapper {
public:
    DecimalFormatSymbols *object;
};

static int t_decimalformatsymbols_init(t_decimalformatsymbols *self,
                                       PyObject *args, PyObject *kwds);
static PyObject *t_decimalformatsymbols_getSymbol(t_decimalformatsymbols *self,
                                                  PyObject *args);
static PyObject *t_decimalformatsymbols_setSymbol(t_decimalformatsymbols *self,
                                                  PyObject *args);
static PyObject *t_decimalformatsymbols_getLocale(t_decimalformatsymbols *self,
                                                  PyObject *args);
#if U_ICU_VERSION_HEX >= 0x04020000
static PyObject *t_decimalformatsymbols_getPatternForCurrencySpacing(t_decimalformatsymbols *self, PyObject *args);
static PyObject *t_decimalformatsymbols_setPatternForCurrencySpacing(t_decimalformatsymbols *self, PyObject *args);
#endif

static PyMethodDef t_decimalformatsymbols_methods[] = {
    DECLARE_METHOD(t_decimalformatsymbols, getSymbol, METH_VARARGS),
    DECLARE_METHOD(t_decimalformatsymbols, setSymbol, METH_VARARGS),
    DECLARE_METHOD(t_decimalformatsymbols, getLocale, METH_VARARGS),
#if U_ICU_VERSION_HEX >= 0x04020000
    DECLARE_METHOD(t_decimalformatsymbols, getPatternForCurrencySpacing, METH_VARARGS),
    DECLARE_METHOD(t_decimalformatsymbols, setPatternForCurrencySpacing, METH_VARARGS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DecimalFormatSymbols, t_decimalformatsymbols, UObject,
             DecimalFormatSymbols, t_decimalformatsymbols_init, NULL);

/* NumberFormat */

class t_numberformat : public _wrapper {
public:
    NumberFormat *object;
};

static PyObject *t_numberformat_format(t_numberformat *self, PyObject *args);
static PyObject *t_numberformat_parse(t_numberformat *self, PyObject *args);
static PyObject *t_numberformat_parseCurrency(t_numberformat *self,
                                              PyObject *args);
static PyObject *t_numberformat_isParseIntegerOnly(t_numberformat *self);
static PyObject *t_numberformat_setParseIntegerOnly(t_numberformat *self,
                                                    PyObject *arg);
static PyObject *t_numberformat_isGroupingUsed(t_numberformat *self);
static PyObject *t_numberformat_setGroupingUsed(t_numberformat *self,
                                                PyObject *arg);
static PyObject *t_numberformat_getMaximumIntegerDigits(t_numberformat *self);
static PyObject *t_numberformat_setMaximumIntegerDigits(t_numberformat *self,
                                                        PyObject *arg);
static PyObject *t_numberformat_getMinimumIntegerDigits(t_numberformat *self);
static PyObject *t_numberformat_setMinimumIntegerDigits(t_numberformat *self,
                                                        PyObject *arg);
static PyObject *t_numberformat_getMaximumFractionDigits(t_numberformat *self);
static PyObject *t_numberformat_setMaximumFractionDigits(t_numberformat *self,
                                                        PyObject *arg);
static PyObject *t_numberformat_getMinimumFractionDigits(t_numberformat *self);
static PyObject *t_numberformat_setMinimumFractionDigits(t_numberformat *self,
                                                        PyObject *arg);
static PyObject *t_numberformat_isLenient(t_numberformat *self);
static PyObject *t_numberformat_setLenient(t_numberformat *self,
                                           PyObject *arg);
static PyObject *t_numberformat_getCurrency(t_numberformat *self);
static PyObject *t_numberformat_setCurrency(t_numberformat *self,
                                            PyObject *arg);
static PyObject *t_numberformat_createInstance(PyTypeObject *type,
                                               PyObject *args);
static PyObject *t_numberformat_createCurrencyInstance(PyTypeObject *type,
                                                       PyObject *args);
static PyObject *t_numberformat_createPercentInstance(PyTypeObject *type,
                                                      PyObject *args);
static PyObject *t_numberformat_createScientificInstance(PyTypeObject *type,
                                                         PyObject *args);
static PyObject *t_numberformat_getAvailableLocales(PyTypeObject *type);

static PyMethodDef t_numberformat_methods[] = {
    DECLARE_METHOD(t_numberformat, format, METH_VARARGS),
    DECLARE_METHOD(t_numberformat, parse, METH_VARARGS),
    DECLARE_METHOD(t_numberformat, parseCurrency, METH_VARARGS),
    DECLARE_METHOD(t_numberformat, isParseIntegerOnly, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setParseIntegerOnly, METH_O),
    DECLARE_METHOD(t_numberformat, isGroupingUsed, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setGroupingUsed, METH_O),
    DECLARE_METHOD(t_numberformat, getMaximumIntegerDigits, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setMaximumIntegerDigits, METH_O),
    DECLARE_METHOD(t_numberformat, getMinimumIntegerDigits, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setMinimumIntegerDigits, METH_O),
    DECLARE_METHOD(t_numberformat, getMaximumFractionDigits, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setMaximumFractionDigits, METH_O),
    DECLARE_METHOD(t_numberformat, getMinimumFractionDigits, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setMinimumFractionDigits, METH_O),
    DECLARE_METHOD(t_numberformat, isLenient, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setLenient, METH_O),
    DECLARE_METHOD(t_numberformat, getCurrency, METH_NOARGS),
    DECLARE_METHOD(t_numberformat, setCurrency, METH_O),
    DECLARE_METHOD(t_numberformat, createInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_numberformat, createCurrencyInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_numberformat, createPercentInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_numberformat, createScientificInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_numberformat, getAvailableLocales, METH_NOARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(NumberFormat, t_numberformat, Format, NumberFormat,
             abstract_init, NULL);

#if U_ICU_VERSION_HEX >= 0x04020000

/* CurrencyPluralInfo */

class t_currencypluralinfo : public _wrapper {
public:
    CurrencyPluralInfo *object;
};

static int t_currencypluralinfo_init(t_currencypluralinfo *self,
                                     PyObject *args, PyObject *kwds);
static PyObject *t_currencypluralinfo_getPluralRules(t_currencypluralinfo *self);
static PyObject *t_currencypluralinfo_setPluralRules(t_currencypluralinfo *self,
                                                     PyObject *arg);
static PyObject *t_currencypluralinfo_getCurrencyPluralPattern(t_currencypluralinfo *self, PyObject *args);
static PyObject *t_currencypluralinfo_setCurrencyPluralPattern(t_currencypluralinfo *self, PyObject *args);
static PyObject *t_currencypluralinfo_getLocale(t_currencypluralinfo *self);
static PyObject *t_currencypluralinfo_setLocale(t_currencypluralinfo *self,
                                                PyObject *arg);

static PyMethodDef t_currencypluralinfo_methods[] = {
    DECLARE_METHOD(t_currencypluralinfo, getPluralRules, METH_NOARGS),
    DECLARE_METHOD(t_currencypluralinfo, setPluralRules, METH_O),
    DECLARE_METHOD(t_currencypluralinfo, getCurrencyPluralPattern, METH_VARARGS),
    DECLARE_METHOD(t_currencypluralinfo, setCurrencyPluralPattern, METH_VARARGS),
    DECLARE_METHOD(t_currencypluralinfo, getLocale, METH_NOARGS),
    DECLARE_METHOD(t_currencypluralinfo, setLocale, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyPluralInfo, t_currencypluralinfo, UObject,
             CurrencyPluralInfo, t_currencypluralinfo_init, NULL);

#endif

/* DecimalFormat */

class t_decimalformat : public _wrapper {
public:
    DecimalFormat *object;
};

static int t_decimalformat_init(t_decimalformat *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_decimalformat_getPositivePrefix(t_decimalformat *self,
                                                   PyObject *args);
static PyObject *t_decimalformat_setPositivePrefix(t_decimalformat *self,
                                                   PyObject *arg);
static PyObject *t_decimalformat_getNegativePrefix(t_decimalformat *self,
                                                   PyObject *args);
static PyObject *t_decimalformat_setNegativePrefix(t_decimalformat *self,
                                                   PyObject *arg);
static PyObject *t_decimalformat_getPositiveSuffix(t_decimalformat *self,
                                                   PyObject *args);
static PyObject *t_decimalformat_setPositiveSuffix(t_decimalformat *self,
                                                   PyObject *arg);
static PyObject *t_decimalformat_getNegativeSuffix(t_decimalformat *self,
                                                   PyObject *args);
static PyObject *t_decimalformat_setNegativeSuffix(t_decimalformat *self,
                                                   PyObject *arg);
static PyObject *t_decimalformat_getMultiplier(t_decimalformat *self);
static PyObject *t_decimalformat_setMultiplier(t_decimalformat *self,
                                               PyObject *arg);
static PyObject *t_decimalformat_getRoundingIncrement(t_decimalformat *self);
static PyObject *t_decimalformat_setRoundingIncrement(t_decimalformat *self,
                                                      PyObject *arg);
static PyObject *t_decimalformat_getRoundingMode(t_decimalformat *self);
static PyObject *t_decimalformat_setRoundingMode(t_decimalformat *self,
                                                 PyObject *arg);
static PyObject *t_decimalformat_getFormatWidth(t_decimalformat *self);
static PyObject *t_decimalformat_setFormatWidth(t_decimalformat *self,
                                                PyObject *arg);
static PyObject *t_decimalformat_getPadCharacterString(t_decimalformat *self,
                                                       PyObject *args);
static PyObject *t_decimalformat_setPadCharacter(t_decimalformat *self,
                                                 PyObject *arg);
static PyObject *t_decimalformat_getPadPosition(t_decimalformat *self);
static PyObject *t_decimalformat_setPadPosition(t_decimalformat *self,
                                                PyObject *arg);
static PyObject *t_decimalformat_isScientificNotation(t_decimalformat *self);
static PyObject *t_decimalformat_setScientificNotation(t_decimalformat *self,
                                                       PyObject *arg);
static PyObject *t_decimalformat_getMinimumExponentDigits(t_decimalformat *self);
static PyObject *t_decimalformat_setMinimumExponentDigits(t_decimalformat *self,
                                                          PyObject *arg);
static PyObject *t_decimalformat_isExponentSignAlwaysShown(t_decimalformat *self);
static PyObject *t_decimalformat_setExponentSignAlwaysShown(t_decimalformat *self,
                                                            PyObject *arg);
static PyObject *t_decimalformat_isDecimalSeparatorAlwaysShown(t_decimalformat *self);
static PyObject *t_decimalformat_setDecimalSeparatorAlwaysShown(t_decimalformat *self,
                                                                PyObject *arg);
static PyObject *t_decimalformat_getGroupingSize(t_decimalformat *self);
static PyObject *t_decimalformat_setGroupingSize(t_decimalformat *self,
                                                 PyObject *arg);
static PyObject *t_decimalformat_getSecondaryGroupingSize(t_decimalformat *self);
static PyObject *t_decimalformat_setSecondaryGroupingSize(t_decimalformat *self,
                                                          PyObject *arg);
static PyObject *t_decimalformat_toPattern(t_decimalformat *self,
                                           PyObject *args);
static PyObject *t_decimalformat_toLocalizedPattern(t_decimalformat *self,
                                                    PyObject *args);
static PyObject *t_decimalformat_applyPattern(t_decimalformat *self,
                                              PyObject *arg);
static PyObject *t_decimalformat_applyLocalizedPattern(t_decimalformat *self,
                                                       PyObject *arg);
static PyObject *t_decimalformat_getMaximumSignificantDigits(t_decimalformat *self);
static PyObject *t_decimalformat_setMaximumSignificantDigits(t_decimalformat *self, PyObject *arg);
static PyObject *t_decimalformat_getMinimumSignificantDigits(t_decimalformat *self);
static PyObject *t_decimalformat_setMinimumSignificantDigits(t_decimalformat *self, PyObject *arg);
static PyObject *t_decimalformat_areSignificantDigitsUsed(t_decimalformat *self);
static PyObject *t_decimalformat_setSignificantDigitsUsed(t_decimalformat *self,
                                                          PyObject *arg);
static PyObject *t_decimalformat_getDecimalFormatSymbols(t_decimalformat *self);
static PyObject *t_decimalformat_setDecimalFormatSymbols(t_decimalformat *self,
                                                         PyObject *arg);
#if U_ICU_VERSION_HEX >= 0x04020000
static PyObject *t_decimalformat_getCurrencyPluralInfo(t_decimalformat *self);
static PyObject *t_decimalformat_setCurrencyPluralInfo(t_decimalformat *self,
                                                       PyObject *arg);
#endif

static PyMethodDef t_decimalformat_methods[] = {
    DECLARE_METHOD(t_decimalformat, getPositivePrefix, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, setPositivePrefix, METH_O),
    DECLARE_METHOD(t_decimalformat, getNegativePrefix, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, setNegativePrefix, METH_O),
    DECLARE_METHOD(t_decimalformat, getPositiveSuffix, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, setPositiveSuffix, METH_O),
    DECLARE_METHOD(t_decimalformat, getNegativeSuffix, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, setNegativeSuffix, METH_O),
    DECLARE_METHOD(t_decimalformat, getMultiplier, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setMultiplier, METH_O),
    DECLARE_METHOD(t_decimalformat, getRoundingIncrement, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setRoundingIncrement, METH_O),
    DECLARE_METHOD(t_decimalformat, getRoundingMode, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setRoundingMode, METH_O),
    DECLARE_METHOD(t_decimalformat, getFormatWidth, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setFormatWidth, METH_O),
    DECLARE_METHOD(t_decimalformat, getPadCharacterString, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, setPadCharacter, METH_O),
    DECLARE_METHOD(t_decimalformat, getPadPosition, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setPadPosition, METH_O),
    DECLARE_METHOD(t_decimalformat, isScientificNotation, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setScientificNotation, METH_O),
    DECLARE_METHOD(t_decimalformat, getMinimumExponentDigits, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setMinimumExponentDigits, METH_O),
    DECLARE_METHOD(t_decimalformat, isExponentSignAlwaysShown, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setExponentSignAlwaysShown, METH_O),
    DECLARE_METHOD(t_decimalformat, isDecimalSeparatorAlwaysShown, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setDecimalSeparatorAlwaysShown, METH_O),
    DECLARE_METHOD(t_decimalformat, getGroupingSize, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setGroupingSize, METH_O),
    DECLARE_METHOD(t_decimalformat, getSecondaryGroupingSize, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setSecondaryGroupingSize, METH_O),
    DECLARE_METHOD(t_decimalformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, toLocalizedPattern, METH_VARARGS),
    DECLARE_METHOD(t_decimalformat, applyPattern, METH_O),
    DECLARE_METHOD(t_decimalformat, applyLocalizedPattern, METH_O),
    DECLARE_METHOD(t_decimalformat, getMaximumSignificantDigits, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setMaximumSignificantDigits, METH_O),
    DECLARE_METHOD(t_decimalformat, getMinimumSignificantDigits, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setMinimumSignificantDigits, METH_O),
    DECLARE_METHOD(t_decimalformat, areSignificantDigitsUsed, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setSignificantDigitsUsed, METH_O),
    DECLARE_METHOD(t_decimalformat, getDecimalFormatSymbols, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setDecimalFormatSymbols, METH_O),
#if U_ICU_VERSION_HEX >= 0x04020000
    DECLARE_METHOD(t_decimalformat, getCurrencyPluralInfo, METH_NOARGS),
    DECLARE_METHOD(t_decimalformat, setCurrencyPluralInfo, METH_O),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DecimalFormat, t_decimalformat, NumberFormat, DecimalFormat,
             t_decimalformat_init, NULL);

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)

/* CompactDecimalFormat */

class t_compactdecimalformat : public _wrapper {
public:
    CompactDecimalFormat *object;
};

static PyObject *t_compactdecimalformat_createInstance(PyTypeObject *type,
                                                       PyObject *args);

static PyMethodDef t_compactdecimalformat_methods[] = {
    DECLARE_METHOD(t_compactdecimalformat, createInstance, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CompactDecimalFormat, t_compactdecimalformat, DecimalFormat,
             CompactDecimalFormat, abstract_init, NULL);

#endif

/* RuleBasedNumberFormat */

class t_rulebasednumberformat : public _wrapper {
public:
    RuleBasedNumberFormat *object;
};

static int t_rulebasednumberformat_init(t_rulebasednumberformat *self,
                                        PyObject *args, PyObject *kwds);
static PyObject *t_rulebasednumberformat_getRules(t_rulebasednumberformat *self,
                                                  PyObject *args);
static PyObject *t_rulebasednumberformat_getNumberOfRuleSetNames(t_rulebasednumberformat *self);
static PyObject *t_rulebasednumberformat_getRuleSetName(t_rulebasednumberformat *self, PyObject *args);
static PyObject *t_rulebasednumberformat_getNumberOfRuleSetDisplayNameLocales(t_rulebasednumberformat *self);
static PyObject *t_rulebasednumberformat_getRuleSetDisplayName(t_rulebasednumberformat *self, PyObject *args);
static PyObject *t_rulebasednumberformat_format(t_rulebasednumberformat *self,
                                                PyObject *args);
static PyObject *t_rulebasednumberformat_isLenient(t_rulebasednumberformat *self);
static PyObject *t_rulebasednumberformat_setLenient(t_rulebasednumberformat *self, PyObject *arg);
static PyObject *t_rulebasednumberformat_getDefaultRuleSetName(t_rulebasednumberformat *self, PyObject *args);
static PyObject *t_rulebasednumberformat_setDefaultRuleSet(t_rulebasednumberformat *self, PyObject *arg);

static PyMethodDef t_rulebasednumberformat_methods[] = {
    DECLARE_METHOD(t_rulebasednumberformat, getRules, METH_VARARGS),
    DECLARE_METHOD(t_rulebasednumberformat, getNumberOfRuleSetNames, METH_NOARGS),
    DECLARE_METHOD(t_rulebasednumberformat, getRuleSetName, METH_VARARGS),
    DECLARE_METHOD(t_rulebasednumberformat, getNumberOfRuleSetDisplayNameLocales, METH_NOARGS),
    DECLARE_METHOD(t_rulebasednumberformat, getRuleSetDisplayName, METH_VARARGS),
    DECLARE_METHOD(t_rulebasednumberformat, format, METH_VARARGS),
    DECLARE_METHOD(t_rulebasednumberformat, isLenient, METH_NOARGS),
    DECLARE_METHOD(t_rulebasednumberformat, setLenient, METH_O),
    DECLARE_METHOD(t_rulebasednumberformat, getDefaultRuleSetName, METH_VARARGS),
    DECLARE_METHOD(t_rulebasednumberformat, setDefaultRuleSet, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(RuleBasedNumberFormat, t_rulebasednumberformat, NumberFormat,
             RuleBasedNumberFormat, t_rulebasednumberformat_init, NULL);

PyObject *wrap_NumberFormat(NumberFormat *format)
{
    RETURN_WRAPPED_IF_ISINSTANCE(format, DecimalFormat);
    RETURN_WRAPPED_IF_ISINSTANCE(format, RuleBasedNumberFormat);
    return wrap_NumberFormat(format, T_OWNED);
}

/* ChoiceFormat */

class t_choiceformat : public _wrapper {
public:
    ChoiceFormat *object;
};

static int t_choiceformat_init(t_choiceformat *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_choiceformat_toPattern(t_choiceformat *self,
                                          PyObject *args);
static PyObject *t_choiceformat_applyPattern(t_choiceformat *self,
                                             PyObject *arg);
static PyObject *t_choiceformat_setChoices(t_choiceformat *self,
                                           PyObject *args);
static PyObject *t_choiceformat_getLimits(t_choiceformat *self);
static PyObject *t_choiceformat_getClosures(t_choiceformat *self);
static PyObject *t_choiceformat_getFormats(t_choiceformat *self);
static PyObject *t_choiceformat_format(t_choiceformat *self, PyObject *args);

static PyMethodDef t_choiceformat_methods[] = {
    DECLARE_METHOD(t_choiceformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_choiceformat, applyPattern, METH_O),
    DECLARE_METHOD(t_choiceformat, setChoices, METH_VARARGS),
    DECLARE_METHOD(t_choiceformat, getLimits, METH_NOARGS),
    DECLARE_METHOD(t_choiceformat, getClosures, METH_NOARGS),
    DECLARE_METHOD(t_choiceformat, getFormats, METH_NOARGS),
    DECLARE_METHOD(t_choiceformat, format, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(ChoiceFormat, t_choiceformat, NumberFormat, ChoiceFormat,
             t_choiceformat_init, NULL);


/* DecimalFormatSymbols */

static int t_decimalformatsymbols_init(t_decimalformatsymbols *self,
                                       PyObject *args, PyObject *kwds)
{
    Locale *locale;
    DecimalFormatSymbols *dfs;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(dfs = new DecimalFormatSymbols(status));
        self->object = dfs;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(dfs = new DecimalFormatSymbols(*locale, status));
            self->object = dfs;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_decimalformatsymbols_getSymbol(t_decimalformatsymbols *self,
                                                  PyObject *args)
{
    DecimalFormatSymbols::ENumberFormatSymbol symbol;
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &symbol))
        {
            UnicodeString u = self->object->getSymbol(symbol);
            return PyUnicode_FromUnicodeString(&u);
        }
      case 2:
        if (!parseArgs(args, "iU", &symbol, &u))
        {
            u->setTo(self->object->getSymbol(symbol));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getSymbol", args);
}

static PyObject *t_decimalformatsymbols_setSymbol(t_decimalformatsymbols *self,
                                                  PyObject *args)
{
    DecimalFormatSymbols::ENumberFormatSymbol symbol;
    UnicodeString *u, _u;
    
    if (!parseArgs(args, "iS", &symbol, &u, &_u))
    {
        self->object->setSymbol(symbol, *u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setSymbol", args);
}

static PyObject *t_decimalformatsymbols_getLocale(t_decimalformatsymbols *self,
                                                  PyObject *args)
{
    ULocDataLocaleType type;
    Locale locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(locale = self->object->getLocale(ULOC_VALID_LOCALE,
                                                     status));
        return wrap_Locale(locale);
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            STATUS_CALL(locale = self->object->getLocale(type, status));
            return wrap_Locale(locale);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocale", args);
}

#if U_ICU_VERSION_HEX >= 0x04020000

static PyObject *t_decimalformatsymbols_getPatternForCurrencySpacing(t_decimalformatsymbols *self, PyObject *args)
{
#if U_ICU_VERSION_HEX >= 0x04080000
    UCurrencySpacing type;
#else
    DecimalFormatSymbols::ECurrencySpacing type;
#endif
    UBool beforeCurrency;

    if (!parseArgs(args, "ib", &type, &beforeCurrency))
    {
        UnicodeString u;
        STATUS_CALL(u = self->object->getPatternForCurrencySpacing(type, beforeCurrency, status));
        return PyUnicode_FromUnicodeString(&u);
    }

    return PyErr_SetArgsError((PyObject *) self, "getPatternForCurrencySpacing", args);
}

static PyObject *t_decimalformatsymbols_setPatternForCurrencySpacing(t_decimalformatsymbols *self, PyObject *args)
{
    UnicodeString *u, _u;
#if U_ICU_VERSION_HEX >= 0x04080000
    UCurrencySpacing type;
#else
    DecimalFormatSymbols::ECurrencySpacing type;
#endif
    UBool beforeCurrency;

    if (!parseArgs(args, "ibS", &type, &beforeCurrency, &u, &_u))
    {
        /* copied */
        self->object->setPatternForCurrencySpacing(type, beforeCurrency, *u);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPatternForCurrencySpacing", args);
}

#endif

DEFINE_RICHCMP(DecimalFormatSymbols, t_decimalformatsymbols);


/* NumberFormat */

static PyObject *t_numberformat_format(t_numberformat *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    double d;
    int i;
    PY_LONG_LONG l;
    FieldPosition *fp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "d", &d))
        {
            self->object->format(d, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "i", &i))
        {
            self->object->format(i, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "L", &l))
        {
          self->object->format((int64_t) l, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "dP", TYPE_CLASSID(FieldPosition),
                       &d, &fp))
        {
            self->object->format(d, _u, *fp);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "iP", TYPE_CLASSID(FieldPosition),
                       &i, &fp))
        {
            self->object->format(i, _u, *fp);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "LP", TYPE_CLASSID(FieldPosition),
                       &l, &fp))
        {
          self->object->format((int64_t) l, _u, *fp);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "dUP", TYPE_CLASSID(FieldPosition),
                       &d, &u, &fp))
        {
            self->object->format(d, *u, *fp);
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "iUP", TYPE_CLASSID(FieldPosition),
                       &i, &u, &fp))
        {
            self->object->format(i, *u, *fp);
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "LUP", TYPE_CLASSID(FieldPosition),
                       &l, &u, &fp))
        {
          self->object->format((int64_t) l, *u, *fp);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return t_format_format((t_format *) self, args);
}

static PyObject *t_numberformat_parse(t_numberformat *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    Formattable *f;
    ParsePosition *pp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Formattable result;
            STATUS_CALL(self->object->parse(*u, result, status));
            return wrap_Formattable(result);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Formattable),
                       &u, &_u, &f))
        {
            STATUS_CALL(self->object->parse(*u, *f, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(ParsePosition),
                       &u, &_u, &pp))
        {
            Formattable result;
            pp->setErrorIndex(-1);
            self->object->parse(*u, result, *pp);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            return wrap_Formattable(result);
        }
        break;
      case 3:
        if (!parseArgs(args, "SPP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(ParsePosition),
                       &u, &_u, &f, &pp))
        {
            pp->setErrorIndex(-1);
            self->object->parse(*u, *f, *pp);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "parse", args);
}

#if U_ICU_VERSION_HEX < VERSION_HEX(49, 0, 0)
static PyObject *t_numberformat_parseCurrency(t_numberformat *self,
                                              PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    Formattable *f;
    ParsePosition *pp;
    ParsePosition _pp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Formattable result;
            _pp.setErrorIndex(-1);
            self->object->parseCurrency(*u, result, _pp);
            if (_pp.getErrorIndex() != -1)
                Py_RETURN_NONE;
            return wrap_Formattable(result);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Formattable),
                       &u, &_u, &f))
        {
            _pp.setErrorIndex(-1);
            self->object->parseCurrency(*u, *f, _pp);
            if (_pp.getErrorIndex() != -1)
                Py_RETURN_NONE;
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(ParsePosition),
                       &u, &_u, &pp))
        {
            Formattable result;
            pp->setErrorIndex(-1);
            self->object->parseCurrency(*u, result, *pp);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            return wrap_Formattable(result);
        }
        break;
      case 3:
        if (!parseArgs(args, "SPP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(ParsePosition),
                       &u, &_u, &f, &pp))
        {
            pp->setErrorIndex(-1);
            self->object->parseCurrency(*u, *f, *pp);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            Py_RETURN_ARG(args, 1);
        }
        break;
    }
        
    return PyErr_SetArgsError((PyObject *) self, "parseCurrency", args);
}
#else
static PyObject *t_numberformat_parseCurrency(t_numberformat *self,
                                              PyObject *args)
{
    UnicodeString _u, *u;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            CurrencyAmount *a;
            ParsePosition _pp;

            _pp.setErrorIndex(-1);
            a = self->object->parseCurrency(*u, _pp);
            if (_pp.getErrorIndex() != -1)
                Py_RETURN_NONE;
            return wrap_CurrencyAmount(a, T_OWNED);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "parseCurrency", args);
}
#endif

static PyObject *t_numberformat_isParseIntegerOnly(t_numberformat *self)
{
    int b = self->object->isParseIntegerOnly();
    Py_RETURN_BOOL(b);
}

static PyObject *t_numberformat_setParseIntegerOnly(t_numberformat *self,
                                                    PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setParseIntegerOnly(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setParseIntegerOnly", arg);
}

static PyObject *t_numberformat_isGroupingUsed(t_numberformat *self)
{
    int b = self->object->isGroupingUsed();
    Py_RETURN_BOOL(b);
}

static PyObject *t_numberformat_setGroupingUsed(t_numberformat *self,
                                                PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setGroupingUsed(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setGroupingUsed", arg);
}

static PyObject *t_numberformat_getMaximumIntegerDigits(t_numberformat *self)
{
    int n = self->object->getMaximumIntegerDigits();
    return PyInt_FromLong(n);
}

static PyObject *t_numberformat_setMaximumIntegerDigits(t_numberformat *self,
                                                        PyObject *arg)
{
    int n;

    if (!parseArg(arg, "i", &n))
    {
        self->object->setMaximumIntegerDigits(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMaximumIntegerDigits", arg);
}

static PyObject *t_numberformat_getMinimumIntegerDigits(t_numberformat *self)
{
    int n = self->object->getMinimumIntegerDigits();
    return PyInt_FromLong(n);
}

static PyObject *t_numberformat_setMinimumIntegerDigits(t_numberformat *self,
                                                        PyObject *arg)
{
    int n;

    if (!parseArg(arg, "i", &n))
    {
        self->object->setMinimumIntegerDigits(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMinimumIntegerDigits", arg);
}

static PyObject *t_numberformat_getMaximumFractionDigits(t_numberformat *self)
{
    int n = self->object->getMaximumFractionDigits();
    return PyInt_FromLong(n);
}

static PyObject *t_numberformat_setMaximumFractionDigits(t_numberformat *self,
                                                         PyObject *arg)
{
    int n;

    if (!parseArg(arg, "i", &n))
    {
        self->object->setMaximumFractionDigits(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMaximumFractionDigits", arg);
}

static PyObject *t_numberformat_getMinimumFractionDigits(t_numberformat *self)
{
    int n = self->object->getMinimumFractionDigits();
    return PyInt_FromLong(n);
}

static PyObject *t_numberformat_setMinimumFractionDigits(t_numberformat *self,
                                                         PyObject *arg)
{
    int n;

    if (!parseArg(arg, "i", &n))
    {
        self->object->setMinimumFractionDigits(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMinimumFractionDigits", arg);
}

static PyObject *t_numberformat_isLenient(t_numberformat *self)
{
    UBool n = self->object->isLenient();
    Py_RETURN_BOOL(n);
}

static PyObject *t_numberformat_setLenient(t_numberformat *self,
                                           PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setLenient(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLenient", arg);
}

static PyObject *t_numberformat_getCurrency(t_numberformat *self)
{
    UnicodeString u(self->object->getCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_numberformat_setCurrency(t_numberformat *self,
                                            PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        /* copied */
        STATUS_CALL(self->object->setCurrency(u->getBuffer(), status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setCurrency", arg);
}

static PyObject *t_numberformat_createInstance(PyTypeObject *type,
                                               PyObject *args)
{
    NumberFormat *format;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = NumberFormat::createInstance(status));
        return wrap_NumberFormat(format);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(format = NumberFormat::createInstance(*locale, status));
            return wrap_NumberFormat(format);
        }
        break;
    }
            
    return PyErr_SetArgsError(type, "createInstance", args);
}

static PyObject *t_numberformat_createCurrencyInstance(PyTypeObject *type,
                                                       PyObject *args)
{
    NumberFormat *format;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = NumberFormat::createCurrencyInstance(status));
        return wrap_NumberFormat(format);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(format = NumberFormat::createCurrencyInstance(*locale, status));
            return wrap_NumberFormat(format);
        }
        break;
    }
            
    return PyErr_SetArgsError(type, "createCurrencyInstance", args);
}
static PyObject *t_numberformat_createPercentInstance(PyTypeObject *type,
                                                      PyObject *args)
{
    NumberFormat *format;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = NumberFormat::createPercentInstance(status));
        return wrap_NumberFormat(format);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(format = NumberFormat::createPercentInstance(*locale, status));
            return wrap_NumberFormat(format);
        }
        break;
    }
            
    return PyErr_SetArgsError(type, "createPercentInstance", args);
}

static PyObject *t_numberformat_createScientificInstance(PyTypeObject *type,
                                                         PyObject *args)
{
    NumberFormat *format;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = NumberFormat::createScientificInstance(status));
        return wrap_NumberFormat(format);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(format = NumberFormat::createScientificInstance(*locale, status));
            return wrap_NumberFormat(format);
        }
        break;
    }
            
    return PyErr_SetArgsError(type, "createScientificInstance", args);
}

static PyObject *t_numberformat_getAvailableLocales(PyTypeObject *type)
{
    int count;
    const Locale *locales = NumberFormat::getAvailableLocales(count);
    PyObject *dict = PyDict_New();

    for (int32_t i = 0; i < count; i++) {
        Locale *locale = (Locale *) locales + i;
        PyObject *obj = wrap_Locale(locale, 0);
        PyDict_SetItemString(dict, locale->getName(), obj);
        Py_DECREF(obj);
    }

    return dict;
}


#if U_ICU_VERSION_HEX >= 0x04020000

/* CurrencyPluralInfo */

static int t_currencypluralinfo_init(t_currencypluralinfo *self,
                                     PyObject *args, PyObject *kwds)
{
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = new CurrencyPluralInfo(status));
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(self->object = new CurrencyPluralInfo(*locale,
                                                                  status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
        break;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_currencypluralinfo_getPluralRules(t_currencypluralinfo *self)
{
    return wrap_PluralRules(self->object->getPluralRules()->clone(), T_OWNED);
}

static PyObject *t_currencypluralinfo_setPluralRules(t_currencypluralinfo *self,
                                                     PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->setPluralRules(*u, status)); /* transient */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPluralRules", arg);
}

static PyObject *t_currencypluralinfo_getCurrencyPluralPattern(t_currencypluralinfo *self, PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            self->object->getCurrencyPluralPattern(*u0, _u1);
            return PyUnicode_FromUnicodeString(&_u1);
        }
        break;
      case 2:
        if (!parseArgs(args, "SU", &u0, &_u0, &u1))
        {
            self->object->getCurrencyPluralPattern(*u0, *u1);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getCurrencyPluralPattern", args);
}

static PyObject *t_currencypluralinfo_setCurrencyPluralPattern(t_currencypluralinfo *self, PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;

    if (!parseArgs(args, "SS", &u0, &u1))
    {
        /* u0 transient, u1 copied */
        STATUS_CALL(self->object->setCurrencyPluralPattern(*u0, *u1, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setCurrencyPluralPattern", args);
}

static PyObject *t_currencypluralinfo_getLocale(t_currencypluralinfo *self)
{
    return wrap_Locale(self->object->getLocale());
}

static PyObject *t_currencypluralinfo_setLocale(t_currencypluralinfo *self,
                                                PyObject *arg)
{
    Locale *locale;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(self->object->setLocale(*locale, status)); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLocale", arg);
}

DEFINE_RICHCMP(CurrencyPluralInfo, t_currencypluralinfo);

#endif


/* DecimalFormat */

static int t_decimalformat_init(t_decimalformat *self,
                                PyObject *args, PyObject *kwds)
{
    DecimalFormat *format;
    DecimalFormatSymbols *dfs;
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(format = new DecimalFormat(status));
        self->object = format;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(format = new DecimalFormat(*u, status));
            self->object = format;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SP",
                       TYPE_CLASSID(DecimalFormatSymbols),
                       &u, &_u, &dfs))
        {
            INT_STATUS_CALL(format = new DecimalFormat(*u, *dfs, status));
            self->object = format;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_decimalformat_getPositivePrefix(t_decimalformat *self,
                                                   PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getPositivePrefix(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getPositivePrefix(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getPositivePrefix", args);
}

static PyObject *t_decimalformat_setPositivePrefix(t_decimalformat *self,
                                                   PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setPositivePrefix(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPositivePrefix", arg);
}

static PyObject *t_decimalformat_getNegativePrefix(t_decimalformat *self,
                                                   PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getNegativePrefix(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getNegativePrefix(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getNegativePrefix", args);
}

static PyObject *t_decimalformat_setNegativePrefix(t_decimalformat *self,
                                                   PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setNegativePrefix(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNegativePrefix", arg);
}

static PyObject *t_decimalformat_getPositiveSuffix(t_decimalformat *self,
                                                   PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getPositiveSuffix(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getPositiveSuffix(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getPositiveSuffix", args);
}

static PyObject *t_decimalformat_setPositiveSuffix(t_decimalformat *self,
                                                   PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setPositiveSuffix(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPositiveSuffix", arg);
}

static PyObject *t_decimalformat_getNegativeSuffix(t_decimalformat *self,
                                                   PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getNegativeSuffix(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getNegativeSuffix(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getNegativeSuffix", args);
}

static PyObject *t_decimalformat_setNegativeSuffix(t_decimalformat *self,
                                                   PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setNegativeSuffix(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNegativeSuffix", arg);
}

static PyObject *t_decimalformat_getMultiplier(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getMultiplier());
}

static PyObject *t_decimalformat_setMultiplier(t_decimalformat *self,
                                               PyObject *arg)
{
    int n;

    if (!parseArg(arg, "i", &n))
    {
        self->object->setMultiplier(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMultiplier", arg);
}

static PyObject *t_decimalformat_getRoundingIncrement(t_decimalformat *self)
{
    return PyFloat_FromDouble(self->object->getRoundingIncrement());
}

static PyObject *t_decimalformat_setRoundingIncrement(t_decimalformat *self,
                                                      PyObject *arg)
{
    double d;

    if (!parseArg(arg, "d", &d))
    {
        self->object->setRoundingIncrement(d);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setRoundingIncrement", arg);
}

static PyObject *t_decimalformat_getRoundingMode(t_decimalformat *self)
{
    DecimalFormat::ERoundingMode mode = self->object->getRoundingMode();
    return PyInt_FromLong(mode);
}

static PyObject *t_decimalformat_setRoundingMode(t_decimalformat *self,
                                                 PyObject *arg)
{
    DecimalFormat::ERoundingMode mode;

    if (!parseArg(arg, "i", &mode))
    {
        self->object->setRoundingMode(mode);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setRoundingMode", arg);
}

static PyObject *t_decimalformat_getFormatWidth(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getFormatWidth());
}

static PyObject *t_decimalformat_setFormatWidth(t_decimalformat *self,
                                                PyObject *arg)
{
    int width;

    if (!parseArg(arg, "i", &width))
    {
        self->object->setFormatWidth(width);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setFormatWidth", arg);
}

static PyObject *t_decimalformat_getPadCharacterString(t_decimalformat *self,
                                                       PyObject *args)
{
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 0:
      {
          UnicodeString u = self->object->getPadCharacterString();
          return PyUnicode_FromUnicodeString(&u);
      }
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            u->setTo(self->object->getPadCharacterString());
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getPadCharacterString", args);
}

static PyObject *t_decimalformat_setPadCharacter(t_decimalformat *self,
                                                 PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setPadCharacter(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPadCharacter", arg);
}

static PyObject *t_decimalformat_getPadPosition(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getPadPosition());
}

static PyObject *t_decimalformat_setPadPosition(t_decimalformat *self,
                                                PyObject *arg)
{
    DecimalFormat::EPadPosition pos;

    if (!parseArg(arg, "i", &pos))
    {
        self->object->setPadPosition(pos);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPadPosition", arg);
}

static PyObject *t_decimalformat_isScientificNotation(t_decimalformat *self)
{
    int b = self->object->isScientificNotation();
    Py_RETURN_BOOL(b);
}

static PyObject *t_decimalformat_setScientificNotation(t_decimalformat *self,
                                                       PyObject *arg)
{
    int b;
    
    if (!parseArg(arg, "b", &b))
    {
        self->object->setScientificNotation(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setScientificNotation", arg);
}

static PyObject *t_decimalformat_getMinimumExponentDigits(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getMinimumExponentDigits());
}

static PyObject *t_decimalformat_setMinimumExponentDigits(t_decimalformat *self,
                                                          PyObject *arg)
{
    int digits;

    if (!parseArg(arg, "i", &digits))
    {
        self->object->setMinimumExponentDigits(digits);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMinimumExponentDigits", arg);
}

static PyObject *t_decimalformat_isExponentSignAlwaysShown(t_decimalformat *self)
{
    int b = self->object->isExponentSignAlwaysShown();
    Py_RETURN_BOOL(b);
}

static PyObject *t_decimalformat_setExponentSignAlwaysShown(t_decimalformat *self, PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setExponentSignAlwaysShown(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setExponentSignAlwaysShown", arg);
}

static PyObject *t_decimalformat_isDecimalSeparatorAlwaysShown(t_decimalformat *self)
{
    int b = self->object->isDecimalSeparatorAlwaysShown();
    Py_RETURN_BOOL(b);
}

static PyObject *t_decimalformat_setDecimalSeparatorAlwaysShown(t_decimalformat *self, PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setDecimalSeparatorAlwaysShown(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDecimalSeparatorAlwaysShown", arg);
}

static PyObject *t_decimalformat_getGroupingSize(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getGroupingSize());
}

static PyObject *t_decimalformat_setGroupingSize(t_decimalformat *self,
                                                 PyObject *arg)
{
    int size;

    if (!parseArg(arg, "i", &size))
    {
        self->object->setGroupingSize(size);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setGroupingSize", arg);
}

static PyObject *t_decimalformat_getSecondaryGroupingSize(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getSecondaryGroupingSize());
}

static PyObject *t_decimalformat_setSecondaryGroupingSize(t_decimalformat *self,
                                                          PyObject *arg)
{
    int size;

    if (!parseArg(arg, "i", &size))
    {
        self->object->setSecondaryGroupingSize(size);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setSecondaryGroupingSize", arg);
}

static PyObject *t_decimalformat_toPattern(t_decimalformat *self,
                                           PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toPattern(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->toPattern(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toPattern", args);
}

static PyObject *t_decimalformat_toLocalizedPattern(t_decimalformat *self,
                                                    PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toLocalizedPattern(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->toLocalizedPattern(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toLocalizedPattern", args);
}

static PyObject *t_decimalformat_applyPattern(t_decimalformat *self,
                                              PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyPattern(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_decimalformat_applyLocalizedPattern(t_decimalformat *self,
                                                       PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyLocalizedPattern(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyLocalizedPattern", arg);
}

static PyObject *t_decimalformat_getMaximumSignificantDigits(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getMaximumSignificantDigits());
}

static PyObject *t_decimalformat_setMaximumSignificantDigits(t_decimalformat *self, PyObject *arg)
{
    int digits;

    if (!parseArg(arg, "i", &digits))
    {
        self->object->setMaximumSignificantDigits(digits);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMaximumSignificantDigits", arg);
}

static PyObject *t_decimalformat_getMinimumSignificantDigits(t_decimalformat *self)
{
    return PyInt_FromLong(self->object->getMinimumSignificantDigits());
}

static PyObject *t_decimalformat_setMinimumSignificantDigits(t_decimalformat *self, PyObject *arg)
{
    int digits;

    if (!parseArg(arg, "i", &digits))
    {
        self->object->setMinimumSignificantDigits(digits);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMinimumSignificantDigits", arg);
}

static PyObject *t_decimalformat_areSignificantDigitsUsed(t_decimalformat *self)
{
    int b = self->object->areSignificantDigitsUsed();
    Py_RETURN_BOOL(b);
}

static PyObject *t_decimalformat_setSignificantDigitsUsed(t_decimalformat *self,
                                                          PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setSignificantDigitsUsed(b);
        Py_RETURN_NONE;
    }
        
    return PyErr_SetArgsError((PyObject *) self, "setSignificantDigitsUsed", arg);
}

static PyObject *t_decimalformat_getDecimalFormatSymbols(t_decimalformat *self)
{
    const DecimalFormatSymbols *dfs = self->object->getDecimalFormatSymbols();
    return wrap_DecimalFormatSymbols(new DecimalFormatSymbols(*dfs), T_OWNED);
}

static PyObject *t_decimalformat_setDecimalFormatSymbols(t_decimalformat *self,
                                                         PyObject *arg)
{
    DecimalFormatSymbols *dfs;

    if (!parseArg(arg, "P", TYPE_CLASSID(DecimalFormatSymbols), &dfs))
    {
        self->object->adoptDecimalFormatSymbols(new DecimalFormatSymbols(*dfs));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDecimalFormatSymbols",
                              arg);
}

#if U_ICU_VERSION_HEX >= 0x04020000

static PyObject *t_decimalformat_getCurrencyPluralInfo(t_decimalformat *self)
{
    const CurrencyPluralInfo *cpi = self->object->getCurrencyPluralInfo();
    return wrap_CurrencyPluralInfo(cpi->clone(), T_OWNED);
}

static PyObject *t_decimalformat_setCurrencyPluralInfo(t_decimalformat *self,
                                                       PyObject *arg)
{
    CurrencyPluralInfo *cpi;

    if (!parseArg(arg, "P", TYPE_CLASSID(CurrencyPluralInfo), &cpi))
    {
        self->object->adoptCurrencyPluralInfo(cpi->clone());
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setCurrencyPluralInfo", arg);
}

#endif


static PyObject *t_decimalformat_str(t_decimalformat *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)

/* CompactDecimalFormat */

static PyObject *t_compactdecimalformat_createInstance(PyTypeObject *type,
                                                       PyObject *args)
{
    CompactDecimalFormat *format;
    Locale *locale;
    UNumberCompactStyle style;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Pi", TYPE_CLASSID(Locale), &locale, &style))
        {
            STATUS_CALL(format = CompactDecimalFormat::createInstance(
                *locale, style, status));
            return wrap_CompactDecimalFormat(format, T_OWNED);
        }
        break;
    }
            
    return PyErr_SetArgsError(type, "createInstance", args);
}

#endif

/* RuleBasedNumberFormat */

static int t_rulebasednumberformat_init(t_rulebasednumberformat *self,
                                        PyObject *args, PyObject *kwds)
{
    UnicodeString *u, *v;
    UnicodeString _u, _v;
    Locale *locale;
    RuleBasedNumberFormat *rbf;
#if U_HAVE_RBNF
    URBNFRuleSetTag tag;
#endif

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_PARSER_CALL(rbf = new RuleBasedNumberFormat(*u, parseError, status));
            self->object = rbf;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
        {
            INT_STATUS_PARSER_CALL(rbf = new RuleBasedNumberFormat(*u, *v, parseError, status));
            self->object = rbf;
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale),
                       &u, &_u, &locale))
        {
            INT_STATUS_PARSER_CALL(rbf = new RuleBasedNumberFormat(*u, *locale, parseError, status));
            self->object = rbf;
            self->flags = T_OWNED;
            break;
        }
#if U_HAVE_RBNF
        if (!parseArgs(args, "iP", TYPE_CLASSID(Locale), &tag, &locale))
        {
            INT_STATUS_CALL(rbf = new RuleBasedNumberFormat(tag, *locale, status));
            self->object = rbf;
            self->flags = T_OWNED;
            break;
        }
#endif
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "SSP", TYPE_CLASSID(Locale),
                       &u, &_u, &v, &_v, &locale))
        {
            INT_STATUS_PARSER_CALL(rbf = new RuleBasedNumberFormat(*u, *v, *locale, parseError, status));
            self->object = rbf;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}    

static PyObject *t_rulebasednumberformat_getRules(t_rulebasednumberformat *self,
                                                  PyObject *args)
{
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 0:
      {
          UnicodeString u = self->object->getRules();
          return PyUnicode_FromUnicodeString(&u);
      }
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            u->setTo(self->object->getRules());
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getRules", args);
}

static PyObject *t_rulebasednumberformat_getNumberOfRuleSetNames(t_rulebasednumberformat *self)
{
    return PyInt_FromLong(self->object->getNumberOfRuleSetNames());
}

static PyObject *t_rulebasednumberformat_getRuleSetName(t_rulebasednumberformat *self, PyObject *args)
{
    int index;
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &index))
        {
            UnicodeString u = self->object->getRuleSetName(index);
            return PyUnicode_FromUnicodeString(&u);
        }
      case 2:
        if (!parseArgs(args, "iU", &index, &u))
        {
            u->setTo(self->object->getRuleSetName(index));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getRuleSetName", args);
}

static PyObject *t_rulebasednumberformat_getNumberOfRuleSetDisplayNameLocales(t_rulebasednumberformat *self)
{
    return PyInt_FromLong(self->object->getNumberOfRuleSetDisplayNameLocales());
}

static PyObject *t_rulebasednumberformat_getRuleSetDisplayName(t_rulebasednumberformat *self, PyObject *args)
{
    int index;
    Locale *locale;
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &index))
        {
            UnicodeString u = self->object->getRuleSetDisplayName(index);
            return PyUnicode_FromUnicodeString(&u);
        }
      case 2:
        if (!parseArgs(args, "iP", TYPE_CLASSID(Locale),
                       &index, &locale))
        {
            UnicodeString u = self->object->getRuleSetDisplayName(index, *locale);
            return PyUnicode_FromUnicodeString(&u);
        }
        if (!parseArgs(args, "iU", &index, &u))
        {
            u->setTo(self->object->getRuleSetDisplayName(index));
            Py_RETURN_ARG(args, 1);
        }
        break;
      case 3:
        if (!parseArgs(args, "iPU", TYPE_CLASSID(Locale),
                       &index, &locale, &u))
        {
            u->setTo(self->object->getRuleSetDisplayName(index, *locale));
            Py_RETURN_ARG(args, 2);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getRuleSetDisplayName", args);
}

static PyObject *t_rulebasednumberformat_format(t_rulebasednumberformat *self,
                                                PyObject *args)
{
    UnicodeString *u, *v;
    UnicodeString _u, _v;
    double d;
    int i;
    PY_LONG_LONG l;
    FieldPosition *fp;

    switch (PyTuple_Size(args)) {
      case 3:
        if (!parseArgs(args, "dSP", TYPE_CLASSID(FieldPosition),
                       &d, &u, &_u, &fp))
        {
            STATUS_CALL(self->object->format(d, *u, _v, *fp, status));
            return PyUnicode_FromUnicodeString(&_v);
        }
        if (!parseArgs(args, "iSP", TYPE_CLASSID(FieldPosition),
                       &i, &u, &_u, &fp))
        {
            STATUS_CALL(self->object->format(i, *u, _v, *fp, status));
            return PyUnicode_FromUnicodeString(&_v);
        }
        if (!parseArgs(args, "LSP", TYPE_CLASSID(FieldPosition),
                       &l, &u, &_u, &fp))
        {
          STATUS_CALL(self->object->format((int64_t) l, *u, _v, *fp, status));
            return PyUnicode_FromUnicodeString(&_v);
        }
      case 4:
        if (!parseArgs(args, "dSUP", TYPE_CLASSID(FieldPosition),
                       &d, &u, &_u, &v, &fp))
        {
            STATUS_CALL(self->object->format(d, *u, *v, *fp, status));
            Py_RETURN_ARG(args, 2);
        }
        if (!parseArgs(args, "iSUP", TYPE_CLASSID(FieldPosition),
                       &i, &u, &_u, &v, &fp))
        {
            STATUS_CALL(self->object->format(i, *u, *v, *fp, status));
            Py_RETURN_ARG(args, 2);
        }
        if (!parseArgs(args, "LSUP", TYPE_CLASSID(FieldPosition),
                       &l, &u, &_u, &v, &fp))
        {
          STATUS_CALL(self->object->format((int64_t) l, *u, *v, *fp, status));
            Py_RETURN_ARG(args, 2);
        }
        break;
    }

    return t_numberformat_format((t_numberformat *) self, args);
}

static PyObject *t_rulebasednumberformat_isLenient(t_rulebasednumberformat *self)
{
    int b = self->object->isLenient();
    Py_RETURN_BOOL(b);
}

static PyObject *t_rulebasednumberformat_setLenient(t_rulebasednumberformat *self, PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setLenient(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLenient", arg);
}


static PyObject *t_rulebasednumberformat_getDefaultRuleSetName(t_rulebasednumberformat *self, PyObject *args)
{
    UnicodeString *u;

    switch (PyTuple_Size(args)) {
      case 0:
      {
          UnicodeString _u = self->object->getDefaultRuleSetName();
          return PyUnicode_FromUnicodeString(&_u);
      }
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            u->setTo(self->object->getDefaultRuleSetName());
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDefaultRuleSetName", args);
}

static PyObject *t_rulebasednumberformat_setDefaultRuleSet(t_rulebasednumberformat *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        /* transient */        
        STATUS_CALL(self->object->setDefaultRuleSet(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDefaultRuleSet", arg);
}

static PyObject *t_rulebasednumberformat_str(t_rulebasednumberformat *self)
{
    UnicodeString u = self->object->getRules();
    return PyUnicode_FromUnicodeString(&u);
}


/* ChoiceFormat */

static int t_choiceformat_init(t_choiceformat *self,
                               PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    UnicodeString _u;
    ChoiceFormat *cf;
    double *limits;
    int limitCount;
    UBool *closures;
    int closureCount;
    UnicodeString *formats;
    int formatCount;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(cf = new ChoiceFormat(*u, status));
            self->object = cf;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "FT",
                       &limits, &limitCount, &formats, &formatCount))
        {
            cf = new ChoiceFormat(limits, formats, limitCount);
            delete[] limits;
            delete[] formats;
                
            self->object = cf;
            self->flags = T_OWNED;
            break;
        }
      case 3:
        if (!parseArgs(args, "FGT",
                       &limits, &limitCount,
                       &closures, &closureCount,
                       &formats, &formatCount))
        {
            cf = new ChoiceFormat(limits, closures, formats, limitCount);
            delete[] limits;
            delete[] closures;
            delete[] formats;
                
            self->object = cf;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}


static PyObject *t_choiceformat_toPattern(t_choiceformat *self,
                                          PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toPattern(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->toPattern(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toPattern", args);
}

static PyObject *t_choiceformat_applyPattern(t_choiceformat *self,
                                             PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyPattern(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_choiceformat_setChoices(t_choiceformat *self,
                                           PyObject *args)
{
    double *limits;
    int limitCount;
    UBool *closures;
    int closureCount;
    UnicodeString *formats;
    int formatCount;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "FT",
                       &limits, &limitCount, &formats, &formatCount))
        {
            self->object->setChoices(limits, formats, limitCount);
            delete[] limits;
            delete[] formats;

            Py_RETURN_NONE;
        }
        break;
      case 3:
        if (!parseArgs(args, "FGT",
                       &limits, &limitCount,
                       &closures, &closureCount,
                       &formats, &formatCount))
        {
            self->object->setChoices(limits, closures, formats, limitCount);
            delete[] limits;
            delete[] closures;
            delete[] formats;

            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "setChoices", args);
}

static PyObject *fromDoubleArray(double *array, int len, int dispose)
{
    PyObject *list = PyList_New(len);
    
    for (int i = 0; i < len; i++)
        PyList_SET_ITEM(list, i, PyFloat_FromDouble(array[i]));

    if (dispose)
        delete array;

    return list;
}

static PyObject *fromUBoolArray(UBool *array, int len, int dispose)
{
    PyObject *list = PyList_New(len);
    
    for (int i = 0; i < len; i++) {
        PyObject *obj = array[i] ? Py_True : Py_False;
       
        Py_INCREF(obj); 
        PyList_SET_ITEM(list, i, obj);
    }

    if (dispose)
        delete array;

    return list;
}

static PyObject *fromUnicodeStringArray(UnicodeString *array,
                                        int len, int dispose)
{
    PyObject *list = PyList_New(len);
    
    for (int i = 0; i < len; i++)
        PyList_SET_ITEM(list, i, PyUnicode_FromUnicodeString(array + i));

    if (dispose)
        delete array;

    return list;
}

static PyObject *t_choiceformat_getLimits(t_choiceformat *self)
{
    int len;
    const double *array = self->object->getLimits(len);
    
    return fromDoubleArray((double *) array, len, 0);
}

static PyObject *t_choiceformat_getClosures(t_choiceformat *self)
{
    int len;
    const UBool *closures = self->object->getClosures(len);
    
    return fromUBoolArray((UBool *) closures, len, 0);
}

static PyObject *t_choiceformat_getFormats(t_choiceformat *self)
{
    int len;
    const UnicodeString *formats = self->object->getFormats(len);
    
    return fromUnicodeStringArray((UnicodeString *) formats, len, 0);
}

static PyObject *t_choiceformat_format(t_choiceformat *self, PyObject *args)
{
    Formattable *f;
    int len;
    UnicodeString *u;
    UnicodeString _u;
    FieldPosition *fp;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "RP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(FieldPosition),
                       &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray, &fp))
        {
            STATUS_CALL(
                {
                    self->object->format(f, len, _u, *fp, status);
                    delete[] f;
                });

            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "RUP",
                       TYPE_CLASSID(Formattable),
                       &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray, &u, &fp))
        {
            STATUS_CALL(
                {
                    self->object->format(f, len, *u, *fp, status);
                    delete[] f;
                });

            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return t_numberformat_format((t_numberformat *) self, args);
}

static PyObject *t_choiceformat_str(t_choiceformat *self)
{
    UnicodeString u; self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}


void _init_numberformat(PyObject *m)
{
    DecimalFormatSymbolsType_.tp_richcompare =
        (richcmpfunc) t_decimalformatsymbols_richcmp;
#if U_ICU_VERSION_HEX >= 0x04020000
    CurrencyPluralInfoType_.tp_richcompare =
        (richcmpfunc) t_currencypluralinfo_richcmp;
#endif
    DecimalFormatType_.tp_str = (reprfunc) t_decimalformat_str;
    RuleBasedNumberFormatType_.tp_str = (reprfunc) t_rulebasednumberformat_str;
    ChoiceFormatType_.tp_str = (reprfunc) t_choiceformat_str;

    REGISTER_TYPE(DecimalFormatSymbols, m);
    REGISTER_TYPE(NumberFormat, m);
#if U_ICU_VERSION_HEX >= 0x04020000
    REGISTER_TYPE(CurrencyPluralInfo, m);
#endif
    REGISTER_TYPE(DecimalFormat, m);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    REGISTER_TYPE(CompactDecimalFormat, m);
#endif
    REGISTER_TYPE(RuleBasedNumberFormat, m);
    REGISTER_TYPE(ChoiceFormat, m);

    INSTALL_STATIC_INT(DecimalFormatSymbols, kDecimalSeparatorSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kGroupingSeparatorSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kPatternSeparatorSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kPercentSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kZeroDigitSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kDigitSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kMinusSignSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kPlusSignSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kCurrencySymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kIntlCurrencySymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kMonetarySeparatorSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kExponentialSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kPerMillSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kPadEscapeSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kInfinitySymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kNaNSymbol);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kSignificantDigitSymbol);

#if U_ICU_VERSION_HEX >= 0x04020000 && U_ICU_VERSION_HEX < 0x04080000
    INSTALL_STATIC_INT(DecimalFormatSymbols, kCurrencyMatch);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kSurroundingMatch);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kInsert);
    INSTALL_STATIC_INT(DecimalFormatSymbols, kCurrencySpacingCount);
#endif

#if U_HAVE_RBNF
    INSTALL_CONSTANTS_TYPE(URBNFRuleSetTag, m);
    INSTALL_ENUM(URBNFRuleSetTag, "SPELLOUT", URBNF_SPELLOUT);
    INSTALL_ENUM(URBNFRuleSetTag, "ORDINAL", URBNF_ORDINAL);
    INSTALL_ENUM(URBNFRuleSetTag, "DURATION", URBNF_DURATION);
    INSTALL_ENUM(URBNFRuleSetTag, "NUMBERING_SYSTEM", URBNF_NUMBERING_SYSTEM);
#endif

#if U_ICU_VERSION_HEX >= 0x04080000
    INSTALL_CONSTANTS_TYPE(UCurrencySpacing, m);
    INSTALL_ENUM(UCurrencySpacing, "MATCH", UNUM_CURRENCY_MATCH);
    INSTALL_ENUM(UCurrencySpacing, "SURROUNDING_MATCH", UNUM_CURRENCY_SURROUNDING_MATCH);
    INSTALL_ENUM(UCurrencySpacing, "INSERT", UNUM_CURRENCY_INSERT);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_CONSTANTS_TYPE(UNumberCompactStyle, m);
    INSTALL_ENUM(UNumberCompactStyle, "SHORT", UNUM_SHORT);
    INSTALL_ENUM(UNumberCompactStyle, "LONG", UNUM_LONG);
#endif

    INSTALL_STATIC_INT(NumberFormat, kIntegerField);
    INSTALL_STATIC_INT(NumberFormat, kFractionField);
    INSTALL_STATIC_INT(NumberFormat, INTEGER_FIELD);
    INSTALL_STATIC_INT(NumberFormat, FRACTION_FIELD);

    INSTALL_STATIC_INT(DecimalFormat, kRoundCeiling);
    INSTALL_STATIC_INT(DecimalFormat, kRoundFloor);
    INSTALL_STATIC_INT(DecimalFormat, kRoundDown);
    INSTALL_STATIC_INT(DecimalFormat, kRoundUp);
    INSTALL_STATIC_INT(DecimalFormat, kRoundHalfEven);
    INSTALL_STATIC_INT(DecimalFormat, kRoundHalfDown);
    INSTALL_STATIC_INT(DecimalFormat, kRoundHalfUp);

    INSTALL_STATIC_INT(DecimalFormat, kPadBeforePrefix);
    INSTALL_STATIC_INT(DecimalFormat, kPadAfterPrefix);
    INSTALL_STATIC_INT(DecimalFormat, kPadBeforeSuffix);
    INSTALL_STATIC_INT(DecimalFormat, kPadAfterSuffix);
}
