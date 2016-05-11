/* ====================================================================
 * Copyright (c) 2004-2015 Open Source Applications Foundation.
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
#include "calendar.h"
#include "numberformat.h"
#include "dateformat.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UDateTimePatternConflict);
DECLARE_CONSTANTS_TYPE(UDateTimePatternField);

#if U_ICU_VERSION_HEX >= 0x04040000
DECLARE_CONSTANTS_TYPE(UDateTimePatternMatchOptions);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
DECLARE_CONSTANTS_TYPE(UDateRelativeDateTimeFormatterStyle);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
DECLARE_CONSTANTS_TYPE(UDisplayContext);
DECLARE_CONSTANTS_TYPE(UDisplayContextType);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
DECLARE_CONSTANTS_TYPE(UDateDirection);
DECLARE_CONSTANTS_TYPE(UDateAbsoluteUnit);
DECLARE_CONSTANTS_TYPE(UDateRelativeUnit);
DECLARE_CONSTANTS_TYPE(UDateFormatBooleanAttribute);
#endif

/* DateFormatSymbols */

class t_dateformatsymbols : public _wrapper {
public:
    DateFormatSymbols *object;
};

static int t_dateformatsymbols_init(t_dateformatsymbols *self,
                                    PyObject *args, PyObject *kwds);
static PyObject *t_dateformatsymbols_getEras(t_dateformatsymbols *self);
static PyObject *t_dateformatsymbols_setEras(t_dateformatsymbols *self, PyObject *arg);
static PyObject *t_dateformatsymbols_getMonths(t_dateformatsymbols *self,
                                               PyObject *args);
static PyObject *t_dateformatsymbols_setMonths(t_dateformatsymbols *self,
                                               PyObject *arg);
static PyObject *t_dateformatsymbols_getShortMonths(t_dateformatsymbols *self);
static PyObject *t_dateformatsymbols_setShortMonths(t_dateformatsymbols *self,
                                                    PyObject *arg);
static PyObject *t_dateformatsymbols_getWeekdays(t_dateformatsymbols *self,
                                                 PyObject *args);
static PyObject *t_dateformatsymbols_setWeekdays(t_dateformatsymbols *self,
                                                 PyObject *arg);
static PyObject *t_dateformatsymbols_getShortWeekdays(t_dateformatsymbols *self);
static PyObject *t_dateformatsymbols_setShortWeekdays(t_dateformatsymbols *self,
                                                      PyObject *arg);
static PyObject *t_dateformatsymbols_getAmPmStrings(t_dateformatsymbols *self);
static PyObject *t_dateformatsymbols_setAmPmStrings(t_dateformatsymbols *self,
                                                    PyObject *arg);
static PyObject *t_dateformatsymbols_getLocalPatternChars(t_dateformatsymbols *self, PyObject *args);
static PyObject *t_dateformatsymbols_setLocalPatternChars(t_dateformatsymbols *self, PyObject *arg);
static PyObject *t_dateformatsymbols_getLocale(t_dateformatsymbols *self,
                                               PyObject *args);

static PyMethodDef t_dateformatsymbols_methods[] = {
    DECLARE_METHOD(t_dateformatsymbols, getEras, METH_NOARGS),
    DECLARE_METHOD(t_dateformatsymbols, setEras, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getMonths, METH_VARARGS),
    DECLARE_METHOD(t_dateformatsymbols, setMonths, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getShortMonths, METH_NOARGS),
    DECLARE_METHOD(t_dateformatsymbols, setShortMonths, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getWeekdays, METH_VARARGS),
    DECLARE_METHOD(t_dateformatsymbols, setWeekdays, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getShortWeekdays, METH_NOARGS),
    DECLARE_METHOD(t_dateformatsymbols, setShortWeekdays, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getAmPmStrings, METH_NOARGS),
    DECLARE_METHOD(t_dateformatsymbols, setAmPmStrings, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getLocalPatternChars, METH_VARARGS),
    DECLARE_METHOD(t_dateformatsymbols, setLocalPatternChars, METH_O),
    DECLARE_METHOD(t_dateformatsymbols, getLocale, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateFormatSymbols, t_dateformatsymbols, UObject,
             DateFormatSymbols, t_dateformatsymbols_init, NULL);

/* DateFormat */

class t_dateformat : public _wrapper {
public:
    DateFormat *object;
};

static PyObject *t_dateformat_isLenient(t_dateformat *self);
static PyObject *t_dateformat_setLenient(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_format(t_dateformat *self, PyObject *args);
static PyObject *t_dateformat_parse(t_dateformat *self, PyObject *args);
static PyObject *t_dateformat_getCalendar(t_dateformat *self);
static PyObject *t_dateformat_setCalendar(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_getNumberFormat(t_dateformat *self);
static PyObject *t_dateformat_setNumberFormat(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_getTimeZone(t_dateformat *self);
static PyObject *t_dateformat_setTimeZone(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_createInstance(PyTypeObject *type);
static PyObject *t_dateformat_createTimeInstance(PyTypeObject *type,
                                                 PyObject *args);
static PyObject *t_dateformat_createDateInstance(PyTypeObject *type,
                                                 PyObject *args);
static PyObject *t_dateformat_createDateTimeInstance(PyTypeObject *type,
                                                     PyObject *args);
static PyObject *t_dateformat_getAvailableLocales(PyTypeObject *type);
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
static PyObject *t_dateformat_setContext(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_getContext(t_dateformat *self, PyObject *arg);
static PyObject *t_dateformat_setBooleanAttribute(t_dateformat *self,
                                                  PyObject *args);
static PyObject *t_dateformat_getBooleanAttribute(t_dateformat *self,
                                                  PyObject *arg);
#endif

static PyMethodDef t_dateformat_methods[] = {
    DECLARE_METHOD(t_dateformat, isLenient, METH_NOARGS),
    DECLARE_METHOD(t_dateformat, setLenient, METH_O),
    DECLARE_METHOD(t_dateformat, format, METH_VARARGS),
    DECLARE_METHOD(t_dateformat, parse, METH_VARARGS),
    DECLARE_METHOD(t_dateformat, getCalendar, METH_NOARGS),
    DECLARE_METHOD(t_dateformat, setCalendar, METH_O),
    DECLARE_METHOD(t_dateformat, getNumberFormat, METH_NOARGS),
    DECLARE_METHOD(t_dateformat, setNumberFormat, METH_O),
    DECLARE_METHOD(t_dateformat, getTimeZone, METH_NOARGS),
    DECLARE_METHOD(t_dateformat, setTimeZone, METH_O),
    DECLARE_METHOD(t_dateformat, createInstance, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_dateformat, createTimeInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_dateformat, createDateInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_dateformat, createDateTimeInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_dateformat, getAvailableLocales, METH_NOARGS | METH_CLASS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    DECLARE_METHOD(t_dateformat, setContext, METH_O),
    DECLARE_METHOD(t_dateformat, getContext, METH_O),
    DECLARE_METHOD(t_dateformat, setBooleanAttribute, METH_VARARGS),
    DECLARE_METHOD(t_dateformat, getBooleanAttribute, METH_O),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateFormat, t_dateformat, Format, DateFormat, abstract_init, NULL);

/* SimpleDateFormat */

class t_simpledateformat : public _wrapper {
public:
    SimpleDateFormat *object;
};

static int t_simpledateformat_init(t_simpledateformat *self,
                                   PyObject *args, PyObject *kwds);
static PyObject *t_simpledateformat_toPattern(t_simpledateformat *self,
                                              PyObject *args);
static PyObject *t_simpledateformat_toLocalizedPattern(t_simpledateformat *self,
                                                       PyObject *args);
static PyObject *t_simpledateformat_applyPattern(t_simpledateformat *self,
                                                 PyObject *arg);
static PyObject *t_simpledateformat_applyLocalizedPattern(t_simpledateformat *self, PyObject *arg);
static PyObject *t_simpledateformat_get2DigitYearStart(t_simpledateformat *self);
static PyObject *t_simpledateformat_set2DigitYearStart(t_simpledateformat *self,
                                                       PyObject *arg);
static PyObject *t_simpledateformat_getDateFormatSymbols(t_simpledateformat *self);
static PyObject *t_simpledateformat_setDateFormatSymbols(t_simpledateformat *self,
                                                         PyObject *arg);

static PyMethodDef t_simpledateformat_methods[] = {
    DECLARE_METHOD(t_simpledateformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_simpledateformat, toLocalizedPattern, METH_VARARGS),
    DECLARE_METHOD(t_simpledateformat, applyPattern, METH_O),
    DECLARE_METHOD(t_simpledateformat, applyLocalizedPattern, METH_O),
    DECLARE_METHOD(t_simpledateformat, get2DigitYearStart, METH_NOARGS),
    DECLARE_METHOD(t_simpledateformat, set2DigitYearStart, METH_O),
    DECLARE_METHOD(t_simpledateformat, getDateFormatSymbols, METH_NOARGS),
    DECLARE_METHOD(t_simpledateformat, setDateFormatSymbols, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(SimpleDateFormat, t_simpledateformat, DateFormat,
             SimpleDateFormat, t_simpledateformat_init, NULL);

PyObject *wrap_DateFormat(DateFormat *format)
{
    RETURN_WRAPPED_IF_ISINSTANCE(format, SimpleDateFormat);
    return wrap_DateFormat(format, T_OWNED);
}

/* DateTimePatternGenerator */

class t_datetimepatterngenerator : public _wrapper {
public:
    DateTimePatternGenerator *object;
};

static PyObject *t_datetimepatterngenerator_createEmptyInstance(
    PyTypeObject *type);
static PyObject *t_datetimepatterngenerator_createInstance(
    PyTypeObject *type, PyObject *args);
static PyObject *t_datetimepatterngenerator_getSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_getBaseSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_addPattern(
    t_datetimepatterngenerator *self, PyObject *args);
static PyObject *t_datetimepatterngenerator_getBestPattern(
    t_datetimepatterngenerator *self, PyObject *args);
static PyObject *t_datetimepatterngenerator_setAppendItemFormat(
    t_datetimepatterngenerator *self, PyObject *args);
static PyObject *t_datetimepatterngenerator_setAppendItemName(
    t_datetimepatterngenerator *self, PyObject *args);
static PyObject *t_datetimepatterngenerator_getAppendItemFormat(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_getAppendItemName(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_replaceFieldTypes(
    t_datetimepatterngenerator *self, PyObject *args);
static PyObject *t_datetimepatterngenerator_getSkeletons(
    t_datetimepatterngenerator *self);
static PyObject *t_datetimepatterngenerator_getBaseSkeletons(
    t_datetimepatterngenerator *self);
static PyObject *t_datetimepatterngenerator_getRedundants(
    t_datetimepatterngenerator *self);
static PyObject *t_datetimepatterngenerator_getPatternForSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_setDecimal(
    t_datetimepatterngenerator *self, PyObject *arg);
static PyObject *t_datetimepatterngenerator_getDecimal(
    t_datetimepatterngenerator *self);
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
static PyObject *t_datetimepatterngenerator_staticGetSkeleton(
    PyTypeObject *type, PyObject *arg);
static PyObject *t_datetimepatterngenerator_staticGetBaseSkeleton(
    PyTypeObject *type, PyObject *arg);
#endif

static PyMethodDef t_datetimepatterngenerator_methods[] = {
    DECLARE_METHOD(t_datetimepatterngenerator, createEmptyInstance,
                   METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_datetimepatterngenerator, createInstance,
                   METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_datetimepatterngenerator, getSkeleton, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, getBaseSkeleton, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, addPattern, METH_VARARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getBestPattern, METH_VARARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, setAppendItemFormat, METH_VARARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, setAppendItemName, METH_VARARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getAppendItemFormat, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, getAppendItemName, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, replaceFieldTypes, METH_VARARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getSkeletons, METH_NOARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getBaseSkeletons, METH_NOARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getRedundants, METH_NOARGS),
    DECLARE_METHOD(t_datetimepatterngenerator, getPatternForSkeleton, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, setDecimal, METH_O),
    DECLARE_METHOD(t_datetimepatterngenerator, getDecimal, METH_NOARGS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
    DECLARE_METHOD(t_datetimepatterngenerator, staticGetSkeleton,
                   METH_O | METH_CLASS),
    DECLARE_METHOD(t_datetimepatterngenerator, staticGetBaseSkeleton,
                   METH_O | METH_CLASS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateTimePatternGenerator, t_datetimepatterngenerator,
             UObject, DateTimePatternGenerator, abstract_init, NULL);

#if U_ICU_VERSION_HEX >= 0x04000000

/* DateInterval */

class t_dateinterval : public _wrapper {
public:
    DateInterval *object;
};

static int t_dateinterval_init(t_dateinterval *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_dateinterval_getFromDate(t_dateinterval *self);
static PyObject *t_dateinterval_getToDate(t_dateinterval *self);

static PyMethodDef t_dateinterval_methods[] = {
    DECLARE_METHOD(t_dateinterval, getFromDate, METH_NOARGS),
    DECLARE_METHOD(t_dateinterval, getToDate, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateInterval, t_dateinterval, UObject, DateInterval,
             t_dateinterval_init, NULL);

/* DateIntervalInfo */

class t_dateintervalinfo : public _wrapper {
public:
    DateIntervalInfo *object;
};

static int t_dateintervalinfo_init(t_dateintervalinfo *self,
                                   PyObject *args, PyObject *kwds);
static PyObject *t_dateintervalinfo_getDefaultOrder(t_dateintervalinfo *self);
static PyObject *t_dateintervalinfo_setIntervalPattern(t_dateintervalinfo *self,
                                                       PyObject *args);
static PyObject *t_dateintervalinfo_getIntervalPattern(t_dateintervalinfo *self,
                                                       PyObject *args);
static PyObject *t_dateintervalinfo_setFallbackIntervalPattern(t_dateintervalinfo *self, PyObject *arg);
static PyObject *t_dateintervalinfo_getFallbackIntervalPattern(t_dateintervalinfo *self, PyObject *args);

static PyMethodDef t_dateintervalinfo_methods[] = {
    DECLARE_METHOD(t_dateintervalinfo, getDefaultOrder, METH_NOARGS),
    DECLARE_METHOD(t_dateintervalinfo, setIntervalPattern, METH_VARARGS),
    DECLARE_METHOD(t_dateintervalinfo, getIntervalPattern, METH_VARARGS),
    DECLARE_METHOD(t_dateintervalinfo, setFallbackIntervalPattern, METH_O),
    DECLARE_METHOD(t_dateintervalinfo, getFallbackIntervalPattern, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateIntervalInfo, t_dateintervalinfo, UObject, DateIntervalInfo,
             t_dateintervalinfo_init, NULL);

/* DateIntervalFormat */

static DateIntervalFormat *DateInterval_format;

class t_dateintervalformat : public _wrapper {
public:
    DateIntervalFormat *object;
};

static PyObject *t_dateintervalformat_format(t_dateintervalformat *self,
                                             PyObject *args);
static PyObject *t_dateintervalformat_getDateIntervalInfo(t_dateintervalformat *self);
static PyObject *t_dateintervalformat_setDateIntervalInfo(t_dateintervalformat *self, PyObject *arg);
static PyObject *t_dateintervalformat_getDateFormat(t_dateintervalformat *self);
static PyObject *t_dateintervalformat_parseObject(t_dateintervalformat *self,
                                                  PyObject *args);
static PyObject *t_dateintervalformat_createInstance(PyTypeObject *type,
                                                     PyObject *args);

static PyMethodDef t_dateintervalformat_methods[] = {
    DECLARE_METHOD(t_dateintervalformat, format, METH_VARARGS),
    DECLARE_METHOD(t_dateintervalformat, getDateIntervalInfo, METH_NOARGS),
    DECLARE_METHOD(t_dateintervalformat, setDateIntervalInfo, METH_O),
    DECLARE_METHOD(t_dateintervalformat, getDateFormat, METH_NOARGS),
    DECLARE_METHOD(t_dateintervalformat, parseObject, METH_VARARGS),
    DECLARE_METHOD(t_dateintervalformat, createInstance, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DateIntervalFormat, t_dateintervalformat, Format,
             DateIntervalFormat, abstract_init, NULL);

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

/* RelativeDateTimeFormatter */

class t_relativedatetimeformatter : public _wrapper {
public:
    RelativeDateTimeFormatter *object;
};

static int t_relativedatetimeformatter_init(t_relativedatetimeformatter *self,
                                            PyObject *args, PyObject *kwds);
static PyObject *t_relativedatetimeformatter_format(
    t_relativedatetimeformatter *self, PyObject *args);
static PyObject *t_relativedatetimeformatter_combineDateAndTime(
    t_relativedatetimeformatter *self, PyObject *args);
static PyObject *t_relativedatetimeformatter_getNumberFormat(
    t_relativedatetimeformatter *self);
static PyObject *t_relativedatetimeformatter_getCapitalizationContext(
    t_relativedatetimeformatter *self);
static PyObject *t_relativedatetimeformatter_getFormatStyle(
    t_relativedatetimeformatter *self);

static PyMethodDef t_relativedatetimeformatter_methods[] = {
    DECLARE_METHOD(t_relativedatetimeformatter, format, METH_VARARGS),
    DECLARE_METHOD(t_relativedatetimeformatter, combineDateAndTime, METH_VARARGS),
    DECLARE_METHOD(t_relativedatetimeformatter, getNumberFormat, METH_NOARGS),
    DECLARE_METHOD(t_relativedatetimeformatter, getCapitalizationContext, METH_NOARGS),
    DECLARE_METHOD(t_relativedatetimeformatter, getFormatStyle, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(RelativeDateTimeFormatter, t_relativedatetimeformatter, UObject,
             RelativeDateTimeFormatter, t_relativedatetimeformatter_init, NULL);

#endif


/* DateFormatSymbols */

static int t_dateformatsymbols_init(t_dateformatsymbols *self,
                                    PyObject *args, PyObject *kwds)
{
    UnicodeString _u;
    Locale *locale;
    DateFormatSymbols *dfs;
    charsArg type;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(dfs = new DateFormatSymbols(status));
        self->object = dfs;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(dfs = new DateFormatSymbols(*locale, status));
            self->object = dfs;
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "n", &type))
        {
            INT_STATUS_CALL(dfs = new DateFormatSymbols(type, status));
            self->object = dfs;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "Pn", TYPE_CLASSID(Locale),
                       &locale, &type))
        {
            INT_STATUS_CALL(dfs = new DateFormatSymbols(*locale, type, status));
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

static PyObject *fromUnicodeStringArray(const UnicodeString *strings,
                                        int len, int dispose)
{
    PyObject *list = PyList_New(len);
    
    for (int i = 0; i < len; i++) {
        UnicodeString *u = (UnicodeString *) (strings + i);
        PyList_SET_ITEM(list, i, PyUnicode_FromUnicodeString(u));
    }

    if (dispose)
        delete strings;

    return list;
}

static PyObject *t_dateformatsymbols_getEras(t_dateformatsymbols *self)
{
    int len;
    const UnicodeString *eras = self->object->getEras(len);

    return fromUnicodeStringArray(eras, len, 0);
}

static PyObject *t_dateformatsymbols_setEras(t_dateformatsymbols *self,
                                             PyObject *arg)
{
    UnicodeString *eras;
    int len;

    if (!parseArg(arg, "T", &eras, &len))
    {
        self->object->setEras(eras, len); /* copied */
        delete[] eras; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setEras", arg);
}

static PyObject *t_dateformatsymbols_getMonths(t_dateformatsymbols *self,
                                               PyObject *args)
{
    int len;
    const UnicodeString *months;
    DateFormatSymbols::DtContextType context;
    DateFormatSymbols::DtWidthType width;

    switch (PyTuple_Size(args)) {
      case 0:
        months = self->object->getMonths(len);
        return fromUnicodeStringArray(months, len, 0);
      case 2:
        if (!parseArgs(args, "ii", &context, &width))
        {
            months = self->object->getMonths(len, context, width);
            return fromUnicodeStringArray(months, len, 0);
        }
        break;
    }
            
    return PyErr_SetArgsError((PyObject *) self, "getMonths", args);
}

static PyObject *t_dateformatsymbols_setMonths(t_dateformatsymbols *self,
                                               PyObject *arg)
{
    UnicodeString *months;
    int len;

    if (!parseArg(arg, "T", &months, &len))
    {
        self->object->setMonths(months, len); /* copied */
        delete[] months; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMonths", arg);
}

static PyObject *t_dateformatsymbols_getShortMonths(t_dateformatsymbols *self)
{
    int len;
    const UnicodeString *months = self->object->getShortMonths(len);

    return fromUnicodeStringArray(months, len, 0);
}

static PyObject *t_dateformatsymbols_setShortMonths(t_dateformatsymbols *self,
                                                    PyObject *arg)
{
    UnicodeString *months;
    int len;

    if (!parseArg(arg, "T", &months, &len))
    {
        self->object->setShortMonths(months, len); /* copied */
        delete[] months; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setShortMonths", arg);
}

static PyObject *t_dateformatsymbols_getWeekdays(t_dateformatsymbols *self,
                                                 PyObject *args)
{
    int len;
    const UnicodeString *weekdays;
    DateFormatSymbols::DtContextType context;
    DateFormatSymbols::DtWidthType width;

    switch (PyTuple_Size(args)) {
      case 0:
        weekdays = self->object->getWeekdays(len);
        return fromUnicodeStringArray(weekdays, len, 0);
      case 2:
        if (!parseArgs(args, "ii", &context, &width))
        {
            weekdays = self->object->getWeekdays(len, context, width);
            return fromUnicodeStringArray(weekdays, len, 0);
        }
        break;
    }
            
    return PyErr_SetArgsError((PyObject *) self, "getWeekdays", args);
}

static PyObject *t_dateformatsymbols_setWeekdays(t_dateformatsymbols *self,
                                                 PyObject *arg)
{
    UnicodeString *weekdays;
    int len;

    if (!parseArg(arg, "T", &weekdays, &len))
    {
        self->object->setWeekdays(weekdays, len); /* copied */
        delete[] weekdays; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setWeekdays", arg);
}

static PyObject *t_dateformatsymbols_getShortWeekdays(t_dateformatsymbols *self)
{
    int len;
    const UnicodeString *months = self->object->getShortWeekdays(len);

    return fromUnicodeStringArray(months, len, 0);
}

static PyObject *t_dateformatsymbols_setShortWeekdays(t_dateformatsymbols *self,
                                                      PyObject *arg)
{
    UnicodeString *weekdays;
    int len;

    if (!parseArg(arg, "T", &weekdays, &len))
    {
        self->object->setShortWeekdays(weekdays, len); /* copied */
        delete[] weekdays; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setShortWeekdays", arg);
}

static PyObject *t_dateformatsymbols_getAmPmStrings(t_dateformatsymbols *self)
{
    int len;
    const UnicodeString *strings = self->object->getAmPmStrings(len);

    return fromUnicodeStringArray(strings, len, 0);
}

static PyObject *t_dateformatsymbols_setAmPmStrings(t_dateformatsymbols *self,
                                                    PyObject *arg)
{
    UnicodeString *strings;
    int len;

    if (!parseArg(arg, "T", &strings, &len))
    {
        self->object->setAmPmStrings(strings, len); /* copied */
        delete[] strings; /* dtfmtsym.cpp code duplicates it */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAmPmStrings", arg);
}

DEFINE_RICHCMP(DateFormatSymbols, t_dateformatsymbols);
        
static PyObject *t_dateformatsymbols_getLocalPatternChars(t_dateformatsymbols *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getLocalPatternChars(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getLocalPatternChars(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocalPatternChars", args);
}

static PyObject *t_dateformatsymbols_setLocalPatternChars(t_dateformatsymbols *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setLocalPatternChars(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLocalPatternChars", arg);
}

static PyObject *t_dateformatsymbols_getLocale(t_dateformatsymbols *self,
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


/* DateFormat */

static PyObject *t_dateformat_isLenient(t_dateformat *self)
{
    int b = self->object->isLenient();
    Py_RETURN_BOOL(b);
}

static PyObject *t_dateformat_setLenient(t_dateformat *self, PyObject *arg)
{
    int b;

    if (!parseArg(arg, "b", &b))
    {
        self->object->setLenient(b);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLenient", arg);
}

static PyObject *t_dateformat_format(t_dateformat *self, PyObject *args)
{
    UDate date;
    Calendar *calendar;
    UnicodeString *u;
    UnicodeString _u;
    FieldPosition *fp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "D", &date))
        {
            self->object->format(date, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "P", TYPE_ID(Calendar), &calendar))
        {
            FieldPosition fp0(0);

            self->object->format(*calendar, _u, fp0);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "DP", TYPE_CLASSID(FieldPosition),
                       &date, &fp))
        {
            self->object->format(date, _u, *fp);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "PP",
                       TYPE_ID(Calendar), TYPE_CLASSID(FieldPosition),
                       &calendar, &fp))
        {
            self->object->format(*calendar, _u, *fp);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "DU", &date, &u))
        {
            self->object->format(date, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
      case 3:
        if (!parseArgs(args, "DUP", TYPE_CLASSID(FieldPosition),
                       &date, &u, &fp))
        {
            self->object->format(date, *u, *fp);
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "PUP",
                       TYPE_ID(Calendar), TYPE_CLASSID(FieldPosition),
                       &calendar, &u, &fp))
        {
            self->object->format(*calendar, *u, *fp);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return t_format_format((t_format *) self, args);
}

static PyObject *t_dateformat_parse(t_dateformat *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    Calendar *calendar;
    ParsePosition *pp;
    UDate date;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(date = self->object->parse(*u, status));
            return PyFloat_FromDouble(date / 1000.0);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(ParsePosition),
                       &u, &_u, &pp))
        {
            pp->setErrorIndex(-1);
            STATUS_CALL(date = self->object->parse(*u, *pp));
            if (pp->getErrorIndex() == -1)
                Py_RETURN_NONE;
            return PyFloat_FromDouble(date / 1000.0);
        }
        break;
      case 3:
        if (!parseArgs(args, "SPP",
                       TYPE_ID(Calendar), TYPE_CLASSID(ParsePosition),
                       &u, &_u, &calendar, &pp))
        {
            pp->setErrorIndex(-1);
            STATUS_CALL(self->object->parse(*u, *calendar, *pp));
            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "parse", args);
}

static PyObject *t_dateformat_getCalendar(t_dateformat *self)
{
    return wrap_Calendar(self->object->getCalendar()->clone(), T_OWNED);
}

static PyObject *t_dateformat_setCalendar(t_dateformat *self, PyObject *arg)
{
    Calendar *calendar;

    if (!parseArg(arg, "P", TYPE_ID(Calendar), &calendar))
    {
        self->object->setCalendar(*calendar); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setCalendar", arg);
}

static PyObject *t_dateformat_getNumberFormat(t_dateformat *self)
{
    return wrap_NumberFormat((NumberFormat *) self->object->getNumberFormat()->clone(), T_OWNED);
}

static PyObject *t_dateformat_setNumberFormat(t_dateformat *self, PyObject *arg)
{
    NumberFormat *format;

    if (!parseArg(arg, "P", TYPE_CLASSID(NumberFormat), &format))
    {
        self->object->setNumberFormat(*format); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNumberFormat", arg);
}

static PyObject *t_dateformat_getTimeZone(t_dateformat *self)
{
    return wrap_TimeZone(self->object->getTimeZone());
}

static PyObject *t_dateformat_setTimeZone(t_dateformat *self, PyObject *arg)
{
    TimeZone *tz;

    if (!parseArg(arg, "P", TYPE_CLASSID(TimeZone), &tz))
    {
        self->object->setTimeZone(*tz); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setTimeZone", arg);
}

static PyObject *t_dateformat_createInstance(PyTypeObject *type)
{
    return wrap_DateFormat(DateFormat::createInstance());
}

static PyObject *t_dateformat_createTimeInstance(PyTypeObject *type,
                                                 PyObject *args)
{
    DateFormat::EStyle style;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &style))
            return wrap_DateFormat(DateFormat::createTimeInstance(style));
        break;
      case 2:
        if (!parseArgs(args, "iP", TYPE_CLASSID(Locale),
                       &style, &locale))
            return wrap_DateFormat(DateFormat::createTimeInstance(style, *locale));
        break;
    }

    return PyErr_SetArgsError(type, "createTimeInstance", args);
}

static PyObject *t_dateformat_createDateInstance(PyTypeObject *type,
                                                 PyObject *args)
{
    DateFormat::EStyle style;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &style))
            return wrap_DateFormat(DateFormat::createDateInstance(style));
        break;
      case 2:
        if (!parseArgs(args, "iP", TYPE_CLASSID(Locale),
                       &style, &locale))
            return wrap_DateFormat(DateFormat::createDateInstance(style, *locale));
        break;
    }

    return PyErr_SetArgsError(type, "createDateInstance", args);
}

static PyObject *t_dateformat_createDateTimeInstance(PyTypeObject *type,
                                                     PyObject *args)
{
    DateFormat::EStyle dateStyle, timeStyle;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &dateStyle))
            return wrap_DateFormat(DateFormat::createDateTimeInstance(dateStyle));
        break;
      case 2:
        if (!parseArgs(args, "ii", &dateStyle, &timeStyle))
            return wrap_DateFormat(DateFormat::createDateTimeInstance(dateStyle, timeStyle));
        break;
      case 3:
        if (!parseArgs(args, "iiP", TYPE_CLASSID(Locale),
                       &dateStyle, &timeStyle, &locale))
            return wrap_DateFormat(DateFormat::createDateTimeInstance(dateStyle, timeStyle, *locale));
        break;
    }

    return PyErr_SetArgsError(type, "createDateTimeInstance", args);
}

static PyObject *t_dateformat_getAvailableLocales(PyTypeObject *type)
{
    int count;
    const Locale *locales = DateFormat::getAvailableLocales(count);
    PyObject *dict = PyDict_New();

    for (int32_t i = 0; i < count; i++) {
        Locale *locale = (Locale *) locales + i;
        PyObject *obj = wrap_Locale(locale, 0);
        PyDict_SetItemString(dict, locale->getName(), obj);
        Py_DECREF(obj);
    }

    return dict;
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

static PyObject *t_dateformat_setContext(t_dateformat *self, PyObject *arg)
{
    int context;

    if (!parseArg(arg, "i", &context))
    {
        STATUS_CALL(self->object->setContext(
                        (UDisplayContext) context, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setContext", arg);
}

static PyObject *t_dateformat_getContext(t_dateformat *self, PyObject *arg)
{
    int context, type;

    if (!parseArg(arg, "i", &type))
    {
        STATUS_CALL(context = self->object->getContext(
                        (UDisplayContextType) type, status));

        return PyInt_FromLong(context);
    }

    return PyErr_SetArgsError((PyObject *) self, "getContext", arg);
}

static PyObject *t_dateformat_setBooleanAttribute(t_dateformat *self,
                                                  PyObject *args)
{
    int attribute, value;

    if (!parseArgs(args, "ii", &attribute, &value))
    {
        STATUS_CALL(self->object->setBooleanAttribute(
                        (UDateFormatBooleanAttribute) attribute,
                        (UBool) value, status));
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "setBooleanAttribute", args);
}

static PyObject *t_dateformat_getBooleanAttribute(t_dateformat *self,
                                                  PyObject *arg)
{
    int attribute;

    if (!parseArg(arg, "i", &attribute))
    {
        UBool result;

        STATUS_CALL(result = self->object->getBooleanAttribute(
                        (UDateFormatBooleanAttribute) attribute,
                        status));
        Py_RETURN_BOOL(result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getBooleanAttribute", arg);
}

#endif

/* SimpleDateFormat */

static int t_simpledateformat_init(t_simpledateformat *self,
                                   PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    UnicodeString _u;
    Locale *locale;
    DateFormatSymbols *dfs;
    SimpleDateFormat *format;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(format = new SimpleDateFormat(status));
        self->object = format;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(format = new SimpleDateFormat(*u, status));
            self->object = format;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale),
                       &u, &_u, &locale))
        {
            INT_STATUS_CALL(format = new SimpleDateFormat(*u, *locale, status));
            self->object = format;
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(DateFormatSymbols),
                       &u, &_u, &dfs))
        {
            INT_STATUS_CALL(format = new SimpleDateFormat(*u, *dfs, status));
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

static PyObject *t_simpledateformat_toPattern(t_simpledateformat *self,
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

static PyObject *t_simpledateformat_toLocalizedPattern(t_simpledateformat *self,
                                                       PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(self->object->toLocalizedPattern(_u, status));
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            STATUS_CALL(self->object->toLocalizedPattern(*u, status));
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toLocalizedPattern", args);
}

static PyObject *t_simpledateformat_applyPattern(t_simpledateformat *self,
                                                 PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->applyPattern(*u);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_simpledateformat_applyLocalizedPattern(t_simpledateformat *self, PyObject *arg)
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

static PyObject *t_simpledateformat_get2DigitYearStart(t_simpledateformat *self)
{
    UDate date;

    STATUS_CALL(date = self->object->get2DigitYearStart(status));
    return PyFloat_FromDouble(date / 1000.0);
}

static PyObject *t_simpledateformat_set2DigitYearStart(t_simpledateformat *self,
                                                       PyObject *arg)
{
    UDate date;

    if (!parseArg(arg, "D", &date))
    {
        STATUS_CALL(self->object->set2DigitYearStart(date, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "set2DigitYearStart", arg);
}

static PyObject *t_simpledateformat_getDateFormatSymbols(t_simpledateformat *self)
{
    return wrap_DateFormatSymbols(new DateFormatSymbols(*self->object->getDateFormatSymbols()), T_OWNED);
}

static PyObject *t_simpledateformat_setDateFormatSymbols(t_simpledateformat *self, PyObject *arg)
{
    DateFormatSymbols *dfs;

    if (!parseArg(arg, "P", TYPE_CLASSID(DateFormatSymbols), &dfs))
    {
        self->object->setDateFormatSymbols(*dfs); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDateFormatSymbols", arg);
}

static PyObject *t_simpledateformat_str(t_simpledateformat *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}


/* DateTimePatternGenerator */

static PyObject *t_datetimepatterngenerator_createEmptyInstance(
    PyTypeObject *type)
{
    DateTimePatternGenerator *dtpg;

    STATUS_CALL(dtpg = DateTimePatternGenerator::createEmptyInstance(status));

    return wrap_DateTimePatternGenerator(dtpg, T_OWNED);
}

static PyObject *t_datetimepatterngenerator_createInstance(PyTypeObject *type,
                                                           PyObject *args)
{
    DateTimePatternGenerator *dtpg;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(dtpg = DateTimePatternGenerator::createInstance(status));
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(dtpg = DateTimePatternGenerator::createInstance(
                            *locale, status));
            break;
        }
        return PyErr_SetArgsError(type, "createInstance", args);
      default:
        return PyErr_SetArgsError(type, "createInstance", args);
    }
        
    return wrap_DateTimePatternGenerator(dtpg, T_OWNED);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)

static PyObject *t_datetimepatterngenerator_staticGetSkeleton(
    PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString result;

        STATUS_CALL(result = DateTimePatternGenerator::staticGetSkeleton(
                        *u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError(type, "staticGetSkeleton", arg);
}

static PyObject *t_datetimepatterngenerator_staticGetBaseSkeleton(
    PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString result;

        STATUS_CALL(result = DateTimePatternGenerator::staticGetBaseSkeleton(
                        *u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError(type, "staticGetBaseSkeleton", arg);
}

#endif

static PyObject *t_datetimepatterngenerator_getSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString result;

        STATUS_CALL(result = self->object->getSkeleton(*u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getSkeleton", arg);
}

static PyObject *t_datetimepatterngenerator_getBaseSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString result;

        STATUS_CALL(result = self->object->getBaseSkeleton(*u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "staticGetBaseSkeleton", arg);
}

static PyObject *t_datetimepatterngenerator_addPattern(
    t_datetimepatterngenerator *self, PyObject *args)
{
    UnicodeString *u, _u;
    int override;

    if (!parseArgs(args, "Sb", &u, &_u, &override))
    {
        UDateTimePatternConflict conflict;
        UnicodeString conflictPattern;

        STATUS_CALL(conflict = self->object->addPattern(
                        *u, override, conflictPattern, status));
        PyObject *result = PyTuple_New(2);

        PyTuple_SET_ITEM(result, 0, PyInt_FromLong(conflict));
        PyTuple_SET_ITEM(result, 1, PyUnicode_FromUnicodeString(&conflictPattern));

        return result;
    }

    return PyErr_SetArgsError((PyObject *) self, "addPattern", args);
}

static PyObject *t_datetimepatterngenerator_getBestPattern(
    t_datetimepatterngenerator *self, PyObject *args)
{
    UnicodeString *u, _u;
#if U_ICU_VERSION_HEX >= 0x04040000
    int options;
#endif

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            UnicodeString result;

            STATUS_CALL(result = self->object->getBestPattern(*u, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
#if U_ICU_VERSION_HEX >= 0x04040000
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &options))
        {
            UnicodeString result;

            STATUS_CALL(result = self->object->getBestPattern(
                            *u, (UDateTimePatternMatchOptions) options,
                            status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
#endif
    }

    return PyErr_SetArgsError((PyObject *) self, "getBestPattern", args);
}

static PyObject *t_datetimepatterngenerator_setAppendItemFormat(
    t_datetimepatterngenerator *self, PyObject *args)
{
    UnicodeString *u, _u;
    int field;

    if (!parseArgs(args, "iS", &field, &u, &_u))
    {
        self->object->setAppendItemFormat((UDateTimePatternField) field, *u);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAppendItemFormat", args);
}

static PyObject *t_datetimepatterngenerator_setAppendItemName(
    t_datetimepatterngenerator *self, PyObject *args)
{
    UnicodeString *u, _u;
    int field;

    if (!parseArgs(args, "iS", &field, &u, &_u))
    {
        self->object->setAppendItemName((UDateTimePatternField) field, *u);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAppendItemName", args);
}

static PyObject *t_datetimepatterngenerator_getAppendItemFormat(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    int field;

    if (!parseArg(arg, "i", &field))
    {
        const UnicodeString &result = self->object->getAppendItemFormat(
            (UDateTimePatternField) field);

        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getAppendItemFormat", arg);
}

static PyObject *t_datetimepatterngenerator_getAppendItemName(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    int field;

    if (!parseArg(arg, "i", &field))
    {
        const UnicodeString &result = self->object->getAppendItemName(
            (UDateTimePatternField) field);

        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getAppendItemName", arg);
}

static PyObject *t_datetimepatterngenerator_replaceFieldTypes(
    t_datetimepatterngenerator *self, PyObject *args)
{
    UnicodeString *u, _u, *v, _v;;
#if U_ICU_VERSION_HEX >= 0x04040000
    int options;
#endif
    
    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
        {
            UnicodeString result;

            STATUS_CALL(result = self->object->replaceFieldTypes(
                            *u, *v, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
#if U_ICU_VERSION_HEX >= 0x04040000
      case 3:
        if (!parseArgs(args, "SSi", &u, &_u, &v, &_v, &options))
        {
            UnicodeString result;

            STATUS_CALL(result = self->object->replaceFieldTypes(
                            *u, *v, (UDateTimePatternMatchOptions) options,
                            status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
#endif
    }

    return PyErr_SetArgsError((PyObject *) self, "replaceFieldTypes", args);
}

static PyObject *t_datetimepatterngenerator_getSkeletons(
    t_datetimepatterngenerator *self)
{
    StringEnumeration *se;
    STATUS_CALL(se = self->object->getSkeletons(status));

    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_datetimepatterngenerator_getBaseSkeletons(
    t_datetimepatterngenerator *self)
{
    StringEnumeration *se;
    STATUS_CALL(se = self->object->getBaseSkeletons(status));

    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_datetimepatterngenerator_getRedundants(
    t_datetimepatterngenerator *self)
{
    StringEnumeration *se;
    STATUS_CALL(se = self->object->getRedundants(status));

    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_datetimepatterngenerator_getPatternForSkeleton(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    UnicodeString *u, _u;;
    
    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString result;

        result = self->object->getPatternForSkeleton(*u);
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getPatternForSkeleton", arg);
}

static PyObject *t_datetimepatterngenerator_setDecimal(
    t_datetimepatterngenerator *self, PyObject *arg)
{
    UnicodeString *u, _u;;
    
    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setDecimal(*u);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDecimal", arg);
}

static PyObject *t_datetimepatterngenerator_getDecimal(
    t_datetimepatterngenerator *self)
{
    const UnicodeString &result = self->object->getDecimal();
    return PyUnicode_FromUnicodeString(&result);
}


#if U_ICU_VERSION_HEX >= 0x04000000

/* DateInterval */

static int t_dateinterval_init(t_dateinterval *self,
                               PyObject *args, PyObject *kwds)
{
    UDate fromDate, toDate;

    if (!parseArgs(args, "DD", &fromDate, &toDate))
    {
        self->object = new DateInterval(fromDate, toDate);
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_dateinterval_getFromDate(t_dateinterval *self)
{
    UDate date = self->object->getFromDate();
    return PyFloat_FromDouble(date / 1000.0);
}

static PyObject *t_dateinterval_getToDate(t_dateinterval *self)
{
    UDate date = self->object->getToDate();
    return PyFloat_FromDouble(date / 1000.0);
}

static PyObject *t_dateinterval_str(t_dateinterval *self)
{
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString u;
    FieldPosition _fp;

    DateInterval_format->format(self->object, u, _fp, status);
    if (U_FAILURE(status))
        return ICUException(status).reportError();
    
    return PyUnicode_FromUnicodeString(&u);
}

DEFINE_RICHCMP(DateInterval, t_dateinterval);


/* DateIntervalInfo */

static int t_dateintervalinfo_init(t_dateintervalinfo *self,
                                   PyObject *args, PyObject *kwds)
{
    DateIntervalInfo *dii;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(dii = new DateIntervalInfo(status));
        self->object = dii;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(dii = new DateIntervalInfo(*locale, status));
            self->object = dii;
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

static PyObject *t_dateintervalinfo_getDefaultOrder(t_dateintervalinfo *self)
{
    UBool b = self->object->getDefaultOrder();
    Py_RETURN_BOOL(b);
}

static PyObject *t_dateintervalinfo_setIntervalPattern(t_dateintervalinfo *self,
                                                       PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    UCalendarDateFields ucdf;

    if (!parseArgs(args, "SiS", &u0, &_u0, &ucdf, &u1, &_u1))
    {
        /* u0 transient, u1 copied */
        STATUS_CALL(self->object->setIntervalPattern(*u0, ucdf, *u1, status));
        Py_RETURN_NONE;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "setIntervalPattern", args);
}

static PyObject *t_dateintervalinfo_getIntervalPattern(t_dateintervalinfo *self,
                                                       PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    UCalendarDateFields ucdf;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Si", &u0, &_u0, &ucdf))
        {
            STATUS_CALL(self->object->getIntervalPattern(*u0, ucdf, _u1,
                                                         status));
            return PyUnicode_FromUnicodeString(&_u1);
        }
        break;
      case 3:
        if (!parseArgs(args, "SiU", &u0, &_u0, &ucdf, &u1))
        {
            STATUS_CALL(self->object->getIntervalPattern(*u0, ucdf, *u1,
                                                         status));
            Py_RETURN_ARG(args, 2);
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "getIntervalPattern", args);
}

static PyObject *t_dateintervalinfo_setFallbackIntervalPattern(t_dateintervalinfo *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        /* copied */
        STATUS_CALL(self->object->setFallbackIntervalPattern(*u, status));
        Py_RETURN_NONE;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "setFallbackIntervalPattern", arg);
}

static PyObject *t_dateintervalinfo_getFallbackIntervalPattern(t_dateintervalinfo *self, PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getFallbackIntervalPattern(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getFallbackIntervalPattern(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "getFallbackIntervalPattern", args);
}

DEFINE_RICHCMP(DateIntervalInfo, t_dateintervalinfo);


/* DateIntervalFormat */

static PyObject *t_dateintervalformat_format(t_dateintervalformat *self,
                                             PyObject *args)
{
    UnicodeString *u, _u;
    FieldPosition *fp, _fp;
    DateInterval *di;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(DateInterval), &di))
        {
            STATUS_CALL(self->object->format(di, _u, _fp, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(DateInterval), &di, &u))
        {
            STATUS_CALL(self->object->format(di, *u, _fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "PP",
                       TYPE_CLASSID(DateInterval), TYPE_CLASSID(FieldPosition),
                       &di, &fp))
        {
            STATUS_CALL(self->object->format(di, _u, *fp, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "PUP",
                       TYPE_CLASSID(DateInterval), TYPE_CLASSID(FieldPosition),
                       &di, &u, &fp))
        {
            STATUS_CALL(self->object->format(di, *u, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return t_format_format((t_format *) self, args);
}

static PyObject *t_dateintervalformat_getDateIntervalInfo(t_dateintervalformat *self)
{
    const DateIntervalInfo *dii = self->object->getDateIntervalInfo();
    return wrap_DateIntervalInfo(new DateIntervalInfo(*dii), T_OWNED);
}

static PyObject *t_dateintervalformat_setDateIntervalInfo(t_dateintervalformat *self, PyObject *arg)
{
    DateIntervalInfo *dii;

    if (!parseArg(arg, "P", TYPE_CLASSID(DateIntervalInfo), &dii))
    {
        /* copied */
        STATUS_CALL(self->object->setDateIntervalInfo(*dii, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDateIntervalInfo", arg);
}

static PyObject *t_dateintervalformat_getDateFormat(t_dateintervalformat *self)
{
    DateFormat *format = (DateFormat *) self->object->getDateFormat()->clone();
    return wrap_DateFormat(format);
}

static PyObject *t_dateintervalformat_parseObject(t_dateintervalformat *self,
                                                  PyObject *args)
{
    PyErr_SetString(PyExc_NotImplementedError,
                    "DateIntervalFormat.parseObject()");
    return NULL;
}

static PyObject *t_dateintervalformat_createInstance(PyTypeObject *type,
                                                     PyObject *args)
{
    UnicodeString *u, _u;
    Locale *locale;
    DateIntervalInfo *dii;
    DateIntervalFormat *dif;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(dif = DateIntervalFormat::createInstance(*u, status));
            return wrap_DateIntervalFormat(dif, T_OWNED);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale),
                       &u, &_u, &locale))
        {
            STATUS_CALL(dif = DateIntervalFormat::createInstance(*u, *locale,
                                                                 status));
            return wrap_DateIntervalFormat(dif, T_OWNED);
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(DateIntervalInfo),
                       &u, &_u, &dii))
        {
            STATUS_CALL(dif = DateIntervalFormat::createInstance(*u, *dii,
                                                                 status));
            return wrap_DateIntervalFormat(dif, T_OWNED);
        }
        break;
      case 3:
        if (!parseArgs(args, "SPP",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(DateIntervalInfo),
                       &u, &_u, &locale, &dii))
        {
            STATUS_CALL(dif = DateIntervalFormat::createInstance(*u, *locale,
                                                                 *dii, status));
            return wrap_DateIntervalFormat(dif, T_OWNED);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createInstance", args);
}

DEFINE_RICHCMP(DateIntervalFormat, t_dateintervalformat);

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)

/* RelativeDateTimeFormatter */

static int t_relativedatetimeformatter_init(t_relativedatetimeformatter *self,
                                            PyObject *args, PyObject *kwds)
{
    Locale *locale;
    RelativeDateTimeFormatter *fmt;
    NumberFormat *number_format;
    UDateRelativeDateTimeFormatterStyle style;
    UDisplayContext context;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(fmt = new RelativeDateTimeFormatter(status));
        self->object = fmt;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(fmt = new RelativeDateTimeFormatter(*locale, status));
            self->object = fmt;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "PP", TYPE_CLASSID(Locale),
                       TYPE_CLASSID(NumberFormat), &locale, &number_format))
        {
            INT_STATUS_CALL(fmt = new RelativeDateTimeFormatter(
                *locale, (NumberFormat *) number_format->clone(), status));
            self->object = fmt;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 4:
        if (!parseArgs(args, "PPii", TYPE_CLASSID(Locale),
                       TYPE_CLASSID(NumberFormat), &locale, &number_format,
                       &style, &context))
        {
            INT_STATUS_CALL(fmt = new RelativeDateTimeFormatter(
                *locale, (NumberFormat *) number_format->clone(),
                style, context, status));
            self->object = fmt;
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

static PyObject *t_relativedatetimeformatter_format(
    t_relativedatetimeformatter *self, PyObject *args)
{
    UDateDirection direction = UDAT_DIRECTION_PLAIN;
    UDateAbsoluteUnit abs_unit = UDAT_ABSOLUTE_NOW;
    UDateRelativeUnit rel_unit = UDAT_RELATIVE_SECONDS;
    UnicodeString *buffer;
    double value;

    switch (PyTuple_Size(args)) {
      case 0: {
        UnicodeString result;

        STATUS_CALL(self->object->format(direction, abs_unit, result, status));
        return PyUnicode_FromUnicodeString(&result);
      }
      case 1:
        if (!parseArgs(args, "d", &value))
        {
            UnicodeString result;

            STATUS_CALL(self->object->format(
              value, UDAT_DIRECTION_NEXT, rel_unit, result, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
      case 2:
        if (!parseArgs(args, "ii", &direction, &abs_unit))
        {
            UnicodeString result;

            STATUS_CALL(self->object->format(
                direction, abs_unit, result, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
      case 3:
        if (!parseArgs(args, "iiU", &direction, &abs_unit, &buffer))
        {
            STATUS_CALL(self->object->format(
                direction, abs_unit, *buffer, status));
            Py_RETURN_ARG(args, 2);
        }
        if (!parseArgs(args, "dii", &value, &direction, &rel_unit))
        {
            UnicodeString result;

            STATUS_CALL(self->object->format(
                value, direction, rel_unit, result, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
      case 4:
        if (!parseArgs(args, "diiU", &value, &direction, &rel_unit, &buffer))
        {
            STATUS_CALL(self->object->format(
                value, direction, rel_unit, *buffer, status));
            Py_RETURN_ARG(args, 3);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "format", args);
}

static PyObject *t_relativedatetimeformatter_combineDateAndTime(
    t_relativedatetimeformatter *self, PyObject *args)
{
    UnicodeString *u, _u, *v, _v;
    UnicodeString *buffer;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
        {
            UnicodeString result;

            STATUS_CALL(self->object->combineDateAndTime(
                *u, *v, result, status));
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
      case 3:
        if (!parseArgs(args, "SSU", &u, &_u, &v, &_v, &buffer))
        {
            STATUS_CALL(self->object->combineDateAndTime(
                *u, *v, *buffer, status));
            Py_RETURN_ARG(args, 2);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "combineDateAndTime", args);
}

static PyObject *t_relativedatetimeformatter_getNumberFormat(
    t_relativedatetimeformatter *self)
{
    const NumberFormat &format = self->object->getNumberFormat();
    return wrap_NumberFormat(const_cast<NumberFormat *>(&format), 0);
}

static PyObject *t_relativedatetimeformatter_getCapitalizationContext(
    t_relativedatetimeformatter *self)
{
    return PyInt_FromLong(self->object->getCapitalizationContext());
}

static PyObject *t_relativedatetimeformatter_getFormatStyle(
    t_relativedatetimeformatter *self)
{
    return PyInt_FromLong(self->object->getFormatStyle());
}

#endif

void _init_dateformat(PyObject *m)
{
    DateFormatSymbolsType_.tp_richcompare =
        (richcmpfunc) t_dateformatsymbols_richcmp;
    SimpleDateFormatType_.tp_str = (reprfunc) t_simpledateformat_str;
#if U_ICU_VERSION_HEX >= 0x04000000
    DateIntervalType_.tp_str = (reprfunc) t_dateinterval_str;
    DateIntervalType_.tp_richcompare =
        (richcmpfunc) t_dateinterval_richcmp;
    DateIntervalInfoType_.tp_richcompare =
        (richcmpfunc) t_dateintervalinfo_richcmp;
    DateIntervalFormatType_.tp_richcompare =
        (richcmpfunc) t_dateintervalformat_richcmp;
#endif

    INSTALL_CONSTANTS_TYPE(UDateTimePatternConflict, m);
    INSTALL_CONSTANTS_TYPE(UDateTimePatternField, m);
#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_CONSTANTS_TYPE(UDateTimePatternMatchOptions, m);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    INSTALL_CONSTANTS_TYPE(UDateRelativeDateTimeFormatterStyle, m);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_CONSTANTS_TYPE(UDisplayContext, m);
    INSTALL_CONSTANTS_TYPE(UDisplayContextType, m);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    INSTALL_CONSTANTS_TYPE(UDateDirection, m);
    INSTALL_CONSTANTS_TYPE(UDateAbsoluteUnit, m);
    INSTALL_CONSTANTS_TYPE(UDateRelativeUnit, m);
    INSTALL_CONSTANTS_TYPE(UDateFormatBooleanAttribute, m);
#endif

    REGISTER_TYPE(DateFormatSymbols, m);
    INSTALL_TYPE(DateFormat, m);
    REGISTER_TYPE(SimpleDateFormat, m);
    REGISTER_TYPE(DateTimePatternGenerator, m);
#if U_ICU_VERSION_HEX >= 0x04000000
    REGISTER_TYPE(DateInterval, m);
    REGISTER_TYPE(DateIntervalInfo, m);
    REGISTER_TYPE(DateIntervalFormat, m);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    INSTALL_TYPE(RelativeDateTimeFormatter, m);
#endif

    INSTALL_STATIC_INT(DateFormatSymbols, FORMAT);
    INSTALL_STATIC_INT(DateFormatSymbols, STANDALONE);

    INSTALL_STATIC_INT(DateFormatSymbols, WIDE);
    INSTALL_STATIC_INT(DateFormatSymbols, ABBREVIATED);
    INSTALL_STATIC_INT(DateFormatSymbols, NARROW);

    INSTALL_STATIC_INT(DateFormat, kNone);
    INSTALL_STATIC_INT(DateFormat, kFull);
    INSTALL_STATIC_INT(DateFormat, kLong);
    INSTALL_STATIC_INT(DateFormat, kMedium);
    INSTALL_STATIC_INT(DateFormat, kShort);
    INSTALL_STATIC_INT(DateFormat, kDateOffset);
    INSTALL_STATIC_INT(DateFormat, kDateTime);
    INSTALL_STATIC_INT(DateFormat, kDefault);
    INSTALL_STATIC_INT(DateFormat, FULL);
    INSTALL_STATIC_INT(DateFormat, LONG);
    INSTALL_STATIC_INT(DateFormat, MEDIUM);
    INSTALL_STATIC_INT(DateFormat, SHORT);
    INSTALL_STATIC_INT(DateFormat, DEFAULT);
    INSTALL_STATIC_INT(DateFormat, DATE_OFFSET);
    INSTALL_STATIC_INT(DateFormat, NONE);
    INSTALL_STATIC_INT(DateFormat, DATE_TIME);

    INSTALL_STATIC_INT(DateFormat, kEraField);
    INSTALL_STATIC_INT(DateFormat, kYearField);
    INSTALL_STATIC_INT(DateFormat, kMonthField);
    INSTALL_STATIC_INT(DateFormat, kDateField);
    INSTALL_STATIC_INT(DateFormat, kHourOfDay1Field);
    INSTALL_STATIC_INT(DateFormat, kHourOfDay0Field);
    INSTALL_STATIC_INT(DateFormat, kMinuteField);
    INSTALL_STATIC_INT(DateFormat, kSecondField);
    INSTALL_STATIC_INT(DateFormat, kMillisecondField);
    INSTALL_STATIC_INT(DateFormat, kDayOfWeekField);
    INSTALL_STATIC_INT(DateFormat, kDayOfYearField);
    INSTALL_STATIC_INT(DateFormat, kDayOfWeekInMonthField);
    INSTALL_STATIC_INT(DateFormat, kWeekOfYearField);
    INSTALL_STATIC_INT(DateFormat, kWeekOfMonthField);
    INSTALL_STATIC_INT(DateFormat, kAmPmField);
    INSTALL_STATIC_INT(DateFormat, kHour1Field);
    INSTALL_STATIC_INT(DateFormat, kHour0Field);
    INSTALL_STATIC_INT(DateFormat, kTimezoneField);
    INSTALL_STATIC_INT(DateFormat, kYearWOYField);
    INSTALL_STATIC_INT(DateFormat, kDOWLocalField);
    INSTALL_STATIC_INT(DateFormat, kExtendedYearField);
    INSTALL_STATIC_INT(DateFormat, kJulianDayField);
    INSTALL_STATIC_INT(DateFormat, kMillisecondsInDayField);
    INSTALL_STATIC_INT(DateFormat, ERA_FIELD);
    INSTALL_STATIC_INT(DateFormat, YEAR_FIELD);
    INSTALL_STATIC_INT(DateFormat, MONTH_FIELD);
    INSTALL_STATIC_INT(DateFormat, DATE_FIELD);
    INSTALL_STATIC_INT(DateFormat, HOUR_OF_DAY1_FIELD);
    INSTALL_STATIC_INT(DateFormat, HOUR_OF_DAY0_FIELD);
    INSTALL_STATIC_INT(DateFormat, MINUTE_FIELD);
    INSTALL_STATIC_INT(DateFormat, SECOND_FIELD);
    INSTALL_STATIC_INT(DateFormat, MILLISECOND_FIELD);
    INSTALL_STATIC_INT(DateFormat, DAY_OF_WEEK_FIELD);
    INSTALL_STATIC_INT(DateFormat, DAY_OF_YEAR_FIELD);
    INSTALL_STATIC_INT(DateFormat, DAY_OF_WEEK_IN_MONTH_FIELD);
    INSTALL_STATIC_INT(DateFormat, WEEK_OF_YEAR_FIELD);
    INSTALL_STATIC_INT(DateFormat, WEEK_OF_MONTH_FIELD);
    INSTALL_STATIC_INT(DateFormat, AM_PM_FIELD);
    INSTALL_STATIC_INT(DateFormat, HOUR1_FIELD);
    INSTALL_STATIC_INT(DateFormat, HOUR0_FIELD);
    INSTALL_STATIC_INT(DateFormat, TIMEZONE_FIELD);

    INSTALL_ENUM(UDateTimePatternConflict, "NO_CONFLICT", UDATPG_NO_CONFLICT);
    INSTALL_ENUM(UDateTimePatternConflict, "BASE_CONFLICT", UDATPG_BASE_CONFLICT);
    INSTALL_ENUM(UDateTimePatternConflict, "CONFLICT", UDATPG_CONFLICT);
    INSTALL_ENUM(UDateTimePatternConflict, "CONFLICT_COUNT", UDATPG_CONFLICT_COUNT);

    INSTALL_ENUM(UDateTimePatternField, "ERA_FIELD", UDATPG_ERA_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "YEAR_FIELD", UDATPG_YEAR_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "QUARTER_FIELD", UDATPG_QUARTER_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "MONTH_FIELD", UDATPG_MONTH_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "WEEK_OF_YEAR_FIELD", UDATPG_WEEK_OF_YEAR_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "WEEK_OF_MONTH_FIELD", UDATPG_WEEK_OF_MONTH_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "WEEKDAY_FIELD", UDATPG_WEEKDAY_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "DAY_OF_YEAR_FIELD", UDATPG_DAY_OF_YEAR_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "DAY_OF_WEEK_IN_MONTH_FIELD", UDATPG_DAY_OF_WEEK_IN_MONTH_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "DAY_FIELD", UDATPG_DAY_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "DAYPERIOD_FIELD", UDATPG_DAYPERIOD_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "HOUR_FIELD", UDATPG_HOUR_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "MINUTE_FIELD", UDATPG_MINUTE_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "SECOND_FIELD", UDATPG_SECOND_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "FRACTIONAL_SECOND_FIELD", UDATPG_FRACTIONAL_SECOND_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "ZONE_FIELD", UDATPG_ZONE_FIELD);
    INSTALL_ENUM(UDateTimePatternField, "FIELD_COUNT", UDATPG_FIELD_COUNT);

#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(UDateTimePatternMatchOptions, "NO_OPTIONS",
                 UDATPG_MATCH_NO_OPTIONS);
    INSTALL_ENUM(UDateTimePatternMatchOptions, "HOUR_FIELD_LENGTH",
                 UDATPG_MATCH_HOUR_FIELD_LENGTH);
    INSTALL_ENUM(UDateTimePatternMatchOptions, "ALL_FIELDS_LENGTH",
                 UDATPG_MATCH_ALL_FIELDS_LENGTH);

    INSTALL_STATIC_INT(DateIntervalInfo, kMaxIntervalPatternIndex);
#endif

#if U_ICU_VERSION_HEX >= 0x04000000
    UErrorCode status = U_ZERO_ERROR;
    DateInterval_format =
        DateIntervalFormat::createInstance(UDAT_YEAR_ABBR_MONTH_DAY, status);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    INSTALL_ENUM(UDateRelativeDateTimeFormatterStyle, "LONG", UDAT_STYLE_LONG);
    INSTALL_ENUM(UDateRelativeDateTimeFormatterStyle, "SHORT", UDAT_STYLE_SHORT);
    INSTALL_ENUM(UDateRelativeDateTimeFormatterStyle, "NARROW", UDAT_STYLE_NARROW);
    INSTALL_ENUM(UDateRelativeDateTimeFormatterStyle, "COUNT", UDAT_STYLE_COUNT);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_ENUM(UDisplayContext, "STANDARD_NAMES", UDISPCTX_STANDARD_NAMES);
    INSTALL_ENUM(UDisplayContext, "DIALECT_NAMES", UDISPCTX_DIALECT_NAMES);
    INSTALL_ENUM(UDisplayContext, "CAPITALIZATION_NONE", UDISPCTX_CAPITALIZATION_NONE);
    INSTALL_ENUM(UDisplayContext, "CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE", UDISPCTX_CAPITALIZATION_FOR_MIDDLE_OF_SENTENCE);
    INSTALL_ENUM(UDisplayContext, "CAPITALIZATION_FOR_BEGINNING_OF_SENTENCE", UDISPCTX_CAPITALIZATION_FOR_BEGINNING_OF_SENTENCE);
    INSTALL_ENUM(UDisplayContext, "CAPITALIZATION_FOR_UI_LIST_OR_MENU", UDISPCTX_CAPITALIZATION_FOR_UI_LIST_OR_MENU);
    INSTALL_ENUM(UDisplayContext, "CAPITALIZATION_FOR_STANDALONE", UDISPCTX_CAPITALIZATION_FOR_STANDALONE);

    INSTALL_ENUM(UDisplayContextType, "TYPE_DIALECT_HANDLING",
                 UDISPCTX_TYPE_DIALECT_HANDLING);
    INSTALL_ENUM(UDisplayContextType, "TYPE_CAPITALIZATION",
                 UDISPCTX_TYPE_CAPITALIZATION);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    INSTALL_ENUM(UDisplayContext, "LENGTH_FULL", UDISPCTX_LENGTH_FULL);
    INSTALL_ENUM(UDisplayContext, "LENGTH_SHORT", UDISPCTX_LENGTH_SHORT);

    INSTALL_ENUM(UDisplayContextType, "TYPE_DISPLAY_LENGTH",
                 UDISPCTX_TYPE_DISPLAY_LENGTH);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    INSTALL_ENUM(UDateDirection, "LAST_2", UDAT_DIRECTION_LAST_2);
    INSTALL_ENUM(UDateDirection, "LAST", UDAT_DIRECTION_LAST);
    INSTALL_ENUM(UDateDirection, "THIS", UDAT_DIRECTION_THIS);
    INSTALL_ENUM(UDateDirection, "NEXT", UDAT_DIRECTION_NEXT);
    INSTALL_ENUM(UDateDirection, "NEXT_2", UDAT_DIRECTION_NEXT_2);
    INSTALL_ENUM(UDateDirection, "PLAIN", UDAT_DIRECTION_PLAIN);

    INSTALL_ENUM(UDateAbsoluteUnit, "SUNDAY", UDAT_ABSOLUTE_SUNDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "MONDAY", UDAT_ABSOLUTE_MONDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "TUESDAY", UDAT_ABSOLUTE_TUESDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "WEDNESDAY", UDAT_ABSOLUTE_WEDNESDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "THURSDAY", UDAT_ABSOLUTE_THURSDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "FRIDAY", UDAT_ABSOLUTE_FRIDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "SATURDAY", UDAT_ABSOLUTE_SATURDAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "DAY", UDAT_ABSOLUTE_DAY);
    INSTALL_ENUM(UDateAbsoluteUnit, "WEEK", UDAT_ABSOLUTE_WEEK);
    INSTALL_ENUM(UDateAbsoluteUnit, "MONTH", UDAT_ABSOLUTE_MONTH);
    INSTALL_ENUM(UDateAbsoluteUnit, "YEAR", UDAT_ABSOLUTE_YEAR);
    INSTALL_ENUM(UDateAbsoluteUnit, "NOW", UDAT_ABSOLUTE_NOW);

    INSTALL_ENUM(UDateRelativeUnit, "SECONDS", UDAT_RELATIVE_SECONDS);
    INSTALL_ENUM(UDateRelativeUnit, "MINUTES", UDAT_RELATIVE_MINUTES);
    INSTALL_ENUM(UDateRelativeUnit, "HOURS", UDAT_RELATIVE_HOURS);
    INSTALL_ENUM(UDateRelativeUnit, "DAYS", UDAT_RELATIVE_DAYS);
    INSTALL_ENUM(UDateRelativeUnit, "WEEKS", UDAT_RELATIVE_WEEKS);
    INSTALL_ENUM(UDateRelativeUnit, "MONTHS", UDAT_RELATIVE_MONTHS);
    INSTALL_ENUM(UDateRelativeUnit, "YEARS", UDAT_RELATIVE_YEARS);

    INSTALL_ENUM(UDateFormatBooleanAttribute, "PARSE_ALLOW_WHITESPACE",
                 UDAT_PARSE_ALLOW_WHITESPACE);
    INSTALL_ENUM(UDateFormatBooleanAttribute, "PARSE_ALLOW_NUMERIC",
                 UDAT_PARSE_ALLOW_NUMERIC);
    INSTALL_ENUM(UDateFormatBooleanAttribute, "BOOLEAN_ATTRIBUTE_COUNT",
                 UDAT_BOOLEAN_ATTRIBUTE_COUNT);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(56, 0, 0)
    INSTALL_ENUM(UDateFormatBooleanAttribute, "PARSE_PARTIAL_LITERAL_MATCH",
                 UDAT_PARSE_PARTIAL_LITERAL_MATCH);
    INSTALL_ENUM(UDateFormatBooleanAttribute, "PARSE_MULTIPLE_PATTERNS_FOR_MATCH",
                 UDAT_PARSE_MULTIPLE_PATTERNS_FOR_MATCH);
#endif
}
