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

#include "bases.h"
#include "locale.h"
#include "format.h"
#include "macros.h"
#include "dateformat.h"
#include "numberformat.h"

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
             t_fieldposition_init);

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
             t_parseposition_init);

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

DECLARE_TYPE(Format, t_format, UObject, Format, abstract_init);

/* MeasureFormat */

class t_measureformat : public _wrapper {
public:
    MeasureFormat *object;
};

static PyObject *t_measureformat_createCurrencyFormat(PyTypeObject *type,
                                                      PyObject *args);

static PyMethodDef t_measureformat_methods[] = {
    DECLARE_METHOD(t_measureformat, createCurrencyFormat, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(MeasureFormat, t_measureformat, Format, MeasureFormat,
             abstract_init);

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
             t_messageformat_init);


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

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(format = MeasureFormat::createCurrencyFormat(status));
        return wrap_MeasureFormat(format, T_OWNED);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(format = MeasureFormat::createCurrencyFormat(*locale, status));
            return wrap_MeasureFormat(format, T_OWNED);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createCurrencyFormat", args);
}


/* MessageFormat */

static int t_messageformat_init(t_messageformat *self,
                                PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    UnicodeString _u;
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
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale),
                       &u, &_u, &locale))
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
        self->object->setLocale(*locale);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLocale", arg);
}

static PyObject *t_messageformat_applyPattern(t_messageformat *self,
                                              PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

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

PyObject *wrap_Format(Format *format)
{
    UClassID id = format->getDynamicClassID();

    if (id == SimpleDateFormat::getStaticClassID())
        return wrap_SimpleDateFormat((SimpleDateFormat *) format, T_OWNED);

    if (id == MessageFormat::getStaticClassID())
        return wrap_MessageFormat((MessageFormat *) format, T_OWNED);

    if (id == ChoiceFormat::getStaticClassID())
        return wrap_ChoiceFormat((ChoiceFormat *) format, T_OWNED);

    if (id == DecimalFormat::getStaticClassID())
        return wrap_DecimalFormat((DecimalFormat *) format, T_OWNED);

    if (id == RuleBasedNumberFormat::getStaticClassID())
        return wrap_RuleBasedNumberFormat((RuleBasedNumberFormat *) format, T_OWNED);

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
        self->object->setFormats(formats, len);
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
        self->object->setFormat(i, *format);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setFormat", args);
}

static PyObject *t_messageformat_format(t_messageformat *self, PyObject *args)
{
    Formattable *f;
    int len;
    UnicodeString *u;
    UnicodeString _u;
    FieldPosition *fp;
    FieldPosition _fp;

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
        break;
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


void _init_format(PyObject *m)
{
    FieldPositionType.tp_richcompare = (richcmpfunc) t_fieldposition_richcmp;
    ParsePositionType.tp_richcompare = (richcmpfunc) t_parseposition_richcmp;
    FormatType.tp_richcompare = (richcmpfunc) t_format_richcmp;
    MessageFormatType.tp_str = (reprfunc) t_messageformat_str;
    MessageFormatType.tp_as_number = &t_messageformat_as_number;
    MessageFormatType.tp_flags |= Py_TPFLAGS_CHECKTYPES;

    REGISTER_TYPE(FieldPosition, m);
    REGISTER_TYPE(ParsePosition, m);
    INSTALL_TYPE(Format, m);
    INSTALL_TYPE(MeasureFormat, m);
    REGISTER_TYPE(MessageFormat, m);

    INSTALL_STATIC_INT(FieldPosition, DONT_CARE);
}
