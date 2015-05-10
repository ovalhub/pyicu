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
#include "iterators.h"
#include "macros.h"


/* UObject */

static PyObject *t_uobject_new(PyTypeObject *type,
                               PyObject *args, PyObject *kwds);

static PyObject *t_uobject_richcmp(t_uobject *, PyObject *o2, int op);
static PyObject *t_uobject_str(t_uobject *self);
static PyObject *t_uobject_repr(t_uobject *self);
static PyObject *t_uobject_getDynamicClassID(t_uobject *self);
static PyObject *t_uobject__getOwned(t_uobject *self, void *data);

static PyMemberDef t_uobject_members[] = {
    { NULL, 0, 0, 0, NULL }
};

static PyMethodDef t_uobject_methods[] = {
    DECLARE_METHOD(t_uobject, getDynamicClassID, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef t_uobject_properties[] = {
    { (char *) "owned", (getter) t_uobject__getOwned, NULL, (char *) "", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject UObjectType_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "icu.UObject",                       /* tp_name */
    sizeof(t_uobject),                   /* tp_basicsize */
    0,                                   /* tp_itemsize */
    (destructor)t_uobject_dealloc,       /* tp_dealloc */
    0,                                   /* tp_print */
    0,                                   /* tp_getattr */
    0,                                   /* tp_setattr */
    0,                                   /* tp_compare */
    (reprfunc)t_uobject_repr,            /* tp_repr */
    0,                                   /* tp_as_number */
    0,                                   /* tp_as_sequence */
    0,                                   /* tp_as_mapping */
    0,                                   /* tp_hash  */
    0,                                   /* tp_call */
    (reprfunc)t_uobject_str,             /* tp_str */
    0,                                   /* tp_getattro */
    0,                                   /* tp_setattro */
    0,                                   /* tp_as_buffer */
    (Py_TPFLAGS_DEFAULT |
     Py_TPFLAGS_BASETYPE),               /* tp_flags */
    "t_uobject objects",                 /* tp_doc */
    0,                                   /* tp_traverse */
    0,                                   /* tp_clear */
    (richcmpfunc)t_uobject_richcmp,      /* tp_richcompare */
    0,                                   /* tp_weaklistoffset */
    0,                                   /* tp_iter */
    0,                                   /* tp_iternext */
    t_uobject_methods,                   /* tp_methods */
    t_uobject_members,                   /* tp_members */
    t_uobject_properties,                /* tp_getset */
    0,                                   /* tp_base */
    0,                                   /* tp_dict */
    0,                                   /* tp_descr_get */
    0,                                   /* tp_descr_set */
    0,                                   /* tp_dictoffset */
    (initproc)abstract_init,             /* tp_init */
    0,                                   /* tp_alloc */
    (newfunc)t_uobject_new,              /* tp_new */
};

PyObject *wrap_UObject(UObject *object, int flags)
{
    if (object)
    {
        if (ISINSTANCE(object, UnicodeString))
            return PyUnicode_FromUnicodeString((UnicodeString *) object);

        t_uobject *self = (t_uobject *) UObjectType_.tp_alloc(&UObjectType_, 0);
        if (self)
        {
            self->object = object;
            self->flags = flags;
        }

        return (PyObject *) self;
    }

    Py_RETURN_NONE;
}

static PyObject *t_uobject__getOwned(t_uobject *self, void *data)
{
    int b = self->flags & T_OWNED;
    Py_RETURN_BOOL(b);
}

/* Replaceable */

class t_replaceable : public _wrapper {
public:
    Replaceable *object;
};

static PyObject *t_replaceable_length(t_replaceable *self);
static PyObject *t_replaceable_charAt(t_replaceable *self, PyObject *arg);
static PyObject *t_replaceable_char32At(t_replaceable *self, PyObject *arg);
static PyObject *t_replaceable_hasMetaData(t_replaceable *self);

static PyMethodDef t_replaceable_methods[] = {
    DECLARE_METHOD(t_replaceable, length, METH_NOARGS),
    DECLARE_METHOD(t_replaceable, charAt, METH_O),
    DECLARE_METHOD(t_replaceable, char32At, METH_O),
    DECLARE_METHOD(t_replaceable, hasMetaData, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Replaceable, t_replaceable, UObject, Replaceable,
             abstract_init, NULL);

/* UnicodeString */

class t_unicodestring : public _wrapper {
public:
    UnicodeString *object;
};

static int t_unicodestring_init(t_unicodestring *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_unicodestring_getAvailableStandards(PyTypeObject *type);
static PyObject *t_unicodestring_getAvailableEncodings(PyTypeObject *type,
                                                       PyObject *args);
static PyObject *t_unicodestring_getStandardEncoding(PyTypeObject *type,
                                                     PyObject *args);
static PyObject *t_unicodestring_append(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_compare(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_compareBetween(t_unicodestring *self,
                                                PyObject *args);
static PyObject *t_unicodestring_compareCodePointOrder(t_unicodestring *self,
                                                       PyObject *args);
static PyObject *t_unicodestring_compareCodePointOrderBetween(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_caseCompare(t_unicodestring *self,
                                             PyObject *args);
static PyObject *t_unicodestring_caseCompareBetween(t_unicodestring *self,
                                                    PyObject *args);
static PyObject *t_unicodestring_startsWith(t_unicodestring *self,
                                            PyObject *args);
static PyObject *t_unicodestring_endsWith(t_unicodestring *self,
                                          PyObject *args);
#define t_unicodestring_startswith t_unicodestring_startsWith
#define t_unicodestring_endswith t_unicodestring_endsWith
static PyObject *t_unicodestring_indexOf(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_lastIndexOf(t_unicodestring *self,
                                             PyObject *args);
static PyObject *t_unicodestring_trim(t_unicodestring *self);
static PyObject *t_unicodestring_reverse(t_unicodestring *self);
static PyObject *t_unicodestring_toUpper(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_toLower(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_toTitle(t_unicodestring *self, PyObject *args);
static PyObject *t_unicodestring_foldCase(t_unicodestring *self,
                                          PyObject *args);
static PyObject *t_unicodestring_isBogus(t_unicodestring *self);
static PyObject *t_unicodestring_encode(t_unicodestring *self, PyObject *arg);

#if U_ICU_VERSION_HEX < VERSION_HEX(55, 1, 0)
static PyObject *t_unicodestring_idna_toASCII(t_unicodestring *self,
                                              PyObject *args);
static PyObject *t_unicodestring_idna_toUnicode(t_unicodestring *self,
                                                PyObject *args);
static PyObject *t_unicodestring_idna_IDNtoASCII(t_unicodestring *self,
                                                 PyObject *args);
static PyObject *t_unicodestring_idna_IDNtoUnicode(t_unicodestring *self,
                                                   PyObject *args);
static PyObject *t_unicodestring_idna_compare(t_unicodestring *self,
                                              PyObject *args);
#endif

static PyMethodDef t_unicodestring_methods[] = {
    DECLARE_METHOD(t_unicodestring, getAvailableStandards, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_unicodestring, getAvailableEncodings, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_unicodestring, getStandardEncoding, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_unicodestring, append, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, compare, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, compareBetween, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, compareCodePointOrder, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, compareCodePointOrderBetween, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, caseCompare, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, caseCompareBetween, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, startsWith, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, endsWith, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, startswith, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, endswith, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, indexOf, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, lastIndexOf, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, trim, METH_NOARGS),
    DECLARE_METHOD(t_unicodestring, reverse, METH_NOARGS),
    DECLARE_METHOD(t_unicodestring, toUpper, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, toLower, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, toTitle, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, foldCase, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, isBogus, METH_NOARGS),
    DECLARE_METHOD(t_unicodestring, encode, METH_O),

#if U_ICU_VERSION_HEX < VERSION_HEX(55, 1, 0)
    DECLARE_METHOD(t_unicodestring, idna_toASCII, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, idna_toUnicode, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, idna_IDNtoASCII, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, idna_IDNtoUnicode, METH_VARARGS),
    DECLARE_METHOD(t_unicodestring, idna_compare, METH_VARARGS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UnicodeString, t_unicodestring, Replaceable, UnicodeString,
             t_unicodestring_init, NULL);

/* Formattable */

class t_formattable : public _wrapper {
public:
    Formattable *object;
};

static int t_formattable_init(t_formattable *self,
                              PyObject *args, PyObject *kwds);
static PyObject *t_formattable_isNumeric(t_formattable *self);
static PyObject *t_formattable_getType(t_formattable *self);
static PyObject *t_formattable_getDouble(t_formattable *self);
static PyObject *t_formattable_getLong(t_formattable *self);
static PyObject *t_formattable_getInt64(t_formattable *self);
static PyObject *t_formattable_getDate(t_formattable *self);
static PyObject *t_formattable_getString(t_formattable *self, PyObject *args);
static PyObject *t_formattable_setDouble(t_formattable *self, PyObject *arg);
static PyObject *t_formattable_setLong(t_formattable *self, PyObject *arg);
static PyObject *t_formattable_setInt64(t_formattable *self, PyObject *arg);
static PyObject *t_formattable_setDate(t_formattable *self, PyObject *arg);
static PyObject *t_formattable_setString(t_formattable *self, PyObject *arg);

static PyMethodDef t_formattable_methods[] = {
    DECLARE_METHOD(t_formattable, isNumeric, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getType, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getDouble, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getLong, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getInt64, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getDate, METH_NOARGS),
    DECLARE_METHOD(t_formattable, getString, METH_VARARGS),
    DECLARE_METHOD(t_formattable, setDouble, METH_O),
    DECLARE_METHOD(t_formattable, setLong, METH_O),
    DECLARE_METHOD(t_formattable, setInt64, METH_O),
    DECLARE_METHOD(t_formattable, setDate, METH_O),
    DECLARE_METHOD(t_formattable, setString, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Formattable, t_formattable, UObject, Formattable,
             t_formattable_init, NULL);

PyObject *wrap_Formattable(Formattable &formattable)
{
    return wrap_Formattable(new Formattable(formattable), T_OWNED);
}


/* MeasureUnit */

class t_measureunit : public _wrapper {
public:
    MeasureUnit *object;
};

static PyMethodDef t_measureunit_methods[] = {
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(MeasureUnit, t_measureunit, UObject, MeasureUnit,
             abstract_init, NULL);

/* Measure */

class t_measure : public _wrapper {
public:
    Measure *object;
};

static PyObject *t_measure_getNumber(t_measure *self);
static PyObject *t_measure_getUnit(t_measure *self);

static PyMethodDef t_measure_methods[] = {
    DECLARE_METHOD(t_measure, getNumber, METH_NOARGS),
    DECLARE_METHOD(t_measure, getUnit, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Measure, t_measure, UObject, Measure, abstract_init, NULL);

/* CurrencyUnit */

class t_currencyunit : public _wrapper {
public:
    CurrencyUnit *object;
};

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self);

static PyMethodDef t_currencyunit_methods[] = {
    DECLARE_METHOD(t_currencyunit, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyUnit, t_currencyunit, MeasureUnit, CurrencyUnit,
             t_currencyunit_init, NULL);

/* CurrencyAmount */

class t_currencyamount : public _wrapper {
public:
    CurrencyAmount *object;
};

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_currencyamount_getCurrency(t_currencyamount *self);
static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self);

static PyMethodDef t_currencyamount_methods[] = {
    DECLARE_METHOD(t_currencyamount, getCurrency, METH_NOARGS),
    DECLARE_METHOD(t_currencyamount, getISOCurrency, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CurrencyAmount, t_currencyamount, Measure, CurrencyAmount,
             t_currencyamount_init, NULL);

/* StringEnumeration */

class t_stringenumeration : public _wrapper {
public:
    StringEnumeration *object;
};

static PyObject *t_stringenumeration_count(t_stringenumeration *self);
static PyObject *t_stringenumeration_reset(t_stringenumeration *self);
static PyObject *t_stringenumeration_next(t_stringenumeration *self);
static PyObject *t_stringenumeration_unext(t_stringenumeration *self);
static PyObject *t_stringenumeration_snext(t_stringenumeration *self);

static PyMethodDef t_stringenumeration_methods[] = {
    DECLARE_METHOD(t_stringenumeration, count, METH_NOARGS),
    DECLARE_METHOD(t_stringenumeration, reset, METH_NOARGS),
    DECLARE_METHOD(t_stringenumeration, next, METH_NOARGS),
    DECLARE_METHOD(t_stringenumeration, unext, METH_NOARGS),
    DECLARE_METHOD(t_stringenumeration, snext, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(StringEnumeration, t_stringenumeration, UObject,
             StringEnumeration, abstract_init, NULL);


/* UObject */

void t_uobject_dealloc(t_uobject *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject *t_uobject_new(PyTypeObject *type,
                               PyObject *args, PyObject *kwds)
{
    t_uobject *self = (t_uobject *) type->tp_alloc(type, 0);

    if (self)
    {
        self->object = NULL;
        self->flags = 0;
    }

    return (PyObject *) self;
}

static PyObject *t_uobject_richcmp(t_uobject *self, PyObject *arg, int op)
{
    int b = 0;

    switch (op) {
      case Py_EQ:
      case Py_NE:
        if (PyObject_TypeCheck(arg, &UObjectType_))
            b = self->object == ((t_uobject *) arg)->object;
        if (op == Py_EQ)
            Py_RETURN_BOOL(b);
        Py_RETURN_BOOL(!b);
      case Py_LT:
        PyErr_SetString(PyExc_NotImplementedError, "<");
        return NULL;
      case Py_LE:
        PyErr_SetString(PyExc_NotImplementedError, "<=");
        return NULL;
      case Py_GT:
        PyErr_SetString(PyExc_NotImplementedError, ">");
        return NULL;
      case Py_GE:
        PyErr_SetString(PyExc_NotImplementedError, ">=");
        return NULL;
    }

    return NULL;
}

static PyObject *t_uobject_str(t_uobject *self)
{
    if (self->object)
    {
        char buf[32];
#if U_ICU_VERSION_HEX < 0x04060000
        sprintf(buf, "0x%lx",
		(unsigned long) self->object->getDynamicClassID());
#else
        sprintf(buf, "0x%llx",
		(unsigned long long) (intptr_t) self->object);
#endif
        return PyString_FromString(buf);
    }

    return PyString_FromString("<null>");
}

static PyObject *t_uobject_repr(t_uobject *self)
{
    PyObject *name = PyObject_GetAttrString((PyObject *) Py_TYPE(self),
                                            "__name__");
    PyObject *str = Py_TYPE(self)->tp_str((PyObject *) self);
#if PY_VERSION_HEX < 0x02040000
    PyObject *args = Py_BuildValue("(OO)", name, str);
#else
    PyObject *args = PyTuple_Pack(2, name, str);
#endif
    PyObject *format = PyString_FromString("<%s: %s>");
    PyObject *repr = PyString_Format(format, args);

    Py_DECREF(name);
    Py_DECREF(str);
    Py_DECREF(args);
    Py_DECREF(format);

    return repr;
}

static PyObject *t_uobject_getDynamicClassID(t_uobject *self)
{
    return PyInt_FromLong((long) self->object->getDynamicClassID());
}


/* Replaceable */

static PyObject *t_replaceable_length(t_replaceable *self)
{
    return PyInt_FromLong(self->object->length());
}

static PyObject *t_replaceable_charAt(t_replaceable *self, PyObject *arg)
{
    int32_t i;

    if (!parseArg(arg, "i", &i))
    {
        if (i >= 0 && self->object->length())
            return PyInt_FromLong(self->object->charAt(i));
        else
        {
            PyErr_SetObject(PyExc_IndexError, arg);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "charAt", arg);
}

static PyObject *t_replaceable_char32At(t_replaceable *self, PyObject *arg)
{
    int32_t i;

    if (!parseArg(arg, "i", &i))
    {
        if (i >= 0 && self->object->length())
            return PyInt_FromLong(self->object->char32At(i));
        else
        {
            PyErr_SetObject(PyExc_IndexError, arg);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "char32At", arg);
}

static PyObject *t_replaceable_hasMetaData(t_replaceable *self)
{
    int b = self->object->hasMetaData();
    Py_RETURN_BOOL(b);
}


/* UnicodeString */

static int t_unicodestring_init(t_unicodestring *self,
                                PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    PyObject *obj;
    charsArg encoding, mode;
    int32_t start, length;
    int i;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new UnicodeString();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "u", &u))
        {
            self->object = u;
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object = new UnicodeString(*u);
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "i", &i))
        {
            self->object = new UnicodeString((UChar32) i);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "Cn", &obj, &encoding))
        {
            UnicodeString u;

            try {
                PyObject_AsUnicodeString(obj, encoding, "strict", u);
                self->object = new UnicodeString(u);
                self->flags = T_OWNED;
            } catch (ICUException e) {
                e.reportError();
                return -1;
            }
            break;
        }
        if (!parseArgs(args, "Si", &u, &_u, &start))
        {
            self->object = new UnicodeString(*u, start);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "Cnn", &obj, &encoding, &mode))
        {
            try {
                PyObject_AsUnicodeString(obj, encoding, mode, _u);
                self->object = new UnicodeString(_u);
                self->flags = T_OWNED;
            } catch (ICUException e) {
                e.reportError();
                return -1;
            }
            break;
        }
        if (!parseArgs(args, "Sii", &u, &_u, &start, &length))
        {
            self->object = new UnicodeString(*u, start, length);
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

static PyObject *t_unicodestring_getAvailableStandards(PyTypeObject *type)
{
    UErrorCode status = U_ZERO_ERROR;
    int count = ucnv_countStandards();
    PyObject *list = PyList_New(count);

    for (int i = 0; i < count; i++) {
        const char *name = ucnv_getStandard(i, &status);
        PyList_SetItem(list, i, PyString_FromString(name));
    }

    return list;
}

static PyObject *t_unicodestring_getAvailableEncodings(PyTypeObject *type,
                                                       PyObject *args)
{
    charsArg standard;

    switch (PyTuple_Size(args)) {
      case 0:
        break;
      case 1:
        if (!parseArgs(args, "n", &standard))
            break;
      default:
        return PyErr_SetArgsError(type, "getAvailableEncodings", args);
    }
        
    int count = ucnv_countAvailable();
    PyObject *list = PyList_New(0);

    for (int i = 0; i < count; i++) {
        const char *name = ucnv_getAvailableName(i);

        if (standard)
        {
            UErrorCode status = U_ZERO_ERROR;
            name = ucnv_getStandardName(name, standard, &status);
        }

        if (name)
            PyList_Append(list, PyString_FromString(name));
    }

    return list;
}

static PyObject *t_unicodestring_getStandardEncoding(PyTypeObject *type,
                                                     PyObject *args)
{
    charsArg name, standard;

    if (!parseArgs(args, "nn", &name, &standard))
    {
        UErrorCode status = U_ZERO_ERROR;
        const char *standardName =
            ucnv_getStandardName(name, standard, &status);

        if (standardName)
            return PyString_FromString(standardName);

        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError(type, "getStandardEncodings", args);
}

static int verifyStart(int &start, int size)
{
    if (start < 0)
    {
        start += size;
        if (start < 0)
            return -1;
    }

    return 0;
}

static int verifyStartLen(int &start, int &len, int size)
{
    if (start < 0)
    {
        start += size;
        if (start < 0)
            return -1;
    }

    if (len < 0)
        len = 0;
    else if (len > size - start)
        len = size - start;

    return 0;
}

static int verifyStartEnd(int &start, int &end, int len)
{
    if (start < 0)
    {
        start += len;
        if (start < 0)
            return -1;
    }
    else if (start > len)
        start = len;

    if (end < 0)
    {
        end += len;
        if (end < 0)
            return -1;
    }
    else if (end > len)
        end = len;

    return 0;
}

static PyObject *t_unicodestring_append(t_unicodestring *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int i, start, len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            self->object->append(*u);

            Py_INCREF(self);
            return (PyObject *) self;
        }
        if (!parseArgs(args, "i", &i))
        {
            if (sizeof(Py_UNICODE) == sizeof(UChar))
                self->object->append((UChar) i);
            else
                self->object->append((UChar32) i);

            Py_INCREF(self);
            return (PyObject *) self;
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &len))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                self->object->append(*u, start, len);

                Py_INCREF(self);
                return (PyObject *) self;
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "append", args);
}

static PyObject *t_unicodestring_compare(t_unicodestring *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int c = self->object->compare(*u);
            return PyInt_FromLong(c);
        }
        break;
      case 3:
        if (!parseArgs(args, "iiS", &start, &len, &u, &_u))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                int c = self->object->compare(start, len, *u);
                return PyInt_FromLong(c);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "compare", args);
}

static PyObject *t_unicodestring_compareBetween(t_unicodestring *self,
                                                PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, end, srcStart, srcEnd;

    if (!parseArgs(args, "iiSii", &start, &end, &u, &_u, &srcStart, &srcEnd))
    {
        if (!verifyStartEnd(start, end, self->object->length()) &&
            !verifyStartEnd(srcStart, srcEnd, u->length()))
        {
            int c = self->object->compareBetween(start, end, *u,
                                                 srcStart, srcEnd);
            return PyInt_FromLong(c);
        }
        
        PyErr_SetObject(PyExc_IndexError, args);
        return NULL;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "compareBetween", args);
}

static PyObject *t_unicodestring_compareCodePointOrder(t_unicodestring *self,
                                                       PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int c = self->object->compareCodePointOrder(*u);
            return PyInt_FromLong(c);
        }
        break;
      case 3:
        if (!parseArgs(args, "iiS", &start, &len, &u, &_u))
        {
            if (!verifyStartLen(start, len, self->object->length()))
            {
                int c = self->object->compareCodePointOrder(start, len, *u);
                return PyInt_FromLong(c);
            }

            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "compareCodePointOrder", args);
}

static PyObject *t_unicodestring_compareCodePointOrderBetween(t_unicodestring *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, end, srcStart, srcEnd;

    if (!parseArgs(args, "iiSii", &start, &end, &u, &_u, &srcStart, &srcEnd))
    {
        if (!verifyStartEnd(start, end, self->object->length()) &&
            !verifyStartEnd(srcStart, srcEnd, u->length()))
        {
            int c = self->object->compareCodePointOrderBetween(start, end, *u, srcStart, srcEnd);
            return PyInt_FromLong(c);
        }
        
        PyErr_SetObject(PyExc_IndexError, args);
        return NULL;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "compareCodePointOrderBetween",
                              args);
}

static PyObject *t_unicodestring_caseCompare(t_unicodestring *self,
                                             PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, len, options;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &options))
        {
            int c = self->object->caseCompare(*u, options);
            return PyInt_FromLong(c);
        }
        break;
      case 4:
        if (!parseArgs(args, "iiSi", &start, &len, &u, &_u, &options))
        {
            if (!verifyStartLen(start, len, self->object->length()))
            {
                int c = self->object->caseCompare(start, len, *u, options);
                return PyInt_FromLong(c);
            }

            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "caseCompare", args);
}

static PyObject *t_unicodestring_caseCompareBetween(t_unicodestring *self,
                                                    PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, end, srcStart, srcEnd, options;

    if (!parseArgs(args, "iiSiii", &start, &end, &u, &_u, &srcStart, &srcEnd,
                   &options))
    {
        if (!verifyStartEnd(start, end, self->object->length()) &&
            !verifyStartEnd(srcStart, srcEnd, u->length()))
        {
            int c = self->object->caseCompareBetween(start, end, *u,
                                                     srcStart, srcEnd, options);
            return PyInt_FromLong(c);
        }
        
        PyErr_SetObject(PyExc_IndexError, args);
        return NULL;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "caseCompareBetween", args);
}

static PyObject *t_unicodestring_startsWith(t_unicodestring *self,
                                            PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int b = self->object->startsWith(*u);
            Py_RETURN_BOOL(b);
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &len))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                int b = self->object->startsWith(*u, start, len);
                Py_RETURN_BOOL(b);
            }

            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "startsWith", args);
}

static PyObject *t_unicodestring_endsWith(t_unicodestring *self,
                                          PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int start, len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int b = self->object->endsWith(*u);
            Py_RETURN_BOOL(b);
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &len))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                int b = self->object->endsWith(*u, start, len);
                Py_RETURN_BOOL(b);
            }

            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
    }
    
    return PyErr_SetArgsError((PyObject *) self, "endsWith", args);
}

static PyObject *t_unicodestring_indexOf(t_unicodestring *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int c, start, len, srcStart, srcLen;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int i = self->object->indexOf(*u);
            return PyInt_FromLong(i);
        }
        if (!parseArgs(args, "i", &c))
        {
            int i;

            if (sizeof(Py_UNICODE) == sizeof(UChar))
                i = self->object->indexOf((UChar) c);
            else
                i = self->object->indexOf((UChar32) c);

            return PyInt_FromLong(i);
        }
        break;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &start))
        {
            if (!verifyStart(start, u->length()))
            {
                int i = self->object->indexOf(*u, start);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        if (!parseArgs(args, "ii", &c, &start))
        {
            if (!verifyStart(start, self->object->length()))
            {
                int i;

                if (sizeof(Py_UNICODE) == sizeof(UChar))
                    i = self->object->indexOf((UChar) c, start);
                else
                    i = self->object->indexOf((UChar32) c, start);

                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &len))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                int i = self->object->indexOf(*u, start, len);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        if (!parseArgs(args, "iii", &c, &start, &len))
        {
            if (!verifyStartLen(start, len, self->object->length()))
            {
                int i;

                if (sizeof(Py_UNICODE) == sizeof(UChar))
                    i = self->object->indexOf((UChar) c, start, len);
                else
                    i = self->object->indexOf((UChar32) c, start, len);

                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
      case 5:
        if (!parseArgs(args, "Siiii", &u, &_u,
                       &srcStart, &srcLen, &start, &len))
        {
            if (!verifyStartLen(srcStart, srcLen, u->length()) &&
                !verifyStartLen(start, len, self->object->length()))
            {
                int i = self->object->indexOf(*u, srcStart, srcLen, start, len);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "indexOf", args);
}

static PyObject *t_unicodestring_lastIndexOf(t_unicodestring *self,
                                             PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int c, start, len, srcStart, srcLen;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            int i = self->object->lastIndexOf(*u);
            return PyInt_FromLong(i);
        }
        if (!parseArgs(args, "i", &c))
        {
            int i;

            if (sizeof(Py_UNICODE) == sizeof(UChar))
                i = self->object->lastIndexOf((UChar) c);
            else
                i = self->object->lastIndexOf((UChar32) c);

            return PyInt_FromLong(i);
        }
        break;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &start))
        {
            if (!verifyStart(start, u->length()))
            {
                int i = self->object->lastIndexOf(*u, start);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        if (!parseArgs(args, "ii", &c, &start))
        {
            if (!verifyStart(start, self->object->length()))
            {
                int i;

                if (sizeof(Py_UNICODE) == sizeof(UChar))
                    i = self->object->lastIndexOf((UChar) c, start);
                else
                    i = self->object->lastIndexOf((UChar32) c, start);

                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &len))
        {
            if (!verifyStartLen(start, len, u->length()))
            {
                int i = self->object->lastIndexOf(*u, start, len);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        if (!parseArgs(args, "iii", &c, &start, &len))
        {
            if (!verifyStartLen(start, len, self->object->length()))
            {
                int i;

                if (sizeof(Py_UNICODE) == sizeof(UChar))
                    i = self->object->lastIndexOf((UChar) c, start, len);
                else
                    i = self->object->lastIndexOf((UChar32) c, start, len);

                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
        break;
      case 5:
        if (!parseArgs(args, "Siiii", &u, &_u,
                       &srcStart, &srcLen, &start, &len))
        {
            if (!verifyStartLen(srcStart, srcLen, u->length()) &&
                !verifyStartLen(start, len, self->object->length()))
            {
                int i = self->object->lastIndexOf(*u, srcStart, srcLen,
                                                  start, len);
                return PyInt_FromLong(i);
            }
            PyErr_SetObject(PyExc_IndexError, args);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "lastIndexOf", args);
}

static PyObject *t_unicodestring_trim(t_unicodestring *self)
{
    self->object->trim();
    Py_RETURN_SELF();
}

static PyObject *t_unicodestring_reverse(t_unicodestring *self)
{
    self->object->reverse();
    Py_RETURN_SELF();
}

static PyObject *t_unicodestring_toUpper(t_unicodestring *self, PyObject *args)
{
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toUpper();
        Py_RETURN_SELF();
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->toUpper(*locale);
            Py_RETURN_SELF();
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toUpper", args);
}

static PyObject *t_unicodestring_toLower(t_unicodestring *self, PyObject *args)
{
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toLower();
        Py_RETURN_SELF();
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->toLower(*locale);
            Py_RETURN_SELF();
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toLower", args);
}

static PyObject *t_unicodestring_toTitle(t_unicodestring *self, PyObject *args)
{
    BreakIterator *iterator;
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toTitle(NULL);
        Py_RETURN_SELF();
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->toTitle(NULL, *locale);
            Py_RETURN_SELF();
        }
        if (!parseArg(args, "P", TYPE_ID(BreakIterator), &iterator))
        {
            self->object->toTitle(iterator);
            Py_RETURN_SELF();
        }
        break;
      case 2:
        if (!parseArgs(args, "PP", TYPE_ID(BreakIterator),
                       TYPE_CLASSID(Locale), &iterator, &locale))
        {
            self->object->toTitle(iterator, *locale);
            Py_RETURN_SELF();
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toTitle", args);
}

static PyObject *t_unicodestring_foldCase(t_unicodestring *self, PyObject *args)
{
    int i;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->foldCase(0);
        Py_RETURN_SELF();
      case 1:
        if (!parseArgs(args, "i", &i))
        {
            self->object->foldCase(i);
            Py_RETURN_SELF();
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "foldCase", args);
}

static PyObject *t_unicodestring_isBogus(t_unicodestring *self)
{
    int b = self->object->isBogus();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodestring_str(t_unicodestring *self)
{
    return PyUnicode_FromUnicodeString(self->object);
}

static PyObject *t_unicodestring_repr(t_unicodestring *self)
{
    PyObject *name = PyObject_GetAttrString((PyObject *) Py_TYPE(self),
                                            "__name__");
    PyObject *str = PyUnicode_FromUnicodeString(self->object);

    if (str)
    {
        PyObject *repr = str->ob_type->tp_repr(str);
        Py_DECREF(str);
        str = repr;
    }
    if (!str)
        return NULL;
    
#if PY_VERSION_HEX < 0x02040000
    PyObject *args = Py_BuildValue("(OO)", name, str);
#else
    PyObject *args = PyTuple_Pack(2, name, str);
#endif
    PyObject *format = PyString_FromString("<%s: %s>");
    PyObject *repr = PyString_Format(format, args);

    Py_DECREF(name);
    Py_DECREF(str);
    Py_DECREF(args);
    Py_DECREF(format);

    return repr;
}

static long t_unicodestring_hash(t_unicodestring *self)
{
  return (long) self->object->hashCode();
}


static PyObject *t_unicodestring_encode(t_unicodestring *self, PyObject *arg)
{
    charsArg encoding;

    if (!parseArg(arg, "n", &encoding))
    {
        int srcLen = self->object->length();
        int dstLen = srcLen * 4, _dstLen;
        UErrorCode status = U_ZERO_ERROR;
        UConverter *conv = ucnv_open(encoding, &status);
        PyObject *string;

        if (U_FAILURE(status))
            return ICUException(status).reportError();

        string = PyBytes_FromStringAndSize(NULL, dstLen);

      retry:
        if (!string)
        {
            ucnv_close(conv);
            return NULL;
        }

        _dstLen = ucnv_fromUChars(conv, PyBytes_AS_STRING(string), dstLen,
                                  self->object->getBuffer(), srcLen, &status);

        if (status == U_BUFFER_OVERFLOW_ERROR && _dstLen > dstLen)
        {
            _PyBytes_Resize(&string, _dstLen);
            dstLen = _dstLen;
            status = U_ZERO_ERROR;

            goto retry;
        }

        ucnv_close(conv);

        if (U_FAILURE(status))
        {
            Py_DECREF(string);
            return ICUException(status).reportError();
        }

        if (_dstLen != dstLen)
            _PyBytes_Resize(&string, _dstLen);

        return string;
    }

    return PyErr_SetArgsError((PyObject *) self, "encode", arg);
}

#if U_ICU_VERSION_HEX < VERSION_HEX(55, 1, 0)

static PyObject *t_unicodestring_idna_toASCII(t_unicodestring *self,
                                              PyObject *args)
{
    UErrorCode status = U_ZERO_ERROR;
    UParseError parseError;
    int options = UIDNA_DEFAULT;
    int len = self->object->length();
    UnicodeString *u;
    UChar *dest;

    if (!PyArg_ParseTuple(args, "|i", &options))
        return NULL;

    dest = new UChar[len * 4 + 32];
    if (!dest)
    {
        PyErr_SetNone(PyExc_MemoryError);
        return NULL;
    }

    len = uidna_toASCII(self->object->getBuffer(), len,
                        dest, len * 4 + 32, options, &parseError, &status);

    if (U_FAILURE(status))
    {
        delete dest;
        return ICUException(parseError, status).reportError();
    }

    u = new UnicodeString(dest, len);
    delete dest;

    return wrap_UnicodeString(u, T_OWNED);
}

static PyObject *t_unicodestring_idna_toUnicode(t_unicodestring *self,
                                                PyObject *args)
{
    UErrorCode status = U_ZERO_ERROR;
    UParseError parseError;
    int options = UIDNA_DEFAULT;
    int len = self->object->length();
    UnicodeString *u;
    UChar *dest;

    if (!PyArg_ParseTuple(args, "|i", &options))
        return NULL;

    dest = new UChar[len];
    if (!dest)
    {
        PyErr_SetNone(PyExc_MemoryError);
        return NULL;
    }

    len = uidna_toUnicode(self->object->getBuffer(), len,
                          dest, len, options, &parseError, &status);

    if (U_FAILURE(status))
    {
        delete dest;
        return ICUException(parseError, status).reportError();
    }

    u = new UnicodeString(dest, len);
    delete dest;

    return wrap_UnicodeString(u, T_OWNED);
}

static PyObject *t_unicodestring_idna_IDNtoASCII(t_unicodestring *self,
                                                 PyObject *args)
{
    UErrorCode status = U_ZERO_ERROR;
    UParseError parseError;
    int options = UIDNA_DEFAULT;
    int len = self->object->length();
    UnicodeString *u;
    UChar *dest;

    if (!PyArg_ParseTuple(args, "|i", &options))
        return NULL;

    dest = new UChar[len * 4 + 32];
    if (!dest)
    {
        PyErr_SetNone(PyExc_MemoryError);
        return NULL;
    }

    len = uidna_IDNToASCII(self->object->getBuffer(), len,
                           dest, len * 4 + 32, options, &parseError, &status);

    if (U_FAILURE(status))
    {
        delete dest;
        return ICUException(parseError, status).reportError();
    }

    u = new UnicodeString(dest, len);
    delete dest;

    return wrap_UnicodeString(u, T_OWNED);
}

static PyObject *t_unicodestring_idna_IDNtoUnicode(t_unicodestring *self,
                                                   PyObject *args)
{
    UErrorCode status = U_ZERO_ERROR;
    UParseError parseError;
    int options = UIDNA_DEFAULT;
    int len = self->object->length();
    UnicodeString *u;
    UChar *dest;

    if (!PyArg_ParseTuple(args, "|i", &options))
        return NULL;

    dest = new UChar[len];
    if (!dest)
    {
        PyErr_SetNone(PyExc_MemoryError);
        return NULL;
    }

    len = uidna_IDNToUnicode(self->object->getBuffer(), len,
                             dest, len, options, &parseError, &status);

    if (U_FAILURE(status))
    {
        delete dest;
        return ICUException(parseError, status).reportError();
    }

    u = new UnicodeString(dest, len);
    delete dest;

    return wrap_UnicodeString(u, T_OWNED);
}

static PyObject *t_unicodestring_idna_compare(t_unicodestring *self,
                                              PyObject *args)
{
    int options = UIDNA_DEFAULT;
    UnicodeString *u;
    UnicodeString _u;
    int n;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(n = uidna_compare(self->object->getBuffer(),
                                          self->object->length(),
                                          u->getBuffer(), u->length(), options,
                                          &status));
            return PyInt_FromLong(n);
        }
        break;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &options))
        {
            STATUS_CALL(n = uidna_compare(self->object->getBuffer(),
                                          self->object->length(),
                                          u->getBuffer(), u->length(), options,
                                          &status));
            return PyInt_FromLong(n);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "idna_compare", args);
}

#endif

static PyObject *t_unicodestring_richcmp(t_unicodestring *self,
                                         PyObject *arg, int op)
{
    UnicodeString *u;
    UnicodeString _u;
    int b = 0;

    if (isUnicodeString(arg))
        u = (UnicodeString *) ((t_uobject *) arg)->object;
    else
        try {
            PyObject_AsUnicodeString(arg, _u);
            u = &_u;
        } catch (ICUException e) {
            return e.reportError();
        }
        
    switch (op) {
      case Py_EQ:
        b = *self->object == *u;
        break;
      case Py_NE:
        b = *self->object != *u;
        break;
      case Py_LT:
        b = *self->object < *u;
        break;
      case Py_LE:
        b = *self->object <= *u;
        break;
      case Py_GT:
        b = *self->object > *u;
        break;
      case Py_GE:
        b = *self->object >= *u;
        break;
      default:
        PyErr_SetNone(PyExc_NotImplementedError);
        return NULL;
    }

    Py_RETURN_BOOL(b);
}

static Py_ssize_t t_unicodestring_length(t_unicodestring *self)
{
    return self->object->length();
}

static PyObject *t_unicodestring_concat(t_unicodestring *self, PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;
    int i;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UnicodeString *v = new UnicodeString(*self->object);
        *v += *u;
        return wrap_UnicodeString(v, T_OWNED);
    }

    if (!parseArg(arg, "i", &i))
    {
        UnicodeString *v = new UnicodeString(*self->object);

        if (sizeof(Py_UNICODE) == sizeof(UChar))
            v->append((UChar) i);
        else
            v->append((UChar32) i);

        return wrap_UnicodeString(v, T_OWNED);
    }

    return PyErr_SetArgsError((PyObject *) self, "+", arg);
}

static PyObject *t_unicodestring_repeat(t_unicodestring *self, Py_ssize_t n)
{
    if (n <= 0)
        return wrap_UnicodeString(new UnicodeString(), T_OWNED);
    else
    {
        UnicodeString *u = self->object;
        UnicodeString *v = new UnicodeString(u->length() * n, 0, 0);
    
        while (n-- > 0)
            *v += *u;

        return wrap_UnicodeString(v, T_OWNED);
    }
}

static PyObject *t_unicodestring_item(t_unicodestring *self, int n)
{
    UnicodeString *u = self->object;
    int len = u->length();

    if (n < 0)
        n += len;

    if (n >= 0 && n < len)
    {
        if (sizeof(Py_UNICODE) == sizeof(UChar))
        {
            Py_UNICODE c = (Py_UNICODE) u->charAt(n);
            return PyUnicode_FromUnicode(&c, 1);
        }
        else
        {
            Py_UNICODE c = (Py_UNICODE) u->char32At(n);
            return PyUnicode_FromUnicode(&c, 1);
        }
    }

    PyErr_SetNone(PyExc_IndexError);
    return NULL;
}

static PyObject *t_unicodestring_slice(t_unicodestring *self,
                                       Py_ssize_t l, Py_ssize_t h)
{
    UnicodeString *u = self->object;
    int len = u->length();

    if (l < 0)
        l += len;
    else if (l > len)
        l = len;

    if (h < 0)
        h += len;
    else if (h > len)
        h = len;

    UnicodeString *v = new UnicodeString();

    if (l >= 0 && h >= 0)
    {
        if (h > l)
            u->extract(l, h - l, *v);

        return wrap_UnicodeString(v, T_OWNED);
    }

    PyErr_SetNone(PyExc_IndexError);
    return NULL;
}

static int t_unicodestring_ass_item(t_unicodestring *self,
                                    Py_ssize_t n, PyObject *arg)
{
    UnicodeString *u = self->object;
    int len = u->length();

    if (n < 0)
        n += len;

    if (n >= 0 && n < len)
    {
        int32_t i;

        if (!parseArg(arg, "i", &i))
        {
            if (sizeof(Py_UNICODE) == sizeof(UChar))
                u->replace(n, 1, (UChar) i);
            else
                u->replace(n, 1, (UChar32) i);

            return 0;
        }

        UnicodeString *v;
        UnicodeString _v;

        if (!parseArg(arg, "S", &v, &_v))
        {
            if (v->length() == 1)
            {
                u->setCharAt(n, v->charAt(0));
                return 0;
            }
            else
            {
                PyErr_SetObject(PyExc_ValueError, arg);
                return -1;
            }
        }

        PyErr_SetObject(PyExc_TypeError, arg);
        return -1;
    }

    PyErr_SetNone(PyExc_IndexError);
    return -1;
}

static int t_unicodestring_ass_slice(t_unicodestring *self,
                                     Py_ssize_t l, Py_ssize_t h,
                                     PyObject *arg)
{
    UnicodeString *v;
    UnicodeString _v;

    if (!parseArg(arg, "S", &v, &_v))
    {
        UnicodeString *u = self->object;
        int len = u->length();

        if (l < 0)
            l += len;
        else if (l > len)
            l = len;

        if (h < 0)
            h += len;
        else if (h > len)
            h = len;

        if (h < l)
            h = l;

        if (h >= 0 && l >= 0)
        {
            u->replaceBetween(l, h, *v);
            return 0;
        }

        PyErr_SetNone(PyExc_IndexError);
        return -1;
    }

    PyErr_SetObject(PyExc_TypeError, arg);
    return -1;
}

static int t_unicodestring_contains(t_unicodestring *self, PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
        return self->object->indexOf(*u) == 0;

    PyErr_SetObject(PyExc_TypeError, arg);
    return -1;
}

static PyObject *t_unicodestring_inplace_concat(t_unicodestring *self,
                                                PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;
    int i;

    if (!parseArg(arg, "S", &u, &_u))
    {
        *self->object += *u;

        Py_INCREF(self);
        return (PyObject *) self;
    }

    if (!parseArg(arg, "i", &i))
    {
        if (sizeof(Py_UNICODE) == sizeof(UChar))
            self->object->append((UChar) i);
        else
            self->object->append((UChar32) i);

        Py_INCREF(self);
        return (PyObject *) self;
    }

    return PyErr_SetArgsError((PyObject *) self, "+=", arg);
}

static PyObject *t_unicodestring_inplace_repeat(t_unicodestring *self,
                                                Py_ssize_t n)
{
    if (n <= 0)
        self->object->remove();
    else if (n > 1)
    {
        UnicodeString v = *self->object;
        while (n-- > 1)
            *self->object += v;
    }

    Py_INCREF(self);
    return (PyObject *) self;
}

static PySequenceMethods t_unicodestring_as_sequence = {
    (lenfunc) t_unicodestring_length,                   /* sq_length */
    (binaryfunc) t_unicodestring_concat,                /* sq_concat */
    (ssizeargfunc) t_unicodestring_repeat,              /* sq_repeat */
    (ssizeargfunc) t_unicodestring_item,                /* sq_item */
#if PY_MAJOR_VERSION >= 3
    NULL,
    (ssizeobjargproc) t_unicodestring_ass_item,         /* sq_ass_item */
    NULL,
#else
    (ssizessizeargfunc) t_unicodestring_slice,          /* sq_slice */
    (ssizeobjargproc) t_unicodestring_ass_item,         /* sq_ass_item */
    (ssizessizeobjargproc) t_unicodestring_ass_slice,   /* sq_ass_slice */
#endif
    (objobjproc) t_unicodestring_contains,              /* sq_contains */
    (binaryfunc) t_unicodestring_inplace_concat,        /* sq_inplace_concat */
    (ssizeargfunc) t_unicodestring_inplace_repeat,      /* sq_inplace_repeat */
};

#if PY_MAJOR_VERSION >= 3
// Inspired by
// http://renesd.blogspot.com/2009/07/python3-c-api-simple-slicing-sqslice.html

static PyObject *t_unicodestring_subscript(t_unicodestring *self,
                                           PyObject *key)
{
    if (PyIndex_Check(key)) {
        Py_ssize_t i = PyNumber_AsSsize_t(key, PyExc_IndexError);
        if (i == -1 && PyErr_Occurred())
            return NULL;
        return t_unicodestring_item(self, i);
    }
    if (PySlice_Check(key)) {
        Py_ssize_t length, start, stop, step, slicelength;
        length = t_unicodestring_length(self);
        if (PySlice_GetIndicesEx(key, length,
                                 &start, &stop, &step, &slicelength))
            return NULL;
        if (step != 1) {
            PyErr_SetString(PyExc_TypeError, "slice steps not supported");
            return NULL;
        }
        return t_unicodestring_slice(self, start, stop);
    }
    PyErr_SetObject(PyExc_TypeError, key);
    return NULL;
}

static int t_unicodestring_ass_subscript(t_unicodestring *self,
                                         PyObject *key, PyObject *arg)
{
    if (PyIndex_Check(key)) {
        Py_ssize_t i = PyNumber_AsSsize_t(key, PyExc_IndexError);
        if (i == -1 && PyErr_Occurred())
            return -1;
        return t_unicodestring_ass_item(self, i, arg);
    }
    if (PySlice_Check(key)) {
        Py_ssize_t length, start, stop, step, slicelength;
        length = t_unicodestring_length(self);
        if (PySlice_GetIndicesEx(key, length,
                                 &start, &stop, &step, &slicelength))
            return -1;
        if (step != 1) {
            PyErr_SetString(PyExc_TypeError, "slice steps not supported");
            return -1;
        }
        return t_unicodestring_ass_slice(self, start, stop, arg);
    }
    PyErr_SetObject(PyExc_TypeError, key);
    return -1;
}

static PyMappingMethods t_unicodestring_as_mapping = {
    (lenfunc) t_unicodestring_length,                   /* mp_length */
    (binaryfunc) t_unicodestring_subscript,             /* mp_subscript */
    (objobjargproc) t_unicodestring_ass_subscript,      /* mp_ass_subscript */
};

#endif

/* Formattable */

static int t_formattable_init(t_formattable *self,
                              PyObject *args, PyObject *kwds)
{
    UDate date;
    Formattable::ISDATE flag;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new Formattable();
        self->flags = T_OWNED;
        break;
      case 1:
        self->object = toFormattable(PyTuple_GET_ITEM(args, 0));
        if (self->object)
        {
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "Di", &date, &flag))
        {
            self->object = new Formattable(date, flag);
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

static PyObject *t_formattable_getType(t_formattable *self)
{
    return PyInt_FromLong(self->object->getType());
}

static PyObject *t_formattable_isNumeric(t_formattable *self)
{
    int b = self->object->isNumeric();
    Py_RETURN_BOOL(b);
}

static PyObject *t_formattable_getDouble(t_formattable *self)
{
    UErrorCode status = U_ZERO_ERROR;
    double d = self->object->getDouble(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return PyFloat_FromDouble(d);
}

static PyObject *t_formattable_getLong(t_formattable *self)
{
    UErrorCode status = U_ZERO_ERROR;
    int n = self->object->getLong(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return PyInt_FromLong(n);
}

static PyObject *t_formattable_getInt64(t_formattable *self)
{
    UErrorCode status = U_ZERO_ERROR;
    PY_LONG_LONG l = self->object->getInt64(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return PyLong_FromLongLong(l);
}

static PyObject *t_formattable_getDate(t_formattable *self)
{
    UErrorCode status = U_ZERO_ERROR;
    double date = self->object->getDate(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return PyFloat_FromDouble(date / 1000.0);
}

static PyObject *t_formattable_getString(t_formattable *self, PyObject *args)
{
    UErrorCode status = U_ZERO_ERROR;

    switch (PyTuple_Size(args)) {
      case 0:
      {
          UnicodeString u;

          self->object->getString(u, status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();

          return PyUnicode_FromUnicodeString(&u);
      }
      case 1:
      {
          PyObject *arg = PyTuple_GET_ITEM(args, 0);
          UnicodeString *u;

          if (!parseArg(arg, "U", &u))
          {
              self->object->getString(*u, status);
              if (U_FAILURE(status))
                  return ICUException(status).reportError();

              Py_INCREF(arg);
              return arg;
          }
          break;
      }
    }

    return PyErr_SetArgsError((PyObject *) self, "getString", args);
}

static PyObject *t_formattable_setDouble(t_formattable *self, PyObject *arg)
{
    double d;
    
    if (!parseArg(arg, "d", &d))
    {
        self->object->setDouble(d);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDouble", arg);
}

static PyObject *t_formattable_setLong(t_formattable *self, PyObject *arg)
{
    int n;
    
    if (!parseArg(arg, "i", &n))
    {
        self->object->setLong(n);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLong", arg);
}

static PyObject *t_formattable_setInt64(t_formattable *self, PyObject *arg)
{
    PY_LONG_LONG l;
    
    if (!parseArg(arg, "L", &l))
    {
        self->object->setInt64(l);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setInt64", arg);
}

static PyObject *t_formattable_setDate(t_formattable *self, PyObject *arg)
{
    double date;
    
    if (!parseArg(arg, "D", &date))
    {
        self->object->setDate(date);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDate", arg);
}

static PyObject *t_formattable_setString(t_formattable *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->setString(*u); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setString", arg);
}

static PyObject *t_formattable_richcmp(t_formattable *self,
                                       PyObject *arg, int op)
{
    Formattable *f;

    if (!parseArg(arg, "P", TYPE_CLASSID(Formattable), &f))
    {
        int b = 0;

        switch (op) {
          case Py_EQ:
            b = *self->object == *f;
            break;
          case Py_NE:
            b = *self->object != *f;
            break;
          default:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }

        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}

static PyObject *t_formattable_str(t_formattable *self)
{
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString u;

    switch (self->object->getType()) {
      case Formattable::kDate:
      {
          SimpleDateFormat f = SimpleDateFormat(status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();

          f.format(*self->object, u, status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();
          break;
      }
      case Formattable::kDouble:
      case Formattable::kLong:
      case Formattable::kInt64:
      {
          DecimalFormat f = DecimalFormat(status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();

          f.format(*self->object, u, status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();
          break;
      }
      case Formattable::kString:
      {
          self->object->getString(u, status);
          if (U_FAILURE(status))
              return ICUException(status).reportError();
          break;
      }
      default:
        return t_uobject_str((t_uobject *) self);
    }

    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_formattable_repr(t_formattable *self)
{
    PyObject *name = PyObject_GetAttrString((PyObject *) Py_TYPE(self),
                                            "__name__");
    PyObject *str = Py_TYPE(self)->tp_str((PyObject *) self);

    if (str)
    {
        PyObject *repr = str->ob_type->tp_repr(str);
        Py_DECREF(str);
        str = repr;
    }
    if (!str)
        return NULL;
    
#if PY_VERSION_HEX < 0x02040000
    PyObject *args = Py_BuildValue("(OO)", name, str);
#else
    PyObject *args = PyTuple_Pack(2, name, str);
#endif
    PyObject *format = PyString_FromString("<%s: %s>");
    PyObject *repr = PyString_Format(format, args);

    Py_DECREF(name);
    Py_DECREF(str);
    Py_DECREF(args);
    Py_DECREF(format);

    return repr;
}


/* MeasureUnit */

static PyObject *t_measureunit_richcmp(t_measureunit *self,
                                       PyObject *arg, int op)
{
    int b = 0;

    switch (op) {
      case Py_EQ:
      case Py_NE:
        if (PyObject_TypeCheck(arg, &UObjectType_))
            b = *self->object == *((t_uobject *) arg)->object;
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

    return NULL;
}


/* Measure */

static PyObject *t_measure_getNumber(t_measure *self)
{
    Formattable *f = new Formattable(self->object->getNumber());
    return wrap_Formattable(f, T_OWNED);
}

static PyObject *t_measure_getUnit(t_measure *self)
{
    MeasureUnit *u = (MeasureUnit *) self->object->getUnit().clone();
    return wrap_MeasureUnit(u, T_OWNED);
}

static PyObject *t_measure_richcmp(t_measure *self, PyObject *arg, int op)
{
    int b = 0;

    switch (op) {
      case Py_EQ:
      case Py_NE:
        if (PyObject_TypeCheck(arg, &UObjectType_))
            b = *self->object == *((t_uobject *) arg)->object;
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

    return NULL;
}


/* CurrencyUnit */

static int t_currencyunit_init(t_currencyunit *self,
                               PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        CurrencyUnit *cu = new CurrencyUnit(u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = cu;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyunit_getISOCurrency(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyunit_str(t_currencyunit *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}


/* CurrencyAmount */

static int t_currencyamount_init(t_currencyamount *self,
                                 PyObject *args, PyObject *kwds)
{
    UErrorCode status = U_ZERO_ERROR;
    Formattable *f;
    double d;
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "PS", TYPE_CLASSID(Formattable),
                   &f, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(*f, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    if (!parseArgs(args, "dS", &d, &u, &_u))
    {
        CurrencyAmount *ca =
            new CurrencyAmount(d, u->getTerminatedBuffer(), status);

        if (U_FAILURE(status))
        {
            ICUException(status).reportError();
            return -1;
        }

        self->object = ca;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_currencyamount_getCurrency(t_currencyamount *self)
{
    CurrencyUnit *cu = new CurrencyUnit(self->object->getCurrency());
    return wrap_CurrencyUnit(cu, T_OWNED);
}

static PyObject *t_currencyamount_getISOCurrency(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_currencyamount_str(t_currencyamount *self)
{
    UnicodeString u(self->object->getISOCurrency());
    UErrorCode status = U_ZERO_ERROR;
    double d = self->object->getNumber().getDouble(status);

    PyObject *currency = PyUnicode_FromUnicodeString(&u);
    PyObject *amount = PyFloat_FromDouble(d);
    PyObject *format = PyString_FromString("%s %0.2f");
    PyObject *tuple = PyTuple_New(2);
    PyObject *str;

    PyTuple_SET_ITEM(tuple, 0, currency);
    PyTuple_SET_ITEM(tuple, 1, amount);
    str = PyString_Format(format, tuple);
    Py_DECREF(tuple);
    Py_DECREF(format);

    return str;
}


/* StringEnumeration */

static PyObject *t_stringenumeration_count(t_stringenumeration *self)
{
    UErrorCode status = U_ZERO_ERROR;
    int i = self->object->count(status);
  
    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return PyInt_FromLong(i);
}

static PyObject *t_stringenumeration_reset(t_stringenumeration *self)
{
    UErrorCode status = U_ZERO_ERROR;
  
    self->object->reset(status);
    if (U_FAILURE(status))
        return ICUException(status).reportError();

    Py_RETURN_NONE;
}

static PyObject *t_stringenumeration_next(t_stringenumeration *self)
{
    int32_t len;
    UErrorCode status = U_ZERO_ERROR;
    const char *str = self->object->next(&len, status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    if (str == NULL)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyString_FromStringAndSize(str, len);
}

static PyObject *t_stringenumeration_unext(t_stringenumeration *self)
{
    int32_t len;
    UErrorCode status = U_ZERO_ERROR;
    const UChar *str = self->object->unext(&len, status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    if (str == NULL)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    UnicodeString u(str);
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_stringenumeration_snext(t_stringenumeration *self)
{
    UErrorCode status = U_ZERO_ERROR;
    const UnicodeString *str = self->object->snext(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    if (str == NULL)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return wrap_UnicodeString(new UnicodeString(*str), T_OWNED);
}                

static PyObject *t_stringenumeration_iter(t_stringenumeration *self)
{
    Py_INCREF(self);
    return (PyObject *) self;
}


void _init_bases(PyObject *m)
{
    UnicodeStringType_.tp_str = (reprfunc) t_unicodestring_str;
    UnicodeStringType_.tp_repr = (reprfunc) t_unicodestring_repr;
    UnicodeStringType_.tp_richcompare = (richcmpfunc) t_unicodestring_richcmp;
    UnicodeStringType_.tp_hash = (hashfunc) t_unicodestring_hash;
    UnicodeStringType_.tp_as_sequence = &t_unicodestring_as_sequence;
#if PY_MAJOR_VERSION >= 3
    UnicodeStringType_.tp_as_mapping = &t_unicodestring_as_mapping;
#endif
    FormattableType_.tp_richcompare = (richcmpfunc) t_formattable_richcmp;
    FormattableType_.tp_str = (reprfunc) t_formattable_str;
    FormattableType_.tp_repr = (reprfunc) t_formattable_repr;
    MeasureUnitType_.tp_richcompare = (richcmpfunc) t_measureunit_richcmp;
    MeasureType_.tp_richcompare = (richcmpfunc) t_measure_richcmp;
    CurrencyUnitType_.tp_str = (reprfunc) t_currencyunit_str;
    CurrencyAmountType_.tp_str = (reprfunc) t_currencyamount_str;
    StringEnumerationType_.tp_iter = (getiterfunc) t_stringenumeration_iter;
    StringEnumerationType_.tp_iternext = (iternextfunc) t_stringenumeration_next;

    INSTALL_TYPE(UObject, m);
    INSTALL_TYPE(Replaceable, m);
    REGISTER_TYPE(UnicodeString, m);
    REGISTER_TYPE(Formattable, m);
    INSTALL_TYPE(MeasureUnit, m);
    INSTALL_TYPE(Measure, m);
    REGISTER_TYPE(CurrencyUnit, m);
    REGISTER_TYPE(CurrencyAmount, m);
    INSTALL_TYPE(StringEnumeration, m);

    INSTALL_MODULE_INT(m, U_FOLD_CASE_DEFAULT);
    INSTALL_MODULE_INT(m, U_COMPARE_CODE_POINT_ORDER);
    INSTALL_MODULE_INT(m, U_FOLD_CASE_EXCLUDE_SPECIAL_I);

#if U_ICU_VERSION_HEX < VERSION_HEX(55, 1, 0)
    INSTALL_MODULE_INT(m, UIDNA_DEFAULT);
    INSTALL_MODULE_INT(m, UIDNA_ALLOW_UNASSIGNED);
    INSTALL_MODULE_INT(m, UIDNA_USE_STD3_RULES);
#endif

    INSTALL_STATIC_INT(Formattable, kIsDate);
    INSTALL_STATIC_INT(Formattable, kDate);
    INSTALL_STATIC_INT(Formattable, kDouble);
    INSTALL_STATIC_INT(Formattable, kLong);
    INSTALL_STATIC_INT(Formattable, kString);
    INSTALL_STATIC_INT(Formattable, kArray);
    INSTALL_STATIC_INT(Formattable, kInt64);
    INSTALL_STATIC_INT(Formattable, kObject);
}
