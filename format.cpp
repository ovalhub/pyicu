/* ====================================================================
 * Copyright (c) 2004-2014 Open Source Applications Foundation.
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
#include "macros.h"
#include "dateformat.h"
#include "numberformat.h"

#if U_ICU_VERSION_HEX >= 0x04080000
    DECLARE_CONSTANTS_TYPE(UTimeUnitFormatStyle);
#endif

/* FieldPosition */

class t_fieldposition : public _wrapper {
public:
    FieldPosition *object;
};

static int t_fieldposition_init(t_fieldposition *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_fieldposition_getField(t_fieldposition *self);
static PyObject *t_fieldposition_setField(t_fieldposition *self, PyObject *arg);
static PyObject *t_fieldposition_getBeginIndex(t_fieldposition *self);
static PyObject *t_fieldposition_setBeginIndex(t_fieldposition *self,
                                               PyObject *arg);
static PyObject *t_fieldposition_getEndIndex(t_fieldposition *self);
static PyObject *t_fieldposition_setEndIndex(t_fieldposition *self,
                                             PyObject *arg);

static PyMethodDef t_fieldposition_methods[] = {
    DECLARE_METHOD(t_fieldposition, getField, METH_NOARGS),
    DECLARE_METHOD(t_fieldposition, setField, METH_O),
    DECLARE_METHOD(t_fieldposition, getBeginIndex, METH_NOARGS),
    DECLARE_METHOD(t_fieldposition, setBeginIndex, METH_O),
    DECLARE_METHOD(t_fieldposition, getEndIndex, METH_NOARGS),
    DECLARE_METHOD(t_fieldposition, setEndIndex, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(FieldPosition, t_fieldposition, UObject, FieldPosition,
             t_fieldposition_init, NULL);

/* ParsePosition */

class t_parseposition : public _wrapper {
public:
    ParsePosition *object;
};

static int t_parseposition_init(t_parseposition *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_parseposition_getIndex(t_parseposition *self);
static PyObject *t_parseposition_setIndex(t_parseposition *self, PyObject *arg);
static PyObject *t_parseposition_getErrorIndex(t_parseposition *self);
static PyObject *t_parseposition_setErrorIndex(t_parseposition *self,
                                               PyObject *arg);

static PyMethodDef t_parseposition_methods[] = {
    DECLARE_METHOD(t_parseposition, getIndex, METH_NOARGS),
    DECLARE_METHOD(t_parseposition, setIndex, METH_O),
    DECLARE_METHOD(t_parseposition, getErrorIndex, METH_NOARGS),
    DECLARE_METHOD(t_parseposition, setErrorIndex, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(ParsePosition, t_parseposition, UObject, ParsePosition,
             t_parseposition_init, NULL);

/* Format */

PyObject *t_format_format(t_format *self, PyObject *args);
static PyObject *t_format_parseObject(t_format *self, PyObject *args);
static PyObject *t_format_getLocale(t_format *self, PyObject *args);
static PyObject *t_format_getLocaleID(t_format *self, PyObject *args);

static PyMethodDef t_format_methods[] = {
    DECLARE_METHOD(t_format, format, METH_VARARGS),
    DECLARE_METHOD(t_format, parseObject, METH_VARARGS),
    DECLARE_METHOD(t_format, getLocale, METH_VARARGS),
    DECLARE_METHOD(t_format, getLocaleID, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Format, t_format, UObject, Format, abstract_init, NULL);

/* MeasureFormat */

class t_measureformat : public _wrapper {
public:
    MeasureFormat *object;
    PyObject *locale;
};

static PyObject *t_measureformat_createCurrencyFormat(PyTypeObject *type,
                                                      PyObject *args);

static PyMethodDef t_measureformat_methods[] = {
    DECLARE_METHOD(t_measureformat, createCurrencyFormat, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_measureformat_dealloc(t_measureformat *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->locale);

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(MeasureFormat, t_measureformat, Format, MeasureFormat,
             abstract_init, t_measureformat_dealloc);

#if U_ICU_VERSION_HEX >= 0x04020000

/* TimeUnitFormat */

class t_timeunitformat : public _wrapper {
public:
    TimeUnitFormat *object;
};

static int t_timeunitformat_init(t_timeunitformat *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_timeunitformat_setLocale(t_timeunitformat *self,
                                            PyObject *arg);
static PyObject *t_timeunitformat_setNumberFormat(t_timeunitformat *self,
                                                  PyObject *arg);

static PyMethodDef t_timeunitformat_methods[] = {
    DECLARE_METHOD(t_timeunitformat, setLocale, METH_O),
    DECLARE_METHOD(t_timeunitformat, setNumberFormat, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(TimeUnitFormat, t_timeunitformat, MeasureFormat, TimeUnitFormat,
             t_timeunitformat_init, NULL);

#endif

/* MessageFormat */

class t_messageformat : public _wrapper {
public:
    MessageFormat *object;
};

static int t_messageformat_init(t_messageformat *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_messageformat_getLocale(t_messageformat *self);
static PyObject *t_messageformat_setLocale(t_messageformat *self,
                                           PyObject *arg);
static PyObject *t_messageformat_applyPattern(t_messageformat *self,
                                              PyObject *arg);
static PyObject *t_messageformat_toPattern(t_messageformat *self,
                                           PyObject *args);
static PyObject *t_messageformat_getFormats(t_messageformat *self);
static PyObject *t_messageformat_setFormats(t_messageformat *self,
                                            PyObject *arg);
static PyObject *t_messageformat_setFormat(t_messageformat *self,
                                           PyObject *args);
static PyObject *t_messageformat_format(t_messageformat *self, PyObject *args);
static PyObject *t_messageformat_parse(t_messageformat *self, PyObject *args);
static PyObject *t_messageformat_formatMessage(PyTypeObject *type,
                                               PyObject *args);
static PyObject *t_messageformat_mod(t_messageformat *self, PyObject *args);

static PyNumberMethods t_messageformat_as_number = {
    0,                                 /* nb_add */
    0,                                 /* nb_subtract */
    0,                                 /* nb_multiply */
    0,                                 /* nb_divide */
    (binaryfunc) t_messageformat_mod,  /* nb_remainder */
};

static PyMethodDef t_messageformat_methods[] = {
    DECLARE_METHOD(t_messageformat, getLocale, METH_NOARGS),
    DECLARE_METHOD(t_messageformat, setLocale, METH_O),
    DECLARE_METHOD(t_messageformat, applyPattern, METH_O),
    DECLARE_METHOD(t_messageformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_messageformat, getFormats, METH_NOARGS),
    DECLARE_METHOD(t_messageformat, setFormats, METH_O),
    DECLARE_METHOD(t_messageformat, setFormat, METH_VARARGS),
    DECLARE_METHOD(t_messageformat, format, METH_VARARGS),
    DECLARE_METHOD(t_messageformat, parse, METH_VARARGS),
    DECLARE_METHOD(t_messageformat, formatMessage, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(MessageFormat, t_messageformat, Format, MessageFormat,
             t_messageformat_init, NULL);

#if U_ICU_VERSION_HEX >= 0x04000000

/* PluralRules */

class t_pluralrules : public _wrapper {
public:
    PluralRules *object;
};

static int t_pluralrules_init(t_pluralrules *self,
                              PyObject *args, PyObject *kwds);
static PyObject *t_pluralrules_select(t_pluralrules *self, PyObject *arg);
static PyObject *t_pluralrules_getKeywords(t_pluralrules *self);
static PyObject *t_pluralrules_getKeywordOther(t_pluralrules *self);
static PyObject *t_pluralrules_isKeyword(t_pluralrules *self, PyObject *arg);
static PyObject *t_pluralrules_createRules(PyTypeObject *type, PyObject *arg);
static PyObject *t_pluralrules_createDefaultRules(PyTypeObject *type);
static PyObject *t_pluralrules_forLocale(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_pluralrules_methods[] = {
    DECLARE_METHOD(t_pluralrules, select, METH_O),
    DECLARE_METHOD(t_pluralrules, getKeywords, METH_NOARGS),
    DECLARE_METHOD(t_pluralrules, getKeywordOther, METH_NOARGS),
    DECLARE_METHOD(t_pluralrules, isKeyword, METH_O),
    DECLARE_METHOD(t_pluralrules, createRules, METH_O | METH_CLASS),
    DECLARE_METHOD(t_pluralrules, createDefaultRules, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_pluralrules, forLocale, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(PluralRules, t_pluralrules, UObject, PluralRules,
             t_pluralrules_init, NULL);

/* PluralFormat */

class t_pluralformat : public _wrapper {
public:
    PluralFormat *object;
    PyObject *numberformat;
};

static int t_pluralformat_init(t_pluralformat *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_pluralformat_setLocale(t_pluralformat *self,
                                            PyObject *arg);
static PyObject *t_pluralformat_setNumberFormat(t_pluralformat *self,
                                                  PyObject *arg);
static PyObject *t_pluralformat_toPattern(t_pluralformat *self, PyObject *args);
static PyObject *t_pluralformat_applyPattern(t_pluralformat *self,
                                             PyObject *arg);
static PyObject *t_pluralformat_format(t_pluralformat *self, PyObject *args);

static PyMethodDef t_pluralformat_methods[] = {
    DECLARE_METHOD(t_pluralformat, setLocale, METH_O),
    DECLARE_METHOD(t_pluralformat, setNumberFormat, METH_O),
    DECLARE_METHOD(t_pluralformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_pluralformat, applyPattern, METH_O),
    DECLARE_METHOD(t_pluralformat, format, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_pluralformat_dealloc(t_pluralformat *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->numberformat);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(PluralFormat, t_pluralformat, Format, PluralFormat,
             t_pluralformat_init, t_pluralformat_dealloc);

#endif

#if U_ICU_VERSION_HEX >= 0x04040000

/* SelectFormat */

class t_selectformat : public _wrapper {
public:
    SelectFormat *object;
};

static int t_selectformat_init(t_selectformat *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_selectformat_applyPattern(t_selectformat *self,
                                             PyObject *arg);
static PyObject *t_selectformat_toPattern(t_selectformat *self, PyObject *args);
static PyObject *t_selectformat_format(t_selectformat *self, PyObject *args);
static PyObject *t_selectformat_parseObject(t_selectformat *self,
                                            PyObject *args);

static PyMethodDef t_selectformat_methods[] = {
    DECLARE_METHOD(t_selectformat, applyPattern, METH_O),
    DECLARE_METHOD(t_selectformat, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_selectformat, format, METH_VARARGS),
    DECLARE_METHOD(t_selectformat, parseObject, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(SelectFormat, t_selectformat, Format, SelectFormat,
             t_selectformat_init, NULL);

#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)

class t_listformatter : public _wrapper {
public:
    ListFormatter *object;
};

static PyObject *t_listformatter_format(t_listformatter *self, PyObject *arg);
static PyObject *t_listformatter_createInstance(PyTypeObject *type,
                                                PyObject *args);

static PyMethodDef t_listformatter_methods[] = {
    DECLARE_METHOD(t_listformatter, format, METH_O),
    DECLARE_METHOD(t_listformatter, createInstance, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(ListFormatter, t_listformatter, UObject, ListFormatter,
             abstract_init, NULL);

#endif

/* FieldPosition */

static int t_fieldposition_init(t_fieldposition *self,
                                PyObject *args, PyObject *kwds)
{
    int i;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new FieldPosition();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "i", &i))
        {
            self->object = new FieldPosition(i);
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

static PyObject *t_fieldposition_getField(t_fieldposition *self)
{
    return PyInt_FromLong(self->object->getField());
}

static PyObject *t_fieldposition_setField(t_fieldposition *self, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        self->object->setField(i);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setField", arg);
}

static PyObject *t_fieldposition_getBeginIndex(t_fieldposition *self)
{
    return PyInt_FromLong(self->object->getBeginIndex());
}

static PyObject *t_fieldposition_setBeginIndex(t_fieldposition *self,
                                               PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        self->object->setBeginIndex(i);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setBeginIndex", arg);
}

static PyObject *t_fieldposition_getEndIndex(t_fieldposition *self)
{
    return PyInt_FromLong(self->object->getEndIndex());
}

static PyObject *t_fieldposition_setEndIndex(t_fieldposition *self,
                                             PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        self->object->setEndIndex(i);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setEndIndex", arg);
}

static PyObject *t_fieldposition_richcmp(t_fieldposition *self, PyObject *arg, int op)
{
    int b = 0;
    FieldPosition *i;

    if (!parseArg(arg, "P", TYPE_CLASSID(FieldPosition), &i))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *i;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}

/* ParsePosition */

static int t_parseposition_init(t_parseposition *self,
                                PyObject *args, PyObject *kwds)
{
    int i;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new ParsePosition();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "i", &i))
        {
            self->object = new ParsePosition(i);
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

static PyObject *t_parseposition_getIndex(t_parseposition *self)
{
    return PyInt_FromLong(self->object->getIndex());
}

static PyObject *t_parseposition_setIndex(t_parseposition *self, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        self->object->setIndex(i);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setIndex", arg);
}

static PyObject *t_parseposition_getErrorIndex(t_parseposition *self)
{
    return PyInt_FromLong(self->object->getErrorIndex());
}

static PyObject *t_parseposition_setErrorIndex(t_parseposition *self,
                                               PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        self->object->setErrorIndex(i);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setErrorIndex", arg);
}

static PyObject *t_parseposition_richcmp(t_parseposition *self, PyObject *arg, int op)
{
    int b = 0;
    ParsePosition *i;

    if (!parseArg(arg, "P", TYPE_CLASSID(ParsePosition), &i))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *i;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}


/* Format */

PyObject *t_format_format(t_format *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    Formattable *obj;
    FieldPosition *fp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Formattable), &obj))
        {
            STATUS_CALL(self->object->format(*obj, _u, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Formattable),
                       &obj, &u))
        {
            STATUS_CALL(self->object->format(*obj, *u, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "PP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(FieldPosition),
                       &obj, &fp))
        {
            STATUS_CALL(self->object->format(*obj, _u, *fp, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "PUP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(FieldPosition),
                       &obj, &u, &fp))
        {
            STATUS_CALL(self->object->format(*obj, *u, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "format", args);
}

static PyObject *t_format_parseObject(t_format *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    Formattable obj;
    ParsePosition *pp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(self->object->parseObject(*u, obj, status));
            return wrap_Formattable(obj);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(ParsePosition),
                       &u, &_u, &pp))
        {
            pp->setErrorIndex(-1);
            self->object->parseObject(*u, obj, *pp);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            return wrap_Formattable(obj);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "parseObject", args);
}

static PyObject *t_format_getLocale(t_format *self, PyObject *args)
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

static PyObject *t_format_getLocaleID(t_format *self, PyObject *args)
{
    ULocDataLocaleType type;
    const char *id;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(id = self->object->getLocaleID(ULOC_VALID_LOCALE, status));
        return PyString_FromString(id);
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            STATUS_CALL(id = self->object->getLocaleID(type, status));
            return PyString_FromString(id);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocaleID", args);
}

static PyObject *t_format_richcmp(t_format *self, PyObject *arg, int op)
{
    int b = 0;
    Format *i;

    if (!parseArg(arg, "P", TYPE_ID(Format), &i))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *i;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}


/* MeasureFormat */

static PyObject *t_measureformat_createCurrencyFormat(PyTypeObject *type,
                                                      PyObject *args)
{
    MeasureFormat *format;
    Locale *locale;
    PyObject *localeObj = NULL;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = MeasureFormat::createCurrencyFormat(status));
        return wrap_MeasureFormat(format, T_OWNED);
      case 1:
        if (!parseArgs(args, "p", TYPE_CLASSID(Locale), &locale, &localeObj))
        {
            UErrorCode status = U_ZERO_ERROR;
            MeasureFormat *format =
                MeasureFormat::createCurrencyFormat(*locale, status);

            if (U_FAILURE(status))
            {
                Py_XDECREF(localeObj);
                return ICUException(status).reportError();
            }

            PyObject *result = wrap_MeasureFormat(format, T_OWNED);
            t_measureformat *self = (t_measureformat *) result;

            self->locale = localeObj;

            return result;
        }
        break;
    }

    return PyErr_SetArgsError(type, "createCurrencyFormat", args);
}


#if U_ICU_VERSION_HEX >= 0x04020000

/* TimeUnitFormat */

static int t_timeunitformat_init(t_timeunitformat *self,
                                 PyObject *args, PyObject *kwds)
{
#if U_ICU_VERSION_HEX >= 0x04080000
    UTimeUnitFormatStyle style;
#else
    TimeUnitFormat::EStyle style;
#endif
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = new TimeUnitFormat(status));
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(self->object = new TimeUnitFormat(*locale, status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "Pi", TYPE_CLASSID(Locale), &locale, &style))
        {
            INT_STATUS_CALL(self->object = new TimeUnitFormat(*locale, style, status));
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

static PyObject *t_timeunitformat_setLocale(t_timeunitformat *self,
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

static PyObject *t_timeunitformat_setNumberFormat(t_timeunitformat *self,
                                                  PyObject *arg)
{
    NumberFormat *format;

    if (!parseArg(arg, "P", TYPE_CLASSID(NumberFormat), &format)) /* copied */
    {
        STATUS_CALL(self->object->setNumberFormat(*format, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNumberFormat", arg);
}

#endif


/* MessageFormat */

static int t_messageformat_init(t_messageformat *self,
                                PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            MessageFormat *format;

            INT_STATUS_CALL(format = new MessageFormat(*u, status));
            self->object = format;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale), &u, &_u, &locale))
        {
            MessageFormat *format;

            INT_STATUS_PARSER_CALL(format = new MessageFormat(*u, *locale, parseError, status));
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

static PyObject *t_messageformat_getLocale(t_messageformat *self)
{
    return wrap_Locale(self->object->getLocale());
}

static PyObject *t_messageformat_setLocale(t_messageformat *self,
                                           PyObject *arg)
{
    Locale *locale;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        self->object->setLocale(*locale); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLocale", arg);
}

static PyObject *t_messageformat_applyPattern(t_messageformat *self,
                                              PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_PARSER_CALL(self->object->applyPattern(*u, parseError, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_messageformat_toPattern(t_messageformat *self,
                                           PyObject *args)
{
    UnicodeString *u, _u;

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

PyObject *wrap_Format(Format *format)
{
    RETURN_WRAPPED_IF_ISINSTANCE(format, SimpleDateFormat);
    RETURN_WRAPPED_IF_ISINSTANCE(format, MessageFormat);
#if U_ICU_VERSION_HEX >= 0x04000000
    RETURN_WRAPPED_IF_ISINSTANCE(format, PluralFormat);
#endif
#if U_ICU_VERSION_HEX >= 0x04020000
    RETURN_WRAPPED_IF_ISINSTANCE(format, TimeUnitFormat);
#endif
#if U_ICU_VERSION_HEX >= 0x04040000
    RETURN_WRAPPED_IF_ISINSTANCE(format, SelectFormat);
#endif
    RETURN_WRAPPED_IF_ISINSTANCE(format, ChoiceFormat);
    RETURN_WRAPPED_IF_ISINSTANCE(format, DecimalFormat);
    RETURN_WRAPPED_IF_ISINSTANCE(format, RuleBasedNumberFormat);
    return wrap_Format(format, T_OWNED);
}

static PyObject *t_messageformat_getFormats(t_messageformat *self)
{
    int count;
    const Format **formats = self->object->getFormats(count);
    PyObject *list = PyList_New(count);

    for (int i = 0; i < count; i++) {
        PyObject *obj = wrap_Format(formats[i]->clone());
        PyList_SET_ITEM(list, i, obj);
    }

    return list;
}

static PyObject *t_messageformat_setFormats(t_messageformat *self,
                                            PyObject *arg)
{
    const Format **formats;
    int len;

    if (!parseArg(arg, "Q", TYPE_ID(Format), &formats, &len, TYPE_ID(Format)))
    {
        self->object->setFormats(formats, len); /* copied */
        free(formats);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setFormats", arg);
}

static PyObject *t_messageformat_setFormat(t_messageformat *self,
                                           PyObject *args)
{
    Format *format;
    int i;

    if (!parseArgs(args, "iP", TYPE_ID(Format), &i, &format))
    {
        self->object->setFormat(i, *format); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setFormat", args);
}

static PyObject *t_messageformat_format(t_messageformat *self, PyObject *args)
{
    Formattable *f;
    UnicodeString *u, _u;
    FieldPosition *fp, _fp;
    int len, u_len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "R", TYPE_CLASSID(Formattable),
                       &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray))
        {
            STATUS_CALL(
                {
                    self->object->format(f, len, _u, _fp, status);
                    delete[] f;
                });
                
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;

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
        if (!parseArgs(args, "RU", TYPE_CLASSID(Formattable),
                       &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray, &u))
        {
            STATUS_CALL(
                {
                    self->object->format(f, len, *u, _fp, status);
                    delete[] f;
                });

            Py_RETURN_ARG(args, 1);
        }
#if U_ICU_VERSION_HEX >= VERSION_HEX(4, 0, 0)
        if (!parseArgs(args, "TR",
                       TYPE_CLASSID(Formattable),
                       &u, &u_len,
                       &f, &len, TYPE_CLASSID(Formattable), toFormattableArray))
        {
            STATUS_CALL(
                {
                    self->object->format(u, f, len < u_len ? len : u_len,
                                         _u, status);
                    delete[] u;
                    delete[] f;
                });

            return PyUnicode_FromUnicodeString(&_u);
        }
#endif
        break;

      case 3:
       if (!parseArgs(args, "RUP",
                       TYPE_CLASSID(Formattable),
                       TYPE_CLASSID(FieldPosition),
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

    return t_format_format((t_format *) self, args);
}

static PyObject *fromFormattableArray(Formattable *formattables,
                                      int len, int dispose)
{
    PyObject *list = PyList_New(len);
    
    for (int i = 0; i < len; i++)
        PyList_SET_ITEM(list, i, wrap_Formattable(formattables[i]));

    if (dispose)
        delete formattables;

    return list;
}

static PyObject *t_messageformat_parse(t_messageformat *self, PyObject *args)
{
    Formattable *f;
    int len;
    UnicodeString *u;
    UnicodeString _u;
    ParsePosition *pp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(f = self->object->parse(*u, len, status));
            return fromFormattableArray(f, len, 1);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(ParsePosition),
                       &u, &_u, &pp))
        {
            pp->setErrorIndex(-1);
            f = self->object->parse(*u, *pp, len);
            if (pp->getErrorIndex() != -1)
                Py_RETURN_NONE;
            return fromFormattableArray(f, len, 1);
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "parse", args);
}

static PyObject *t_messageformat_formatMessage(PyTypeObject *type,
                                               PyObject *args)
{
    Formattable *f;
    int len;
    UnicodeString *u, *v;
    UnicodeString _u, _v;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SR", TYPE_CLASSID(Formattable),
                       &u, &_u, &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray))
        {
            STATUS_CALL(
                {
                    MessageFormat::format(*u, f, len, _v, status);
                    delete[] f;
                });

            return PyUnicode_FromUnicodeString(&_v);
        }
        break;
      case 3:
        if (!parseArgs(args, "SRU", TYPE_CLASSID(Formattable),
                       &u, &_u, &f, &len, TYPE_CLASSID(Formattable),
                       toFormattableArray, &v))
        {
            STATUS_CALL(
                {
                    MessageFormat::format(*u, f, len, *v, status);
                    delete[] f;
                });

            Py_RETURN_ARG(args, 2);
        }
        break;
    }

    return PyErr_SetArgsError(type, "formatMessage", args);
}

static PyObject *t_messageformat_str(t_messageformat *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_messageformat_mod(t_messageformat *self, PyObject *args)
{
    int len;
    Formattable *f = toFormattableArray(args, &len, TYPE_CLASSID(Formattable));
    UnicodeString _u;
    FieldPosition _fp;

    if (!f)
    {
        PyErr_SetObject(PyExc_TypeError, args);
        return NULL;
    }
    
    STATUS_CALL(
        {
            self->object->format(f, len, _u, _fp, status);
            delete[] f;
        });

    return PyUnicode_FromUnicodeString(&_u);
}


#if U_ICU_VERSION_HEX >= 0x04000000

/* PluralRules */

static int t_pluralrules_init(t_pluralrules *self,
                              PyObject *args, PyObject *kwds)
{
    if (PyTuple_Size(args) == 0)
    {
        INT_STATUS_CALL(self->object = new PluralRules(status));
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_pluralrules_select(t_pluralrules *self, PyObject *arg)
{
    UnicodeString u;
    int32_t n;
    double d;

    if (!parseArg(arg, "i", &n))
        u = self->object->select(n);
    else if (!parseArg(arg, "d", &d))
        u = self->object->select(d);
    else
        return PyErr_SetArgsError((PyObject *) self, "select", arg);
        
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_pluralrules_getKeywords(t_pluralrules *self)
{
    StringEnumeration *se;
    STATUS_CALL(se = self->object->getKeywords(status));

    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_pluralrules_getKeywordOther(t_pluralrules *self)
{
    UnicodeString u = self->object->getKeywordOther();
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_pluralrules_isKeyword(t_pluralrules *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UBool b = self->object->isKeyword(*u);
        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError((PyObject *) self, "isKeyword", arg);
}


static PyObject *t_pluralrules_createRules(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        PluralRules *rules;
        STATUS_CALL(rules = PluralRules::createRules(*u, status));
        return wrap_PluralRules(rules, T_OWNED);
    }

    return PyErr_SetArgsError(type, "createRules", arg);
}

static PyObject *t_pluralrules_createDefaultRules(PyTypeObject *type)
{
    PluralRules *rules;
    STATUS_CALL(rules = PluralRules::createDefaultRules(status));

    return wrap_PluralRules(rules, T_OWNED);
}

static PyObject *t_pluralrules_forLocale(PyTypeObject *type, PyObject *arg)
{
    Locale *locale;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        PluralRules *rules;
        STATUS_CALL(rules = PluralRules::forLocale(*locale, status));
        return wrap_PluralRules(rules, T_OWNED);
    }

    return PyErr_SetArgsError(type, "forLocale", arg);
}

static PyObject *t_pluralrules_richcmp(t_pluralrules *self,
                                       PyObject *arg, int op)
{
    int b = 0;
    PluralRules *rules;

    if (!parseArg(arg, "P", TYPE_CLASSID(PluralRules), &rules))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *rules;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}


/* PluralFormat */

static int t_pluralformat_init(t_pluralformat *self,
                               PyObject *args, PyObject *kwds)
{
    Locale *locale;
    PluralRules *rules;
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = new PluralFormat(status));
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*locale, status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "P", TYPE_CLASSID(PluralRules), &rules))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*rules, status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*u, status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "PP",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(PluralRules),
                       &locale, &rules))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*locale, *rules,
                                                            status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*locale, *u,
                                                            status));
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "PS", TYPE_CLASSID(PluralRules), &rules, &u, &_u))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*rules, *u,
                                                            status));
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "PPS",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(PluralRules),
                       &locale, &rules, &u, &_u))
        {
            INT_STATUS_CALL(self->object = new PluralFormat(*locale, *rules, *u,
                                                            status));
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

static PyObject *t_pluralformat_setLocale(t_pluralformat *self, PyObject *arg)
{
    Locale *locale;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(self->object->setLocale(*locale, status)); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLocale", arg);
}

static PyObject *t_pluralformat_setNumberFormat(t_pluralformat *self,
                                                PyObject *arg)
{
    NumberFormat *format;

    if (!parseArg(arg, "p", TYPE_CLASSID(NumberFormat), &format,
                  &self->numberformat)) /* ref'd */
    {
        STATUS_CALL(self->object->setNumberFormat(format, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNumberFormat", arg);
}

static PyObject *t_pluralformat_toPattern(t_pluralformat *self, PyObject *args)
{
    UnicodeString *u, _u;

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

static PyObject *t_pluralformat_applyPattern(t_pluralformat *self,
                                             PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyPattern(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_pluralformat_format(t_pluralformat *self, PyObject *args)
{
    UnicodeString *u, _u;
    FieldPosition *fp, _fp;
    double d;
    int n;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &n))
        {
            STATUS_CALL(_u = self->object->format(n, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "d", &d))
        {
            STATUS_CALL(_u = self->object->format(d, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "iS", &n, &u, &_u))
        {
            STATUS_CALL(self->object->format(n, *u, _fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "dS", &d, &u, &_u))
        {
            STATUS_CALL(self->object->format(d, *u, _fp, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
      case 3:
        if (!parseArgs(args, "iSP", TYPE_CLASSID(FieldPosition),
                       &n, &u, &_u, &fp))
        {
            STATUS_CALL(self->object->format(n, *u, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "dSP", TYPE_CLASSID(FieldPosition),
                       &d, &u, &_u, &fp))
        {
            STATUS_CALL(self->object->format(d, *u, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return t_format_format((t_format *) self, args);
}

static PyObject *t_pluralformat_str(t_pluralformat *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}

#endif


#if U_ICU_VERSION_HEX >= 0x04040000

/* SelectFormat */

static int t_selectformat_init(t_selectformat *self,
                               PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        SelectFormat *format;

        INT_STATUS_CALL(format = new SelectFormat(*u, status));
        self->object = format;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_selectformat_applyPattern(t_selectformat *self,
                                             PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyPattern(*u, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
}

static PyObject *t_selectformat_toPattern(t_selectformat *self, PyObject *args)
{
    UnicodeString *u, _u;

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

PyObject *t_selectformat_format(t_selectformat *self, PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    Formattable *obj;
    FieldPosition *fp, _fp;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Formattable), &obj))
        {
            STATUS_CALL(self->object->format(*obj, _u1, _fp, status));
            return PyUnicode_FromUnicodeString(&_u1);
        }
        break;
        if (!parseArgs(args, "S", &u0, &_u0, &obj))
        {
            STATUS_CALL(self->object->format(*u0, _u1, _fp, status));
            return PyUnicode_FromUnicodeString(&_u1);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Formattable), &obj, &u1))
        {
            STATUS_CALL(self->object->format(*obj, *u1, _fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "SU", &u0, &_u0, &u1))
        {
            STATUS_CALL(self->object->format(*u0, *u1, _fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "PP",
                       TYPE_CLASSID(Formattable), TYPE_CLASSID(FieldPosition),
                       &obj, &fp))
        {
            STATUS_CALL(self->object->format(*obj, _u1, *fp, status));
            return PyUnicode_FromUnicodeString(&_u1);
        }
        if (!parseArgs(args, "SP", TYPE_CLASSID(FieldPosition), &u0, &_u0, &fp))
        {
            STATUS_CALL(self->object->format(*u0, _u1, *fp, status));
            return PyUnicode_FromUnicodeString(&_u1);
        }
        break;
      case 3:
        if (!parseArgs(args, "PUP",
                       TYPE_CLASSID(Formattable), TYPE_CLASSID(FieldPosition),
                       &obj, &u1, &fp))
        {
            STATUS_CALL(self->object->format(*obj, *u1, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "SUP", TYPE_CLASSID(FieldPosition),
                       &u0, &_u0, &u1, &fp))
        {
            STATUS_CALL(self->object->format(*u0, *u1, *fp, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "format", args);
}

static PyObject *t_selectformat_parseObject(t_selectformat *self,
                                            PyObject *args)
{
    PyErr_SetString(PyExc_NotImplementedError, "SelectFormat.parseObject()");
    return NULL;
}

static PyObject *t_selectformat_str(t_selectformat *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}

#endif


#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)

/* ListFormatter */

static PyObject *t_listformatter_format(t_listformatter *self, PyObject *arg)
{
    UnicodeString *array;
    int count;

    if (!parseArg(arg, "T", &array, &count))
    {
        UnicodeString u;

        STATUS_CALL(self->object->format(array, (int32_t) count, u, status));
        return PyUnicode_FromUnicodeString(&u);
    }

    return PyErr_SetArgsError((PyObject *) self, "format", arg);
}

static PyObject *t_listformatter_createInstance(PyTypeObject *type,
                                                PyObject *args)
{
    ListFormatter *formatter;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(formatter = ListFormatter::createInstance(status));
        return wrap_ListFormatter(formatter, T_OWNED);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(formatter = ListFormatter::createInstance(
                *locale, status));
            return wrap_ListFormatter(formatter, T_OWNED);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createInstance", args);
}

#endif

void _init_format(PyObject *m)
{
    FieldPositionType_.tp_richcompare = (richcmpfunc) t_fieldposition_richcmp;
    ParsePositionType_.tp_richcompare = (richcmpfunc) t_parseposition_richcmp;
    FormatType_.tp_richcompare = (richcmpfunc) t_format_richcmp;
    MessageFormatType_.tp_str = (reprfunc) t_messageformat_str;
    MessageFormatType_.tp_as_number = &t_messageformat_as_number;
    MessageFormatType_.tp_flags |= Py_TPFLAGS_CHECKTYPES;
#if U_ICU_VERSION_HEX >= 0x04000000
    PluralRulesType_.tp_richcompare = (richcmpfunc) t_pluralrules_richcmp;
    PluralFormatType_.tp_str = (reprfunc) t_pluralformat_str;
#endif
#if U_ICU_VERSION_HEX >= 0x04040000
    SelectFormatType_.tp_str = (reprfunc) t_selectformat_str;
#endif

    REGISTER_TYPE(FieldPosition, m);
    REGISTER_TYPE(ParsePosition, m);
    INSTALL_TYPE(Format, m);
    INSTALL_TYPE(MeasureFormat, m);
    REGISTER_TYPE(MessageFormat, m);
#if U_ICU_VERSION_HEX >= 0x04000000
    REGISTER_TYPE(PluralRules, m);
    REGISTER_TYPE(PluralFormat, m);
#endif
#if U_ICU_VERSION_HEX >= 0x04020000
    REGISTER_TYPE(TimeUnitFormat, m);
#endif
#if U_ICU_VERSION_HEX >= 0x04040000
    REGISTER_TYPE(SelectFormat, m);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)
    INSTALL_TYPE(ListFormatter, m);
#endif

    INSTALL_STATIC_INT(FieldPosition, DONT_CARE);

#if U_ICU_VERSION_HEX >= 0x04020000 && U_ICU_VERSION_HEX < 0x04080000
    INSTALL_STATIC_INT(TimeUnitFormat, kFull);
    INSTALL_STATIC_INT(TimeUnitFormat, kAbbreviate);
#endif
#if U_ICU_VERSION_HEX >= 0x04080000
    INSTALL_CONSTANTS_TYPE(UTimeUnitFormatStyle, m);
    INSTALL_ENUM(UTimeUnitFormatStyle, "FULL", UTMUTFMT_FULL_STYLE);
    INSTALL_ENUM(UTimeUnitFormatStyle, "ABBREVIATED", UTMUTFMT_ABBREVIATED_STYLE);
#endif
}
