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

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "char.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UProperty);
DECLARE_CONSTANTS_TYPE(UCharDirection);
DECLARE_CONSTANTS_TYPE(UCharCategory);
DECLARE_CONSTANTS_TYPE(UBlockCode);
DECLARE_CONSTANTS_TYPE(UCharNameChoice);
DECLARE_CONSTANTS_TYPE(UPropertyNameChoice);

/* Char */

struct UNone;
typedef struct UNone UNone;

class t_char : public _wrapper {
public:
    UNone *object;
};

typedef UBool (*bool_char_fn)(UChar32 c);
typedef UChar32 (*uchar32_char_fn)(UChar32 c);

static int t_char_init(t_char *self, PyObject *args, PyObject *kwds);
static PyObject *t_char_hasBinaryProperty(PyTypeObject *type, PyObject *args);
static PyObject *t_char_getIntPropertyValue(PyTypeObject *type, PyObject *args);
static PyObject *t_char_getIntPropertyMinValue(PyTypeObject *type,
                                               PyObject *arg);
static PyObject *t_char_getIntPropertyMaxValue(PyTypeObject *type,
                                               PyObject *arg);
static PyObject *t_char_getNumericValue(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isUAlphabetic(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isULowercase(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isUUppercase(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isUWhiteSpace(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_islower(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isupper(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_istitle(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isdigit(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isalpha(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isalnum(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isxdigit(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_ispunct(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isgraph(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isblank(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isdefined(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isspace(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isJavaSpaceChar(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isWhitespace(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_iscntrl(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isISOControl(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isprint(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isbase(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_charDirection(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isMirrored(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_charMirror(PyTypeObject *type, PyObject *arg);
#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
static PyObject *t_char_getBidiPairedBracket(PyTypeObject *type, PyObject *arg);
#endif
static PyObject *t_char_charType(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_enumCharTypes(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_getCombiningClass(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_charDigitValue(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_ublock_getCode(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_charName(PyTypeObject *type, PyObject *args);
static PyObject *t_char_charFromName(PyTypeObject *type, PyObject *args);
static PyObject *t_char_enumCharNames(PyTypeObject *type, PyObject *args);
static PyObject *t_char_getPropertyName(PyTypeObject *type, PyObject *args);
static PyObject *t_char_getPropertyEnum(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isIDStart(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isIDIgnorable(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isJavaIDStart(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_isJavaIDPart(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_tolower(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_toupper(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_totitle(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_foldCase(PyTypeObject *type, PyObject *args);
static PyObject *t_char_digit(PyTypeObject *type, PyObject *args);
static PyObject *t_char_forDigit(PyTypeObject *type, PyObject *args);
static PyObject *t_char_charAge(PyTypeObject *type, PyObject *arg);
static PyObject *t_char_getUnicodeVersion(PyTypeObject *type);
static PyObject *t_char_getFC_NFKC_Closure(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_char_methods[] = {
    DECLARE_METHOD(t_char, hasBinaryProperty, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, getIntPropertyValue, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, getIntPropertyMinValue, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, getIntPropertyMaxValue, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, getNumericValue, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isUAlphabetic, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isULowercase, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isUUppercase, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isUWhiteSpace, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, islower, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isupper, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, istitle, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isdigit, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isalpha, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isalnum, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isxdigit, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, ispunct, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isgraph, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isblank, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isdefined, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isspace, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isJavaSpaceChar, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isWhitespace, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, iscntrl, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isISOControl, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isprint, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isbase, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, charDirection, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isMirrored, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, charMirror, METH_O | METH_CLASS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
    DECLARE_METHOD(t_char, getBidiPairedBracket, METH_O | METH_CLASS),
#endif
    DECLARE_METHOD(t_char, charType, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, enumCharTypes, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, getCombiningClass, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, charDigitValue, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, ublock_getCode, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, charName, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, charFromName, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, enumCharNames, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, getPropertyName, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, getPropertyEnum, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isIDStart, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isIDIgnorable, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isJavaIDStart, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, isJavaIDPart, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, tolower, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, toupper, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, totitle, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, foldCase, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, digit, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, forDigit, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_char, charAge, METH_O | METH_CLASS),
    DECLARE_METHOD(t_char, getUnicodeVersion, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_char, getFC_NFKC_Closure, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_char_dealloc(t_char *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(Char, t_char, UNone, t_char_init, t_char_dealloc);

/* Char */

static int t_char_init(t_char *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = NULL;  /* there is no ICU struct for this */
        self->flags = T_OWNED;
        return 0;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
}

static PyObject *t_char_hasBinaryProperty(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UProperty prop;
    UChar32 c;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "ii", &c, &prop))
            Py_RETURN_BOOL(u_hasBinaryProperty(c, prop));
        if (!parseArgs(args, "Si", &u, &_u, &prop) && u->length() >= 1)
            Py_RETURN_BOOL(u_hasBinaryProperty(u->char32At(0), prop));
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "hasBinaryProperty", args);
}

static PyObject *t_char_getIntPropertyValue(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UProperty prop;
    UChar32 c;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "ii", &c, &prop))
            return PyInt_FromLong(u_getIntPropertyValue(c, prop));
        if (!parseArgs(args, "Si", &u, &_u, &prop) && u->length() >= 1)
            return PyInt_FromLong(u_getIntPropertyValue(u->char32At(0), prop));
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "getIntPropertyValue", args);
}

static PyObject *t_char_getIntPropertyMinValue(PyTypeObject *type,
                                               PyObject *arg)
{
    UProperty prop;

    if (!parseArg(arg, "i", &prop))
        return PyInt_FromLong(u_getIntPropertyMinValue(prop));

    return PyErr_SetArgsError((PyObject *) type, "getIntPropertyMinValue", arg);
}

static PyObject *t_char_getIntPropertyMaxValue(PyTypeObject *type,
                                               PyObject *arg)
{
    UProperty prop;

    if (!parseArg(arg, "i", &prop))
        return PyInt_FromLong(u_getIntPropertyMaxValue(prop));

    return PyErr_SetArgsError((PyObject *) type, "getIntPropertyMaxValue", arg);
}

static PyObject *t_char_getNumericValue(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;
    double value = U_NO_NUMERIC_VALUE;

    if (!parseArg(arg, "i", &c))
        value = u_getNumericValue(c);
    else if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        value = u_getNumericValue(u->char32At(0));
    else
        return PyErr_SetArgsError((PyObject *) type, "getNumericValue", arg);

    if (value == U_NO_NUMERIC_VALUE)
        Py_RETURN_NONE;

    return PyFloat_FromDouble(value);
}

static PyObject *t_char_fn(bool_char_fn fn, const char *name,
                           PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        Py_RETURN_BOOL((*fn)(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        Py_RETURN_BOOL((*fn)(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, name, arg);
}

static PyObject *t_char_isUAlphabetic(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isUAlphabetic, "isUAlphabetic", type, arg);
}

static PyObject *t_char_isULowercase(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isULowercase, "isULowercase", type, arg);
}

static PyObject *t_char_isUUppercase(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isUUppercase, "isUUpperCase", type, arg);
}

static PyObject *t_char_isUWhiteSpace(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isUWhiteSpace, "isUWhiteSpace", type, arg);
}

static PyObject *t_char_islower(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_islower, "islower", type, arg);
}

static PyObject *t_char_isupper(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isupper, "isupper", type, arg);
}

static PyObject *t_char_istitle(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_istitle, "istitle", type, arg);
}

static PyObject *t_char_isdigit(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isdigit, "isdigit", type, arg);
}

static PyObject *t_char_isalpha(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isalpha, "isalpha", type, arg);
}

static PyObject *t_char_isalnum(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isalnum, "isalnum", type, arg);
}

static PyObject *t_char_isxdigit(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isxdigit, "isxdigit", type, arg);
}

static PyObject *t_char_ispunct(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_ispunct, "ispunct", type, arg);
}

static PyObject *t_char_isgraph(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isgraph, "isgraph", type, arg);
}

static PyObject *t_char_isblank(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isblank, "isblank", type, arg);
}

static PyObject *t_char_isdefined(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isdefined, "isdefined", type, arg);
}

static PyObject *t_char_isspace(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isspace, "isspace", type, arg);
}

static PyObject *t_char_isJavaSpaceChar(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isJavaSpaceChar, "isJavaSpaceChar", type, arg);
}

static PyObject *t_char_isWhitespace(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isWhitespace, "isWhitespace", type, arg);
}

static PyObject *t_char_iscntrl(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_iscntrl, "iscntrl", type, arg);
}

static PyObject *t_char_isISOControl(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isISOControl, "isISOControl", type, arg);
}

static PyObject *t_char_isprint(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isprint, "isprint", type, arg);
}

static PyObject *t_char_isbase(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isbase, "isbase", type, arg);
}

static PyObject *t_char_isMirrored(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isMirrored, "isMirrored", type, arg);
}

static PyObject *t_char_isIDStart(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isIDStart, "isIDStart", type, arg);
}

static PyObject *t_char_isIDIgnorable(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isIDIgnorable, "isIDIgnorable", type, arg);
}

static PyObject *t_char_isJavaIDStart(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isJavaIDStart, "isJavaIDStart", type, arg);
}

static PyObject *t_char_isJavaIDPart(PyTypeObject *type, PyObject *arg) {
    return t_char_fn(u_isJavaIDPart, "isJavaIDPart", type, arg);
}

static PyObject *t_char_charDirection(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        return PyInt_FromLong(u_charDirection(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong(u_charDirection(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, "charDirection", arg);
}

static PyObject *t_char_charType(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        return PyInt_FromLong((int) u_charType(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong((int) u_charType(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, "charType", arg);
}

static UBool t_char_enum_types_cb(
    const void *context, UChar32 start, UChar32 limit, UCharCategory type)
{
    PyObject *obj = PyObject_CallFunction(
        (PyObject *) context, (char *) "iii", start, limit, type);

    if (obj == NULL)
        return false;

    bool result = PyObject_IsTrue(obj);

    Py_DECREF(obj);

    return result;
}

static PyObject *t_char_enumCharTypes(PyTypeObject *type, PyObject *arg)
{
    if (PyCallable_Check(arg))
    {
        u_enumCharTypes(t_char_enum_types_cb, arg);
        if (PyErr_Occurred())
            return NULL;

        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) type, "enumCharTypes", arg);
}


static PyObject *t_char_getCombiningClass(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        return PyInt_FromLong((unsigned int) u_getCombiningClass(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong(
            (unsigned int) u_getCombiningClass(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, "getCombiningClass", arg);
}

static PyObject *t_char_charDigitValue(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        return PyInt_FromLong((int) u_charDigitValue(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong((int) u_charDigitValue(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, "charDigitValue", arg);
}

static PyObject *t_char_ublock_getCode(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        return PyInt_FromLong((int) ublock_getCode(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong((int) ublock_getCode(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) type, "ublock_getCode", arg);
}

static PyObject *t_char_charName(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UCharNameChoice choice = U_UNICODE_CHAR_NAME;
    char buffer[128];
    int32_t size;
    UChar32 c;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &c))
        {
            STATUS_CALL(size = u_charName(c, choice, buffer,
                                          sizeof(buffer), &status));
            return PyString_FromString(buffer);
        }
        if (!parseArgs(args, "S", &u, &_u) && u->length() >= 1)
        {
            STATUS_CALL(size = u_charName(u->char32At(0), choice,
                                          buffer, sizeof(buffer), &status));
            return PyString_FromStringAndSize(buffer, size);
        }
        break;
      case 2:
        if (!parseArgs(args, "ii", &c, &choice))
        {
            STATUS_CALL(size = u_charName(c, choice,
                                          buffer, sizeof(buffer), &status));
            return PyString_FromStringAndSize(buffer, size);
        }
        if (!parseArgs(args, "Si", &u, &_u, &choice) && u->length() >= 1)
        {
            STATUS_CALL(size = u_charName(u->char32At(0), choice,
                                          buffer, sizeof(buffer), &status));
            return PyString_FromStringAndSize(buffer, size);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "charName", args);
}

static PyObject *t_char_charFromName(PyTypeObject *type, PyObject *args)
{
    char *name;
    UCharNameChoice choice = U_UNICODE_CHAR_NAME;
    UChar32 c;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "c", &name))
        {
            STATUS_CALL(c = u_charFromName(choice, name, &status));
            return PyInt_FromLong(c);
        }
        break;
      case 2:
        if (!parseArgs(args, "ci", &name, &choice))
        {
            STATUS_CALL(c = u_charFromName(choice, name, &status));
            return PyInt_FromLong(c);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "charFromName", args);
}

static UBool t_char_enum_names_cb(
    void *context, UChar32 code, UCharNameChoice choice,
    const char *name, int32_t length)
{
    PyObject *obj = PyObject_CallFunction(
        (PyObject *) context, (char *) "is#i", code, name, (int) length,
        choice);

    if (obj == NULL)
        return false;

    bool result = PyObject_IsTrue(obj);

    Py_DECREF(obj);

    return result;
}

static PyObject *t_char_enumCharNames(PyTypeObject *type, PyObject *args)
{
    PyObject *callable;
    UCharNameChoice choice = U_UNICODE_CHAR_NAME;
    UnicodeString *u, _u, *v, _v;
    UChar32 start, limit;

    switch (PyTuple_Size(args)) {
      case 3:
        if (!parseArgs(args, "iiM", &start, &limit, &callable))
        {
            STATUS_CALL(u_enumCharNames(
                start, limit, t_char_enum_names_cb, callable, choice, &status));
            if (PyErr_Occurred())
                return NULL;
            Py_RETURN_NONE;
        }
        if (!parseArgs(args, "SSM", &u, &_u, &v, &_v, &callable) &&
            u->length() >= 1 && v->length() >= 1)
        {
            STATUS_CALL(u_enumCharNames(
                u->char32At(0), v->char32At(0),
                t_char_enum_names_cb, callable, choice, &status));
            if (PyErr_Occurred())
                return NULL;
            Py_RETURN_NONE;
        }
        break;
      case 4:
        if (!parseArgs(args, "iiMi", &start, &limit, &callable, &choice))
        {
            STATUS_CALL(u_enumCharNames(
                start, limit, t_char_enum_names_cb, callable, choice, &status));
            if (PyErr_Occurred())
                return NULL;
            Py_RETURN_NONE;
        }
        if (!parseArgs(args, "SSMi", &u, &_u, &v, &_v, &callable, &choice) &&
            u->length() >= 1 && v->length() >= 1)
        {
            STATUS_CALL(u_enumCharNames(
                u->char32At(0), v->char32At(0),
                t_char_enum_names_cb, callable, choice, &status));
            if (PyErr_Occurred())
                return NULL;
            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "enumCharNames", args);
}

static PyObject *t_char_getPropertyName(PyTypeObject *type, PyObject *args)
{
    UPropertyNameChoice choice = U_SHORT_PROPERTY_NAME;
    UProperty prop;
    const char *result;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &prop))
        {
            result = u_getPropertyName(prop, choice);
            if (result != NULL)
                return PyString_FromString(result);
            Py_RETURN_NONE;
        }
        break;
      case 2:
        if (!parseArgs(args, "ii", &prop, &choice))
        {
            result = u_getPropertyName(prop, choice);
            if (result != NULL)
                return PyString_FromString(result);
            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "getPropertyName", args);
}

static PyObject *t_char_getPropertyEnum(PyTypeObject *type, PyObject *arg)
{
    char *alias;

    if (!parseArg(arg, "c", &alias))
        return PyInt_FromLong(u_getPropertyEnum(alias));

    return PyErr_SetArgsError((PyObject *) type, "getPropertyEnum", arg);
}

static PyObject *t_char_fn(uchar32_char_fn fn, const char *name,
                           PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
      return PyInt_FromLong((*fn)(c));
    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
    {
        UnicodeString result;
        result += (*fn)(u->char32At(0));
        
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) type, name, arg);
}

static PyObject *t_char_charMirror(PyTypeObject *type, PyObject *arg)
{
    return t_char_fn(u_charMirror, "charMirror", type, arg);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
static PyObject *t_char_getBidiPairedBracket(PyTypeObject *type, PyObject *arg)
{
    return t_char_fn(u_getBidiPairedBracket, "getBidiPairedBracket", type, arg);
}
#endif

static PyObject *t_char_tolower(PyTypeObject *type, PyObject *arg)
{
    return t_char_fn(u_tolower, "tolower", type, arg);
}

static PyObject *t_char_toupper(PyTypeObject *type, PyObject *arg)
{
    return t_char_fn(u_toupper, "toupper", type, arg);
}

static PyObject *t_char_totitle(PyTypeObject *type, PyObject *arg)
{
    return t_char_fn(u_totitle, "totitle", type, arg);
}

static PyObject *t_char_foldCase(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UChar32 c;
    uint32_t options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &c))
            return PyInt_FromLong(u_foldCase(c, U_FOLD_CASE_DEFAULT));
        if (!parseArgs(args, "S", &u, &_u) && u->length() >= 1)
        {
            UnicodeString result;
            result += u_foldCase(u->char32At(0), U_FOLD_CASE_DEFAULT);
        
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
      case 2:
        if (!parseArgs(args, "ii", &c, &options))
            return PyInt_FromLong(u_foldCase(c, options));
        if (!parseArgs(args, "Si", &u, &_u, &options) && u->length() >= 1)
        {
            UnicodeString result;
            result += u_foldCase(u->char32At(0), options);
        
            return PyUnicode_FromUnicodeString(&result);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "foldCase", args);
}

static PyObject *t_char_digit(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UChar32 c;
    int radix;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &c))
            return PyInt_FromLong(u_digit(c, (int8_t) 10));
        if (!parseArgs(args, "S", &u, &_u) && u->length() >= 1)
            return PyInt_FromLong(u_digit(u->char32At(0), (int8_t) 10));
        break;
      case 2:
        if (!parseArgs(args, "ii", &c, &radix))
            return PyInt_FromLong(u_digit(c, (int8_t) radix));
        if (!parseArgs(args, "Si", &u, &_u, &radix) && u->length() >= 1)
            return PyInt_FromLong(u_digit(u->char32At(0), (int8_t) radix));
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "digit", args);
}

static PyObject *t_char_forDigit(PyTypeObject *type, PyObject *args)
{
    UChar32 c;
    int radix;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &c))
            return PyInt_FromLong(u_forDigit(c, (int8_t) 10));
        break;
      case 2:
        if (!parseArgs(args, "ii", &c, &radix))
            return PyInt_FromLong(u_forDigit(c, (int8_t) radix));
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "forDigit", args);
}

static PyObject *t_char_charAge(PyTypeObject *type, PyObject *arg)
{
    char buffer[U_MAX_VERSION_STRING_LENGTH + 1];
    UVersionInfo versionInfo;
    UnicodeString *u, _u;
    UChar32 c;

    if (!parseArg(arg, "i", &c))
        u_charAge(c, versionInfo);
    else if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        u_charAge(u->char32At(0), versionInfo);
    else
        return PyErr_SetArgsError((PyObject *) type, "charAge", arg);

    u_versionToString(versionInfo, buffer);

    return PyString_FromString(buffer);
}

static PyObject *t_char_getUnicodeVersion(PyTypeObject *type)
{
    UVersionInfo versionInfo;
    char buffer[U_MAX_VERSION_STRING_LENGTH + 1];

    u_getUnicodeVersion(versionInfo);
    u_versionToString(versionInfo, buffer);

    return PyString_FromString(buffer);
}

static PyObject *t_char_getFC_NFKC_Closure(PyTypeObject *type, PyObject *arg)
{
    UChar buffer[128];
    UnicodeString *u, _u;
    UChar32 c;
    int32_t size;

    if (!parseArg(arg, "i", &c))
    {
        STATUS_CALL(size = u_getFC_NFKC_Closure(c, buffer, 128, &status));
    }
    else if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
    {
        STATUS_CALL(size = u_getFC_NFKC_Closure(u->char32At(0),
                                                buffer, 128, &status));
    }
    else
        return PyErr_SetArgsError((PyObject *) type, "getFC_NFKC_Closure", arg);

    return PyUnicode_FromUnicodeString(buffer, size);
}

void _init_char(PyObject *m)
{
    INSTALL_CONSTANTS_TYPE(UProperty, m);
    INSTALL_CONSTANTS_TYPE(UCharDirection, m);
    INSTALL_CONSTANTS_TYPE(UCharCategory, m);
    INSTALL_CONSTANTS_TYPE(UBlockCode, m);
    INSTALL_CONSTANTS_TYPE(UCharNameChoice, m);
    INSTALL_CONSTANTS_TYPE(UPropertyNameChoice, m);
    INSTALL_STRUCT(Char, m);

    INSTALL_ENUM(Char, "FOLD_CASE_DEFAULT", U_FOLD_CASE_DEFAULT);
    INSTALL_ENUM(Char, "FOLD_CASE_EXCLUDE_SPECIAL_I", U_FOLD_CASE_EXCLUDE_SPECIAL_I);

    INSTALL_ENUM(UProperty, "ALPHABETIC", UCHAR_ALPHABETIC);
    INSTALL_ENUM(UProperty, "ASCII_HEX_DIGIT", UCHAR_ASCII_HEX_DIGIT);
    INSTALL_ENUM(UProperty, "BIDI_CONTROL", UCHAR_BIDI_CONTROL);
    INSTALL_ENUM(UProperty, "BIDI_MIRRORED", UCHAR_BIDI_MIRRORED);
    INSTALL_ENUM(UProperty, "DASH", UCHAR_DASH);
    INSTALL_ENUM(UProperty, "DEFAULT_IGNORABLE_CODE_POINT", UCHAR_DEFAULT_IGNORABLE_CODE_POINT);
    INSTALL_ENUM(UProperty, "DIACRITIC", UCHAR_DIACRITIC);
    INSTALL_ENUM(UProperty, "EXTENDER", UCHAR_EXTENDER);
    INSTALL_ENUM(UProperty, "FULL_COMPOSITION_EXCLUSION", UCHAR_FULL_COMPOSITION_EXCLUSION);
    INSTALL_ENUM(UProperty, "GRAPHEME_BASE", UCHAR_GRAPHEME_BASE);
    INSTALL_ENUM(UProperty, "GRAPHEME_EXTEND", UCHAR_GRAPHEME_EXTEND);
    INSTALL_ENUM(UProperty, "GRAPHEME_LINK", UCHAR_GRAPHEME_LINK);
    INSTALL_ENUM(UProperty, "HEX_DIGIT", UCHAR_HEX_DIGIT);
    INSTALL_ENUM(UProperty, "HYPHEN", UCHAR_HYPHEN);
    INSTALL_ENUM(UProperty, "ID_CONTINUE", UCHAR_ID_CONTINUE);
    INSTALL_ENUM(UProperty, "ID_START", UCHAR_ID_START);
    INSTALL_ENUM(UProperty, "IDEOGRAPHIC", UCHAR_IDEOGRAPHIC);
    INSTALL_ENUM(UProperty, "IDS_BINARY_OPERATOR", UCHAR_IDS_BINARY_OPERATOR);
    INSTALL_ENUM(UProperty, "IDS_TRINARY_OPERATOR", UCHAR_IDS_TRINARY_OPERATOR);
    INSTALL_ENUM(UProperty, "JOIN_CONTROL", UCHAR_JOIN_CONTROL);
    INSTALL_ENUM(UProperty, "LOGICAL_ORDER_EXCEPTION", UCHAR_LOGICAL_ORDER_EXCEPTION);
    INSTALL_ENUM(UProperty, "LOWERCASE", UCHAR_LOWERCASE);
    INSTALL_ENUM(UProperty, "MATH", UCHAR_MATH);
    INSTALL_ENUM(UProperty, "NONCHARACTER_CODE_POINT", UCHAR_NONCHARACTER_CODE_POINT);
    INSTALL_ENUM(UProperty, "QUOTATION_MARK", UCHAR_QUOTATION_MARK);
    INSTALL_ENUM(UProperty, "RADICAL", UCHAR_RADICAL);
    INSTALL_ENUM(UProperty, "SOFT_DOTTED", UCHAR_SOFT_DOTTED);
    INSTALL_ENUM(UProperty, "TERMINAL_PUNCTUATION", UCHAR_TERMINAL_PUNCTUATION);
    INSTALL_ENUM(UProperty, "UNIFIED_IDEOGRAPH", UCHAR_UNIFIED_IDEOGRAPH);
    INSTALL_ENUM(UProperty, "UPPERCASE", UCHAR_UPPERCASE);
    INSTALL_ENUM(UProperty, "WHITE_SPACE", UCHAR_WHITE_SPACE);
    INSTALL_ENUM(UProperty, "XID_CONTINUE", UCHAR_XID_CONTINUE);
    INSTALL_ENUM(UProperty, "XID_START", UCHAR_XID_START);
    INSTALL_ENUM(UProperty, "CASE_SENSITIVE", UCHAR_CASE_SENSITIVE);
    INSTALL_ENUM(UProperty, "S_TERM", UCHAR_S_TERM);
    INSTALL_ENUM(UProperty, "VARIATION_SELECTOR", UCHAR_VARIATION_SELECTOR);
    INSTALL_ENUM(UProperty, "NFD_INERT", UCHAR_NFD_INERT);
    INSTALL_ENUM(UProperty, "NFKD_INERT", UCHAR_NFKD_INERT);
    INSTALL_ENUM(UProperty, "NFC_INERT", UCHAR_NFC_INERT);
    INSTALL_ENUM(UProperty, "NFKC_INERT", UCHAR_NFKC_INERT);
    INSTALL_ENUM(UProperty, "SEGMENT_STARTER", UCHAR_SEGMENT_STARTER);
    INSTALL_ENUM(UProperty, "PATTERN_SYNTAX", UCHAR_PATTERN_SYNTAX);
    INSTALL_ENUM(UProperty, "PATTERN_WHITE_SPACE", UCHAR_PATTERN_WHITE_SPACE);
    INSTALL_ENUM(UProperty, "POSIX_ALNUM", UCHAR_POSIX_ALNUM);
    INSTALL_ENUM(UProperty, "POSIX_BLANK", UCHAR_POSIX_BLANK);
    INSTALL_ENUM(UProperty, "POSIX_GRAPH", UCHAR_POSIX_GRAPH);
    INSTALL_ENUM(UProperty, "POSIX_PRINT", UCHAR_POSIX_PRINT);
    INSTALL_ENUM(UProperty, "POSIX_XDIGIT", UCHAR_POSIX_XDIGIT);
#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(UProperty, "CASED", UCHAR_CASED);
    INSTALL_ENUM(UProperty, "CASE_IGNORABLE", UCHAR_CASE_IGNORABLE);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_LOWERCASED", UCHAR_CHANGES_WHEN_LOWERCASED);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_UPPERCASED", UCHAR_CHANGES_WHEN_UPPERCASED);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_TITLECASED", UCHAR_CHANGES_WHEN_TITLECASED);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_CASEFOLDED", UCHAR_CHANGES_WHEN_CASEFOLDED);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_CASEMAPPED", UCHAR_CHANGES_WHEN_CASEMAPPED);
    INSTALL_ENUM(UProperty, "CHANGES_WHEN_NFKC_CASEFOLDED", UCHAR_CHANGES_WHEN_NFKC_CASEFOLDED);
#endif
    INSTALL_ENUM(UProperty, "BINARY_LIMIT", UCHAR_BINARY_LIMIT);
    INSTALL_ENUM(UProperty, "BIDI_CLASS", UCHAR_BIDI_CLASS);
    INSTALL_ENUM(UProperty, "INT_START", UCHAR_INT_START);
    INSTALL_ENUM(UProperty, "BLOCK", UCHAR_BLOCK);
    INSTALL_ENUM(UProperty, "CANONICAL_COMBINING_CLASS", UCHAR_CANONICAL_COMBINING_CLASS);
    INSTALL_ENUM(UProperty, "DECOMPOSITION_TYPE", UCHAR_DECOMPOSITION_TYPE);
    INSTALL_ENUM(UProperty, "EAST_ASIAN_WIDTH", UCHAR_EAST_ASIAN_WIDTH);
    INSTALL_ENUM(UProperty, "GENERAL_CATEGORY", UCHAR_GENERAL_CATEGORY);
    INSTALL_ENUM(UProperty, "JOINING_GROUP", UCHAR_JOINING_GROUP);
    INSTALL_ENUM(UProperty, "JOINING_TYPE", UCHAR_JOINING_TYPE);
    INSTALL_ENUM(UProperty, "LINE_BREAK", UCHAR_LINE_BREAK);
    INSTALL_ENUM(UProperty, "NUMERIC_TYPE", UCHAR_NUMERIC_TYPE);
    INSTALL_ENUM(UProperty, "SCRIPT", UCHAR_SCRIPT);
    INSTALL_ENUM(UProperty, "HANGUL_SYLLABLE_TYPE", UCHAR_HANGUL_SYLLABLE_TYPE);
    INSTALL_ENUM(UProperty, "NFD_QUICK_CHECK", UCHAR_NFD_QUICK_CHECK);
    INSTALL_ENUM(UProperty, "NFKD_QUICK_CHECK", UCHAR_NFKD_QUICK_CHECK);
    INSTALL_ENUM(UProperty, "NFC_QUICK_CHECK", UCHAR_NFC_QUICK_CHECK);
    INSTALL_ENUM(UProperty, "NFKC_QUICK_CHECK", UCHAR_NFKC_QUICK_CHECK);
    INSTALL_ENUM(UProperty, "LEAD_CANONICAL_COMBINING_CLASS", UCHAR_LEAD_CANONICAL_COMBINING_CLASS);
    INSTALL_ENUM(UProperty, "TRAIL_CANONICAL_COMBINING_CLASS", UCHAR_TRAIL_CANONICAL_COMBINING_CLASS);
    INSTALL_ENUM(UProperty, "GRAPHEME_CLUSTER_BREAK", UCHAR_GRAPHEME_CLUSTER_BREAK);
    INSTALL_ENUM(UProperty, "SENTENCE_BREAK", UCHAR_SENTENCE_BREAK);
    INSTALL_ENUM(UProperty, "WORD_BREAK", UCHAR_WORD_BREAK);
#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
    INSTALL_ENUM(UProperty, "BIDI_PAIRED_BRACKET_TYPE", UCHAR_BIDI_PAIRED_BRACKET_TYPE);
#endif
    INSTALL_ENUM(UProperty, "INT_LIMIT", UCHAR_INT_LIMIT);
    INSTALL_ENUM(UProperty, "GENERAL_CATEGORY_MASK", UCHAR_GENERAL_CATEGORY_MASK);
    INSTALL_ENUM(UProperty, "MASK_START", UCHAR_MASK_START);
    INSTALL_ENUM(UProperty, "MASK_LIMIT", UCHAR_MASK_LIMIT);
    INSTALL_ENUM(UProperty, "NUMERIC_VALUE", UCHAR_NUMERIC_VALUE);
    INSTALL_ENUM(UProperty, "DOUBLE_START", UCHAR_DOUBLE_START);
    INSTALL_ENUM(UProperty, "DOUBLE_LIMIT", UCHAR_DOUBLE_LIMIT);
    INSTALL_ENUM(UProperty, "AGE", UCHAR_AGE);
    INSTALL_ENUM(UProperty, "STRING_START", UCHAR_STRING_START);
    INSTALL_ENUM(UProperty, "BIDI_MIRRORING_GLYPH", UCHAR_BIDI_MIRRORING_GLYPH);
    INSTALL_ENUM(UProperty, "CASE_FOLDING", UCHAR_CASE_FOLDING);
    INSTALL_ENUM(UProperty, "LOWERCASE_MAPPING", UCHAR_LOWERCASE_MAPPING);
    INSTALL_ENUM(UProperty, "NAME", UCHAR_NAME);
    INSTALL_ENUM(UProperty, "SIMPLE_CASE_FOLDING", UCHAR_SIMPLE_CASE_FOLDING);
    INSTALL_ENUM(UProperty, "SIMPLE_LOWERCASE_MAPPING", UCHAR_SIMPLE_LOWERCASE_MAPPING);
    INSTALL_ENUM(UProperty, "SIMPLE_TITLECASE_MAPPING", UCHAR_SIMPLE_TITLECASE_MAPPING);
    INSTALL_ENUM(UProperty, "SIMPLE_UPPERCASE_MAPPING", UCHAR_SIMPLE_UPPERCASE_MAPPING);
    INSTALL_ENUM(UProperty, "TITLECASE_MAPPING", UCHAR_TITLECASE_MAPPING);
    INSTALL_ENUM(UProperty, "UPPERCASE_MAPPING", UCHAR_UPPERCASE_MAPPING);
#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
    INSTALL_ENUM(UProperty, "BIDI_PAIRED_BRACKET", UCHAR_BIDI_PAIRED_BRACKET);
#endif
    INSTALL_ENUM(UProperty, "STRING_LIMIT", UCHAR_STRING_LIMIT);
#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(UProperty, "SCRIPT_EXTENSIONS", UCHAR_SCRIPT_EXTENSIONS);
    INSTALL_ENUM(UProperty, "OTHER_PROPERTY_START", UCHAR_OTHER_PROPERTY_START);
    INSTALL_ENUM(UProperty, "OTHER_PROPERTY_LIMIT", UCHAR_OTHER_PROPERTY_LIMIT);
#endif
    INSTALL_ENUM(UProperty, "INVALID_CODE ", UCHAR_INVALID_CODE );

    INSTALL_ENUM(UCharDirection, "LEFT_TO_RIGHT", U_LEFT_TO_RIGHT);
    INSTALL_ENUM(UCharDirection, "RIGHT_TO_LEFT", U_RIGHT_TO_LEFT);
    INSTALL_ENUM(UCharDirection, "EUROPEAN_NUMBER", U_EUROPEAN_NUMBER);
    INSTALL_ENUM(UCharDirection, "EUROPEAN_NUMBER_SEPARATOR", U_EUROPEAN_NUMBER_SEPARATOR);
    INSTALL_ENUM(UCharDirection, "EUROPEAN_NUMBER_TERMINATOR", U_EUROPEAN_NUMBER_TERMINATOR);
    INSTALL_ENUM(UCharDirection, "ARABIC_NUMBER", U_ARABIC_NUMBER);
    INSTALL_ENUM(UCharDirection, "COMMON_NUMBER_SEPARATOR", U_COMMON_NUMBER_SEPARATOR);
    INSTALL_ENUM(UCharDirection, "BLOCK_SEPARATOR", U_BLOCK_SEPARATOR);
    INSTALL_ENUM(UCharDirection, "SEGMENT_SEPARATOR", U_SEGMENT_SEPARATOR);
    INSTALL_ENUM(UCharDirection, "WHITE_SPACE_NEUTRAL", U_WHITE_SPACE_NEUTRAL);
    INSTALL_ENUM(UCharDirection, "OTHER_NEUTRAL", U_OTHER_NEUTRAL);
    INSTALL_ENUM(UCharDirection, "LEFT_TO_RIGHT_EMBEDDING", U_LEFT_TO_RIGHT_EMBEDDING);
    INSTALL_ENUM(UCharDirection, "LEFT_TO_RIGHT_OVERRIDE", U_LEFT_TO_RIGHT_OVERRIDE);
    INSTALL_ENUM(UCharDirection, "RIGHT_TO_LEFT_ARABIC", U_RIGHT_TO_LEFT_ARABIC);
    INSTALL_ENUM(UCharDirection, "RIGHT_TO_LEFT_EMBEDDING", U_RIGHT_TO_LEFT_EMBEDDING);
    INSTALL_ENUM(UCharDirection, "RIGHT_TO_LEFT_OVERRIDE", U_RIGHT_TO_LEFT_OVERRIDE);
    INSTALL_ENUM(UCharDirection, "POP_DIRECTIONAL_FORMAT", U_POP_DIRECTIONAL_FORMAT);
    INSTALL_ENUM(UCharDirection, "DIR_NON_SPACING_MARK", U_DIR_NON_SPACING_MARK);
    INSTALL_ENUM(UCharDirection, "BOUNDARY_NEUTRAL", U_BOUNDARY_NEUTRAL);
#if U_ICU_VERSION_HEX >= VERSION_HEX(52, 0, 0)
    INSTALL_ENUM(UCharDirection, "FIRST_STRONG_ISOLATE", U_FIRST_STRONG_ISOLATE);
    INSTALL_ENUM(UCharDirection, "LEFT_TO_RIGHT_ISOLATE", U_LEFT_TO_RIGHT_ISOLATE);
    INSTALL_ENUM(UCharDirection, "RIGHT_TO_LEFT_ISOLATE", U_RIGHT_TO_LEFT_ISOLATE);
    INSTALL_ENUM(UCharDirection, "POP_DIRECTIONAL_ISOLATE", U_POP_DIRECTIONAL_ISOLATE);
#endif

    INSTALL_ENUM(UCharCategory, "UNASSIGNED", U_UNASSIGNED);
    INSTALL_ENUM(UCharCategory, "GENERAL_OTHER_TYPES", U_GENERAL_OTHER_TYPES);
    INSTALL_ENUM(UCharCategory, "UPPERCASE_LETTER", U_UPPERCASE_LETTER);
    INSTALL_ENUM(UCharCategory, "LOWERCASE_LETTER", U_LOWERCASE_LETTER);
    INSTALL_ENUM(UCharCategory, "TITLECASE_LETTER", U_TITLECASE_LETTER);
    INSTALL_ENUM(UCharCategory, "MODIFIER_LETTER", U_MODIFIER_LETTER);
    INSTALL_ENUM(UCharCategory, "OTHER_LETTER", U_OTHER_LETTER);
    INSTALL_ENUM(UCharCategory, "NON_SPACING_MARK", U_NON_SPACING_MARK);
    INSTALL_ENUM(UCharCategory, "ENCLOSING_MARK", U_ENCLOSING_MARK);
    INSTALL_ENUM(UCharCategory, "COMBINING_SPACING_MARK", U_COMBINING_SPACING_MARK);
    INSTALL_ENUM(UCharCategory, "DECIMAL_DIGIT_NUMBER", U_DECIMAL_DIGIT_NUMBER);
    INSTALL_ENUM(UCharCategory, "LETTER_NUMBER", U_LETTER_NUMBER);
    INSTALL_ENUM(UCharCategory, "OTHER_NUMBER", U_OTHER_NUMBER);
    INSTALL_ENUM(UCharCategory, "SPACE_SEPARATOR", U_SPACE_SEPARATOR);
    INSTALL_ENUM(UCharCategory, "LINE_SEPARATOR", U_LINE_SEPARATOR);
    INSTALL_ENUM(UCharCategory, "PARAGRAPH_SEPARATOR", U_PARAGRAPH_SEPARATOR);
    INSTALL_ENUM(UCharCategory, "CONTROL_CHAR", U_CONTROL_CHAR);
    INSTALL_ENUM(UCharCategory, "FORMAT_CHAR", U_FORMAT_CHAR);
    INSTALL_ENUM(UCharCategory, "PRIVATE_USE_CHAR", U_PRIVATE_USE_CHAR);
    INSTALL_ENUM(UCharCategory, "SURROGATE", U_SURROGATE);
    INSTALL_ENUM(UCharCategory, "DASH_PUNCTUATION", U_DASH_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "START_PUNCTUATION", U_START_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "END_PUNCTUATION", U_END_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "CONNECTOR_PUNCTUATION", U_CONNECTOR_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "OTHER_PUNCTUATION", U_OTHER_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "MATH_SYMBOL", U_MATH_SYMBOL);
    INSTALL_ENUM(UCharCategory, "CURRENCY_SYMBOL", U_CURRENCY_SYMBOL);
    INSTALL_ENUM(UCharCategory, "MODIFIER_SYMBOL", U_MODIFIER_SYMBOL);
    INSTALL_ENUM(UCharCategory, "OTHER_SYMBOL", U_OTHER_SYMBOL);
    INSTALL_ENUM(UCharCategory, "INITIAL_PUNCTUATION", U_INITIAL_PUNCTUATION);
    INSTALL_ENUM(UCharCategory, "FINAL_PUNCTUATION", U_FINAL_PUNCTUATION);

    INSTALL_ENUM(UBlockCode, "NO_BLOCK", UBLOCK_NO_BLOCK);
    INSTALL_ENUM(UBlockCode, "BASIC_LATIN", UBLOCK_BASIC_LATIN);
    INSTALL_ENUM(UBlockCode, "LATIN_1_SUPPLEMENT,", UBLOCK_LATIN_1_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_A", UBLOCK_LATIN_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_B", UBLOCK_LATIN_EXTENDED_B);
    INSTALL_ENUM(UBlockCode, "IPA_EXTENSIONS", UBLOCK_IPA_EXTENSIONS);
    INSTALL_ENUM(UBlockCode, "SPACING_MODIFIER_LETTERS", UBLOCK_SPACING_MODIFIER_LETTERS);
    INSTALL_ENUM(UBlockCode, "COMBINING_DIACRITICAL_MARKS", UBLOCK_COMBINING_DIACRITICAL_MARKS);
    INSTALL_ENUM(UBlockCode, "GREEK", UBLOCK_GREEK);
    INSTALL_ENUM(UBlockCode, "CYRILLIC", UBLOCK_CYRILLIC);
    INSTALL_ENUM(UBlockCode, "ARMENIAN", UBLOCK_ARMENIAN);
    INSTALL_ENUM(UBlockCode, "HEBREW", UBLOCK_HEBREW);
    INSTALL_ENUM(UBlockCode, "ARABIC", UBLOCK_ARABIC);
    INSTALL_ENUM(UBlockCode, "SYRIAC", UBLOCK_SYRIAC);
    INSTALL_ENUM(UBlockCode, "THAANA", UBLOCK_THAANA);
    INSTALL_ENUM(UBlockCode, "DEVANAGARI", UBLOCK_DEVANAGARI);
    INSTALL_ENUM(UBlockCode, "BENGALI", UBLOCK_BENGALI);
    INSTALL_ENUM(UBlockCode, "GURMUKHI", UBLOCK_GURMUKHI);
    INSTALL_ENUM(UBlockCode, "GUJARATI", UBLOCK_GUJARATI);
    INSTALL_ENUM(UBlockCode, "ORIYA", UBLOCK_ORIYA);
    INSTALL_ENUM(UBlockCode, "TAMIL", UBLOCK_TAMIL);
    INSTALL_ENUM(UBlockCode, "TELUGU", UBLOCK_TELUGU);
    INSTALL_ENUM(UBlockCode, "KANNADA", UBLOCK_KANNADA);
    INSTALL_ENUM(UBlockCode, "MALAYALAM", UBLOCK_MALAYALAM);
    INSTALL_ENUM(UBlockCode, "SINHALA", UBLOCK_SINHALA);
    INSTALL_ENUM(UBlockCode, "THAI", UBLOCK_THAI);
    INSTALL_ENUM(UBlockCode, "LAO", UBLOCK_LAO);
    INSTALL_ENUM(UBlockCode, "TIBETAN", UBLOCK_TIBETAN);
    INSTALL_ENUM(UBlockCode, "MYANMAR", UBLOCK_MYANMAR);
    INSTALL_ENUM(UBlockCode, "GEORGIAN", UBLOCK_GEORGIAN);
    INSTALL_ENUM(UBlockCode, "HANGUL_JAMO", UBLOCK_HANGUL_JAMO);
    INSTALL_ENUM(UBlockCode, "ETHIOPIC", UBLOCK_ETHIOPIC);
    INSTALL_ENUM(UBlockCode, "CHEROKEE", UBLOCK_CHEROKEE);
    INSTALL_ENUM(UBlockCode, "UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS", UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS);
    INSTALL_ENUM(UBlockCode, "OGHAM", UBLOCK_OGHAM);
    INSTALL_ENUM(UBlockCode, "RUNIC", UBLOCK_RUNIC);
    INSTALL_ENUM(UBlockCode, "KHMER", UBLOCK_KHMER);
    INSTALL_ENUM(UBlockCode, "MONGOLIAN", UBLOCK_MONGOLIAN);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_ADDITIONAL", UBLOCK_LATIN_EXTENDED_ADDITIONAL);
    INSTALL_ENUM(UBlockCode, "GREEK_EXTENDED", UBLOCK_GREEK_EXTENDED);
    INSTALL_ENUM(UBlockCode, "GENERAL_PUNCTUATION", UBLOCK_GENERAL_PUNCTUATION);
    INSTALL_ENUM(UBlockCode, "SUPERSCRIPTS_AND_SUBSCRIPTS", UBLOCK_SUPERSCRIPTS_AND_SUBSCRIPTS);
    INSTALL_ENUM(UBlockCode, "CURRENCY_SYMBOLS", UBLOCK_CURRENCY_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "COMBINING_MARKS_FOR_SYMBOLS", UBLOCK_COMBINING_MARKS_FOR_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "LETTERLIKE_SYMBOLS", UBLOCK_LETTERLIKE_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "NUMBER_FORMS", UBLOCK_NUMBER_FORMS);
    INSTALL_ENUM(UBlockCode, "ARROWS", UBLOCK_ARROWS);
    INSTALL_ENUM(UBlockCode, "MATHEMATICAL_OPERATORS", UBLOCK_MATHEMATICAL_OPERATORS);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_TECHNICAL", UBLOCK_MISCELLANEOUS_TECHNICAL);
    INSTALL_ENUM(UBlockCode, "CONTROL_PICTURES", UBLOCK_CONTROL_PICTURES);
    INSTALL_ENUM(UBlockCode, "OPTICAL_CHARACTER_RECOGNITION", UBLOCK_OPTICAL_CHARACTER_RECOGNITION);
    INSTALL_ENUM(UBlockCode, "ENCLOSED_ALPHANUMERICS", UBLOCK_ENCLOSED_ALPHANUMERICS);
    INSTALL_ENUM(UBlockCode, "BOX_DRAWING", UBLOCK_BOX_DRAWING);
    INSTALL_ENUM(UBlockCode, "BLOCK_ELEMENTS", UBLOCK_BLOCK_ELEMENTS);
    INSTALL_ENUM(UBlockCode, "GEOMETRIC_SHAPES", UBLOCK_GEOMETRIC_SHAPES);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_SYMBOLS", UBLOCK_MISCELLANEOUS_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "DINGBATS", UBLOCK_DINGBATS);
    INSTALL_ENUM(UBlockCode, "BRAILLE_PATTERNS", UBLOCK_BRAILLE_PATTERNS);
    INSTALL_ENUM(UBlockCode, "CJK_RADICALS_SUPPLEMENT", UBLOCK_CJK_RADICALS_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "KANGXI_RADICALS", UBLOCK_KANGXI_RADICALS);
    INSTALL_ENUM(UBlockCode, "IDEOGRAPHIC_DESCRIPTION_CHARACTERS", UBLOCK_IDEOGRAPHIC_DESCRIPTION_CHARACTERS);
    INSTALL_ENUM(UBlockCode, "CJK_SYMBOLS_AND_PUNCTUATION", UBLOCK_CJK_SYMBOLS_AND_PUNCTUATION);
    INSTALL_ENUM(UBlockCode, "HIRAGANA", UBLOCK_HIRAGANA);
    INSTALL_ENUM(UBlockCode, "KATAKANA", UBLOCK_KATAKANA);
    INSTALL_ENUM(UBlockCode, "BOPOMOFO", UBLOCK_BOPOMOFO);
    INSTALL_ENUM(UBlockCode, "HANGUL_COMPATIBILITY_JAMO", UBLOCK_HANGUL_COMPATIBILITY_JAMO);
    INSTALL_ENUM(UBlockCode, "KANBUN", UBLOCK_KANBUN);
    INSTALL_ENUM(UBlockCode, "BOPOMOFO_EXTENDED", UBLOCK_BOPOMOFO_EXTENDED);
    INSTALL_ENUM(UBlockCode, "ENCLOSED_CJK_LETTERS_AND_MONTHS", UBLOCK_ENCLOSED_CJK_LETTERS_AND_MONTHS);
    INSTALL_ENUM(UBlockCode, "CJK_COMPATIBILITY", UBLOCK_CJK_COMPATIBILITY);
    INSTALL_ENUM(UBlockCode, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A", UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_A);
    INSTALL_ENUM(UBlockCode, "CJK_UNIFIED_IDEOGRAPHS", UBLOCK_CJK_UNIFIED_IDEOGRAPHS);
    INSTALL_ENUM(UBlockCode, "YI_SYLLABLES", UBLOCK_YI_SYLLABLES);
    INSTALL_ENUM(UBlockCode, "YI_RADICALS", UBLOCK_YI_RADICALS);
    INSTALL_ENUM(UBlockCode, "HANGUL_SYLLABLES", UBLOCK_HANGUL_SYLLABLES);
    INSTALL_ENUM(UBlockCode, "HIGH_SURROGATES", UBLOCK_HIGH_SURROGATES);
    INSTALL_ENUM(UBlockCode, "HIGH_PRIVATE_USE_SURROGATES", UBLOCK_HIGH_PRIVATE_USE_SURROGATES);
    INSTALL_ENUM(UBlockCode, "LOW_SURROGATES", UBLOCK_LOW_SURROGATES);
    INSTALL_ENUM(UBlockCode, "PRIVATE_USE_AREA", UBLOCK_PRIVATE_USE_AREA);
    INSTALL_ENUM(UBlockCode, "PRIVATE_USE", UBLOCK_PRIVATE_USE);
    INSTALL_ENUM(UBlockCode, "CJK_COMPATIBILITY_IDEOGRAPHS", UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS);
    INSTALL_ENUM(UBlockCode, "ALPHABETIC_PRESENTATION_FORMS", UBLOCK_ALPHABETIC_PRESENTATION_FORMS);
    INSTALL_ENUM(UBlockCode, "ARABIC_PRESENTATION_FORMS_A", UBLOCK_ARABIC_PRESENTATION_FORMS_A);
    INSTALL_ENUM(UBlockCode, "COMBINING_HALF_MARKS", UBLOCK_COMBINING_HALF_MARKS);
    INSTALL_ENUM(UBlockCode, "CJK_COMPATIBILITY_FORMS", UBLOCK_CJK_COMPATIBILITY_FORMS);
    INSTALL_ENUM(UBlockCode, "SMALL_FORM_VARIANTS", UBLOCK_SMALL_FORM_VARIANTS);
    INSTALL_ENUM(UBlockCode, "ARABIC_PRESENTATION_FORMS_B", UBLOCK_ARABIC_PRESENTATION_FORMS_B);
    INSTALL_ENUM(UBlockCode, "SPECIALS", UBLOCK_SPECIALS);
    INSTALL_ENUM(UBlockCode, "HALFWIDTH_AND_FULLWIDTH_FORMS", UBLOCK_HALFWIDTH_AND_FULLWIDTH_FORMS);
    INSTALL_ENUM(UBlockCode, "OLD_ITALIC", UBLOCK_OLD_ITALIC);
    INSTALL_ENUM(UBlockCode, "GOTHIC", UBLOCK_GOTHIC);
    INSTALL_ENUM(UBlockCode, "DESERET", UBLOCK_DESERET);
    INSTALL_ENUM(UBlockCode, "BYZANTINE_MUSICAL_SYMBOLS", UBLOCK_BYZANTINE_MUSICAL_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "MUSICAL_SYMBOLS", UBLOCK_MUSICAL_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "MATHEMATICAL_ALPHANUMERIC_SYMBOLS", UBLOCK_MATHEMATICAL_ALPHANUMERIC_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B", UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_B);
    INSTALL_ENUM(UBlockCode, "CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT", UBLOCK_CJK_COMPATIBILITY_IDEOGRAPHS_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "TAGS", UBLOCK_TAGS);
    INSTALL_ENUM(UBlockCode, "CYRILLIC_SUPPLEMENT", UBLOCK_CYRILLIC_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "CYRILLIC_SUPPLEMENTARY", UBLOCK_CYRILLIC_SUPPLEMENTARY);
    INSTALL_ENUM(UBlockCode, "TAGALOG", UBLOCK_TAGALOG);
    INSTALL_ENUM(UBlockCode, "HANUNOO", UBLOCK_HANUNOO);
    INSTALL_ENUM(UBlockCode, "BUHID", UBLOCK_BUHID);
    INSTALL_ENUM(UBlockCode, "TAGBANWA", UBLOCK_TAGBANWA);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A", UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_A);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTAL_ARROWS_A", UBLOCK_SUPPLEMENTAL_ARROWS_A);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTAL_ARROWS_B", UBLOCK_SUPPLEMENTAL_ARROWS_B);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B", UBLOCK_MISCELLANEOUS_MATHEMATICAL_SYMBOLS_B);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTAL_MATHEMATICAL_OPERATORS", UBLOCK_SUPPLEMENTAL_MATHEMATICAL_OPERATORS);
    INSTALL_ENUM(UBlockCode, "KATAKANA_PHONETIC_EXTENSIONS", UBLOCK_KATAKANA_PHONETIC_EXTENSIONS);
    INSTALL_ENUM(UBlockCode, "VARIATION_SELECTORS", UBLOCK_VARIATION_SELECTORS);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTARY_PRIVATE_USE_AREA_A", UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_A);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTARY_PRIVATE_USE_AREA_B", UBLOCK_SUPPLEMENTARY_PRIVATE_USE_AREA_B);
    INSTALL_ENUM(UBlockCode, "LIMBU", UBLOCK_LIMBU);
    INSTALL_ENUM(UBlockCode, "TAI_LE", UBLOCK_TAI_LE);
    INSTALL_ENUM(UBlockCode, "KHMER_SYMBOLS", UBLOCK_KHMER_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "PHONETIC_EXTENSIONS", UBLOCK_PHONETIC_EXTENSIONS);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_SYMBOLS_AND_ARROWS", UBLOCK_MISCELLANEOUS_SYMBOLS_AND_ARROWS);
    INSTALL_ENUM(UBlockCode, "YIJING_HEXAGRAM_SYMBOLS", UBLOCK_YIJING_HEXAGRAM_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "LINEAR_B_SYLLABARY", UBLOCK_LINEAR_B_SYLLABARY);
    INSTALL_ENUM(UBlockCode, "LINEAR_B_IDEOGRAMS", UBLOCK_LINEAR_B_IDEOGRAMS);
    INSTALL_ENUM(UBlockCode, "AEGEAN_NUMBERS", UBLOCK_AEGEAN_NUMBERS);
    INSTALL_ENUM(UBlockCode, "UGARITIC", UBLOCK_UGARITIC);
    INSTALL_ENUM(UBlockCode, "SHAVIAN", UBLOCK_SHAVIAN);
    INSTALL_ENUM(UBlockCode, "OSMANYA", UBLOCK_OSMANYA);
    INSTALL_ENUM(UBlockCode, "CYPRIOT_SYLLABARY", UBLOCK_CYPRIOT_SYLLABARY);
    INSTALL_ENUM(UBlockCode, "TAI_XUAN_JING_SYMBOLS", UBLOCK_TAI_XUAN_JING_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "VARIATION_SELECTORS_SUPPLEMENT", UBLOCK_VARIATION_SELECTORS_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "ANCIENT_GREEK_MUSICAL_NOTATION", UBLOCK_ANCIENT_GREEK_MUSICAL_NOTATION);
    INSTALL_ENUM(UBlockCode, "ANCIENT_GREEK_NUMBERS", UBLOCK_ANCIENT_GREEK_NUMBERS);
    INSTALL_ENUM(UBlockCode, "ARABIC_SUPPLEMENT", UBLOCK_ARABIC_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "BUGINESE", UBLOCK_BUGINESE);
    INSTALL_ENUM(UBlockCode, "CJK_STROKES", UBLOCK_CJK_STROKES);
    INSTALL_ENUM(UBlockCode, "COMBINING_DIACRITICAL_MARKS_SUPPLEMENT", UBLOCK_COMBINING_DIACRITICAL_MARKS_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "COPTIC", UBLOCK_COPTIC);
    INSTALL_ENUM(UBlockCode, "ETHIOPIC_EXTENDED", UBLOCK_ETHIOPIC_EXTENDED);
    INSTALL_ENUM(UBlockCode, "ETHIOPIC_SUPPLEMENT", UBLOCK_ETHIOPIC_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "GEORGIAN_SUPPLEMENT", UBLOCK_GEORGIAN_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "GLAGOLITIC", UBLOCK_GLAGOLITIC);
    INSTALL_ENUM(UBlockCode, "KHAROSHTHI", UBLOCK_KHAROSHTHI);
    INSTALL_ENUM(UBlockCode, "MODIFIER_TONE_LETTERS", UBLOCK_MODIFIER_TONE_LETTERS);
    INSTALL_ENUM(UBlockCode, "NEW_TAI_LUE", UBLOCK_NEW_TAI_LUE);
    INSTALL_ENUM(UBlockCode, "OLD_PERSIAN", UBLOCK_OLD_PERSIAN);
    INSTALL_ENUM(UBlockCode, "PHONETIC_EXTENSIONS_SUPPLEMENT", UBLOCK_PHONETIC_EXTENSIONS_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTAL_PUNCTUATION", UBLOCK_SUPPLEMENTAL_PUNCTUATION);
    INSTALL_ENUM(UBlockCode, "SYLOTI_NAGRI", UBLOCK_SYLOTI_NAGRI);
    INSTALL_ENUM(UBlockCode, "TIFINAGH", UBLOCK_TIFINAGH);
    INSTALL_ENUM(UBlockCode, "VERTICAL_FORMS", UBLOCK_VERTICAL_FORMS);
    INSTALL_ENUM(UBlockCode, "NKO", UBLOCK_NKO);
    INSTALL_ENUM(UBlockCode, "BALINESE", UBLOCK_BALINESE);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_C", UBLOCK_LATIN_EXTENDED_C);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_D", UBLOCK_LATIN_EXTENDED_D);
    INSTALL_ENUM(UBlockCode, "PHAGS_PA", UBLOCK_PHAGS_PA);
    INSTALL_ENUM(UBlockCode, "PHOENICIAN", UBLOCK_PHOENICIAN);
    INSTALL_ENUM(UBlockCode, "CUNEIFORM", UBLOCK_CUNEIFORM);
    INSTALL_ENUM(UBlockCode, "CUNEIFORM_NUMBERS_AND_PUNCTUATION", UBLOCK_CUNEIFORM_NUMBERS_AND_PUNCTUATION);
    INSTALL_ENUM(UBlockCode, "COUNTING_ROD_NUMERALS", UBLOCK_COUNTING_ROD_NUMERALS);
#if U_ICU_VERSION_HEX >= 0x04000000
    INSTALL_ENUM(UBlockCode, "SUNDANESE", UBLOCK_SUNDANESE);
    INSTALL_ENUM(UBlockCode, "LEPCHA", UBLOCK_LEPCHA);
    INSTALL_ENUM(UBlockCode, "OL_CHIKI", UBLOCK_OL_CHIKI);
    INSTALL_ENUM(UBlockCode, "CYRILLIC_EXTENDED_A", UBLOCK_CYRILLIC_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "VAI", UBLOCK_VAI);
    INSTALL_ENUM(UBlockCode, "CYRILLIC_EXTENDED_B", UBLOCK_CYRILLIC_EXTENDED_B);
    INSTALL_ENUM(UBlockCode, "SAURASHTRA", UBLOCK_SAURASHTRA);
    INSTALL_ENUM(UBlockCode, "KAYAH_LI", UBLOCK_KAYAH_LI);
    INSTALL_ENUM(UBlockCode, "REJANG", UBLOCK_REJANG);
    INSTALL_ENUM(UBlockCode, "CHAM", UBLOCK_CHAM);
    INSTALL_ENUM(UBlockCode, "ANCIENT_SYMBOLS", UBLOCK_ANCIENT_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "PHAISTOS_DISC", UBLOCK_PHAISTOS_DISC);
    INSTALL_ENUM(UBlockCode, "LYCIAN", UBLOCK_LYCIAN);
    INSTALL_ENUM(UBlockCode, "CARIAN", UBLOCK_CARIAN);
    INSTALL_ENUM(UBlockCode, "LYDIAN", UBLOCK_LYDIAN);
    INSTALL_ENUM(UBlockCode, "MAHJONG_TILES", UBLOCK_MAHJONG_TILES);
    INSTALL_ENUM(UBlockCode, "DOMINO_TILES", UBLOCK_DOMINO_TILES);
#endif
#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(UBlockCode, "SAMARITAN", UBLOCK_SAMARITAN);
    INSTALL_ENUM(UBlockCode, "UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED", UBLOCK_UNIFIED_CANADIAN_ABORIGINAL_SYLLABICS_EXTENDED);
    INSTALL_ENUM(UBlockCode, "TAI_THAM", UBLOCK_TAI_THAM);
    INSTALL_ENUM(UBlockCode, "VEDIC_EXTENSIONS", UBLOCK_VEDIC_EXTENSIONS);
    INSTALL_ENUM(UBlockCode, "LISU", UBLOCK_LISU);
    INSTALL_ENUM(UBlockCode, "BAMUM", UBLOCK_BAMUM);
    INSTALL_ENUM(UBlockCode, "COMMON_INDIC_NUMBER_FORMS", UBLOCK_COMMON_INDIC_NUMBER_FORMS);
    INSTALL_ENUM(UBlockCode, "DEVANAGARI_EXTENDED", UBLOCK_DEVANAGARI_EXTENDED);
    INSTALL_ENUM(UBlockCode, "HANGUL_JAMO_EXTENDED_A", UBLOCK_HANGUL_JAMO_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "JAVANESE", UBLOCK_JAVANESE);
    INSTALL_ENUM(UBlockCode, "MYANMAR_EXTENDED_A", UBLOCK_MYANMAR_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "TAI_VIET", UBLOCK_TAI_VIET);
    INSTALL_ENUM(UBlockCode, "MEETEI_MAYEK", UBLOCK_MEETEI_MAYEK);
    INSTALL_ENUM(UBlockCode, "HANGUL_JAMO_EXTENDED_B", UBLOCK_HANGUL_JAMO_EXTENDED_B);
    INSTALL_ENUM(UBlockCode, "IMPERIAL_ARAMAIC", UBLOCK_IMPERIAL_ARAMAIC);
    INSTALL_ENUM(UBlockCode, "OLD_SOUTH_ARABIAN", UBLOCK_OLD_SOUTH_ARABIAN);
    INSTALL_ENUM(UBlockCode, "AVESTAN", UBLOCK_AVESTAN);
    INSTALL_ENUM(UBlockCode, "INSCRIPTIONAL_PARTHIAN", UBLOCK_INSCRIPTIONAL_PARTHIAN);
    INSTALL_ENUM(UBlockCode, "INSCRIPTIONAL_PAHLAVI", UBLOCK_INSCRIPTIONAL_PAHLAVI);
    INSTALL_ENUM(UBlockCode, "OLD_TURKIC", UBLOCK_OLD_TURKIC);
    INSTALL_ENUM(UBlockCode, "RUMI_NUMERAL_SYMBOLS", UBLOCK_RUMI_NUMERAL_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "KAITHI", UBLOCK_KAITHI);
    INSTALL_ENUM(UBlockCode, "EGYPTIAN_HIEROGLYPHS", UBLOCK_EGYPTIAN_HIEROGLYPHS);
    INSTALL_ENUM(UBlockCode, "ENCLOSED_ALPHANUMERIC_SUPPLEMENT", UBLOCK_ENCLOSED_ALPHANUMERIC_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "ENCLOSED_IDEOGRAPHIC_SUPPLEMENT", UBLOCK_ENCLOSED_IDEOGRAPHIC_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C", UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_C);
#endif
#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(UBlockCode, "MANDAIC", UBLOCK_MANDAIC);
    INSTALL_ENUM(UBlockCode, "BATAK", UBLOCK_BATAK);
    INSTALL_ENUM(UBlockCode, "ETHIOPIC_EXTENDED_A", UBLOCK_ETHIOPIC_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "BRAHMI", UBLOCK_BRAHMI);
    INSTALL_ENUM(UBlockCode, "BAMUM_SUPPLEMENT", UBLOCK_BAMUM_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "KANA_SUPPLEMENT", UBLOCK_KANA_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "PLAYING_CARDS", UBLOCK_PLAYING_CARDS);
    INSTALL_ENUM(UBlockCode, "MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS", UBLOCK_MISCELLANEOUS_SYMBOLS_AND_PICTOGRAPHS);
    INSTALL_ENUM(UBlockCode, "EMOTICONS", UBLOCK_EMOTICONS);
    INSTALL_ENUM(UBlockCode, "TRANSPORT_AND_MAP_SYMBOLS", UBLOCK_TRANSPORT_AND_MAP_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "ALCHEMICAL_SYMBOLS", UBLOCK_ALCHEMICAL_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D", UBLOCK_CJK_UNIFIED_IDEOGRAPHS_EXTENSION_D);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
    INSTALL_ENUM(UBlockCode, "ARABIC_EXTENDED_A", UBLOCK_ARABIC_EXTENDED_A);
    INSTALL_ENUM(UBlockCode, "ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS", UBLOCK_ARABIC_MATHEMATICAL_ALPHABETIC_SYMBOLS);
    INSTALL_ENUM(UBlockCode, "CHAKMA", UBLOCK_CHAKMA);
    INSTALL_ENUM(UBlockCode, "MEETEI_MAYEK_EXTENSIONS", UBLOCK_MEETEI_MAYEK_EXTENSIONS);
    INSTALL_ENUM(UBlockCode, "MEROITIC_CURSIVE", UBLOCK_MEROITIC_CURSIVE);
    INSTALL_ENUM(UBlockCode, "MEROITIC_HIEROGLYPHS", UBLOCK_MEROITIC_HIEROGLYPHS);
    INSTALL_ENUM(UBlockCode, "MIAO", UBLOCK_MIAO);
    INSTALL_ENUM(UBlockCode, "SHARADA", UBLOCK_SHARADA);
    INSTALL_ENUM(UBlockCode, "SORA_SOMPENG", UBLOCK_SORA_SOMPENG);
    INSTALL_ENUM(UBlockCode, "SUNDANESE_SUPPLEMENT", UBLOCK_SUNDANESE_SUPPLEMENT);
    INSTALL_ENUM(UBlockCode, "TAKRI", UBLOCK_TAKRI);
#endif
#if U_ICU_VERSION_HEX >= VERSION_HEX(54, 0, 0)
    INSTALL_ENUM(UBlockCode, "BASSA_VAH", UBLOCK_BASSA_VAH);
    INSTALL_ENUM(UBlockCode, "CAUCASIAN_ALBANIAN", UBLOCK_CAUCASIAN_ALBANIAN);
    INSTALL_ENUM(UBlockCode, "COPTIC_EPACT_NUMBERS", UBLOCK_COPTIC_EPACT_NUMBERS);
    INSTALL_ENUM(UBlockCode, "COMBINING_DIACRITICAL_MARKS_EXTENDED", UBLOCK_COMBINING_DIACRITICAL_MARKS_EXTENDED);
    INSTALL_ENUM(UBlockCode, "DUPLOYAN", UBLOCK_DUPLOYAN);
    INSTALL_ENUM(UBlockCode, "ELBASAN", UBLOCK_ELBASAN);
    INSTALL_ENUM(UBlockCode, "GEOMETRIC_SHAPES_EXTENDED", UBLOCK_GEOMETRIC_SHAPES_EXTENDED);
    INSTALL_ENUM(UBlockCode, "GRANTHA", UBLOCK_GRANTHA);
    INSTALL_ENUM(UBlockCode, "KHOJKI", UBLOCK_KHOJKI);
    INSTALL_ENUM(UBlockCode, "KHUDAWADI", UBLOCK_KHUDAWADI);
    INSTALL_ENUM(UBlockCode, "LATIN_EXTENDED_E", UBLOCK_LATIN_EXTENDED_E);
    INSTALL_ENUM(UBlockCode, "LINEAR_A", UBLOCK_LINEAR_A);
    INSTALL_ENUM(UBlockCode, "MAHAJANI", UBLOCK_MAHAJANI);
    INSTALL_ENUM(UBlockCode, "MANICHAEAN", UBLOCK_MANICHAEAN);
    INSTALL_ENUM(UBlockCode, "MENDE_KIKAKUI", UBLOCK_MENDE_KIKAKUI);
    INSTALL_ENUM(UBlockCode, "MODI", UBLOCK_MODI);
    INSTALL_ENUM(UBlockCode, "MRO", UBLOCK_MRO);
    INSTALL_ENUM(UBlockCode, "MYANMAR_EXTENDED_B", UBLOCK_MYANMAR_EXTENDED_B);
    INSTALL_ENUM(UBlockCode, "NABATAEAN", UBLOCK_NABATAEAN);
    INSTALL_ENUM(UBlockCode, "OLD_NORTH_ARABIAN", UBLOCK_OLD_NORTH_ARABIAN);
    INSTALL_ENUM(UBlockCode, "OLD_PERMIC", UBLOCK_OLD_PERMIC);
    INSTALL_ENUM(UBlockCode, "ORNAMENTAL_DINGBATS", UBLOCK_ORNAMENTAL_DINGBATS);
    INSTALL_ENUM(UBlockCode, "PAHAWH_HMONG", UBLOCK_PAHAWH_HMONG);
    INSTALL_ENUM(UBlockCode, "PALMYRENE", UBLOCK_PALMYRENE);
    INSTALL_ENUM(UBlockCode, "PAU_CIN_HAU", UBLOCK_PAU_CIN_HAU);
    INSTALL_ENUM(UBlockCode, "PSALTER_PAHLAVI", UBLOCK_PSALTER_PAHLAVI);
    INSTALL_ENUM(UBlockCode, "SHORTHAND_FORMAT_CONTROLS", UBLOCK_SHORTHAND_FORMAT_CONTROLS);
    INSTALL_ENUM(UBlockCode, "SIDDHAM", UBLOCK_SIDDHAM);
    INSTALL_ENUM(UBlockCode, "SINHALA_ARCHAIC_NUMBERS", UBLOCK_SINHALA_ARCHAIC_NUMBERS);
    INSTALL_ENUM(UBlockCode, "SUPPLEMENTAL_ARROWS_C", UBLOCK_SUPPLEMENTAL_ARROWS_C);
    INSTALL_ENUM(UBlockCode, "TIRHUTA", UBLOCK_TIRHUTA);
    INSTALL_ENUM(UBlockCode, "WARANG_CITI", UBLOCK_WARANG_CITI);
#endif
    INSTALL_ENUM(UBlockCode, "INVALID_CODE", UBLOCK_INVALID_CODE);

    INSTALL_ENUM(UCharNameChoice, "UNICODE_CHAR_NAME", U_UNICODE_CHAR_NAME);
    INSTALL_ENUM(UCharNameChoice, "EXTENDED_CHAR_NAME", U_EXTENDED_CHAR_NAME);
#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(UCharNameChoice, "CHAR_NAME_ALIAS", U_CHAR_NAME_ALIAS);
#endif

    INSTALL_ENUM(UPropertyNameChoice, "SHORT_PROPERTY_NAME", U_SHORT_PROPERTY_NAME);
    INSTALL_ENUM(UPropertyNameChoice, "LONG_PROPERTY_NAME", U_LONG_PROPERTY_NAME);
}
