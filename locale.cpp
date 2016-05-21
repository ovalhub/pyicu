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

#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER) || defined(__WIN32)
#include <windows.h>
#else
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#endif

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "locale.h"
#include "macros.h"
#include "unicodeset.h"

DECLARE_CONSTANTS_TYPE(ULocDataLocaleType);
DECLARE_CONSTANTS_TYPE(UResType);
DECLARE_CONSTANTS_TYPE(ULocaleDataDelimiterType);
DECLARE_CONSTANTS_TYPE(ULocaleDataExemplarSetType);
DECLARE_CONSTANTS_TYPE(UMeasurementSystem);

/* Locale */

class t_locale : public _wrapper {
public:
    Locale *object;
};

static int t_locale_init(t_locale *self, PyObject *args, PyObject *kwds);
static PyObject *t_locale_getLanguage(t_locale *self);
static PyObject *t_locale_getScript(t_locale *self);
static PyObject *t_locale_getCountry(t_locale *self);
static PyObject *t_locale_getVariant(t_locale *self);
static PyObject *t_locale_getName(t_locale *self);
static PyObject *t_locale_getBaseName(t_locale *self);
static PyObject *t_locale_getISO3Language(t_locale *self);
static PyObject *t_locale_getISO3Country(t_locale *self);
static PyObject *t_locale_getLCID(t_locale *self);
static PyObject *t_locale_getDisplayLanguage(t_locale *self, PyObject *args);
static PyObject *t_locale_getDisplayScript(t_locale *self, PyObject *args);
static PyObject *t_locale_getDisplayCountry(t_locale *self, PyObject *args);
static PyObject *t_locale_getDisplayVariant(t_locale *self, PyObject *args);
static PyObject *t_locale_getDisplayName(t_locale *self, PyObject *args);
static PyObject *t_locale_createKeywords(t_locale *self);
static PyObject *t_locale_getKeywordValue(t_locale *self, PyObject *arg);
#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
static PyObject *t_locale_setKeywordValue(t_locale *self, PyObject *args);
static PyObject *t_locale_removeKeywordValue(t_locale *self, PyObject *arg);
#endif
static PyObject *t_locale_isBogus(t_locale *self);
static PyObject *t_locale_setToBogus(t_locale *self);
#if U_ICU_VERSION_HEX >= 0x04040000
static PyObject *t_locale_getRoot(PyTypeObject *type);
#endif
static PyObject *t_locale_getEnglish(PyTypeObject *type);
static PyObject *t_locale_getFrench(PyTypeObject *type);
static PyObject *t_locale_getGerman(PyTypeObject *type);
static PyObject *t_locale_getItalian(PyTypeObject *type);
static PyObject *t_locale_getJapanese(PyTypeObject *type);
static PyObject *t_locale_getKorean(PyTypeObject *type);
static PyObject *t_locale_getChinese(PyTypeObject *type);
static PyObject *t_locale_getSimplifiedChinese(PyTypeObject *type);
static PyObject *t_locale_getTraditionalChinese(PyTypeObject *type);
static PyObject *t_locale_getFrance(PyTypeObject *type);
static PyObject *t_locale_getGermany(PyTypeObject *type);
static PyObject *t_locale_getItaly(PyTypeObject *type);
static PyObject *t_locale_getJapan(PyTypeObject *type);
static PyObject *t_locale_getKorea(PyTypeObject *type);
static PyObject *t_locale_getChina(PyTypeObject *type);
static PyObject *t_locale_getPRC(PyTypeObject *type);
static PyObject *t_locale_getTaiwan(PyTypeObject *type);
static PyObject *t_locale_getUK(PyTypeObject *type);
static PyObject *t_locale_getUS(PyTypeObject *type);
static PyObject *t_locale_getCanada(PyTypeObject *type);
static PyObject *t_locale_getCanadaFrench(PyTypeObject *type);
static PyObject *t_locale_getDefault(PyTypeObject *type);
static PyObject *t_locale_setDefault(PyTypeObject *type, PyObject *args);
static PyObject *t_locale_createFromName(PyTypeObject *type, PyObject *args);
static PyObject *t_locale_createCanonical(PyTypeObject *type, PyObject *arg);
static PyObject *t_locale_getAvailableLocales(PyTypeObject *type);
static PyObject *t_locale_getISOCountries(PyTypeObject *type);
static PyObject *t_locale_getISOLanguages(PyTypeObject *type);

static PyMethodDef t_locale_methods[] = {
    DECLARE_METHOD(t_locale, getLanguage, METH_NOARGS),
    DECLARE_METHOD(t_locale, getScript, METH_NOARGS),
    DECLARE_METHOD(t_locale, getCountry, METH_NOARGS),
    DECLARE_METHOD(t_locale, getVariant, METH_NOARGS),
    DECLARE_METHOD(t_locale, getName, METH_NOARGS),
    DECLARE_METHOD(t_locale, getBaseName, METH_NOARGS),
    DECLARE_METHOD(t_locale, getISO3Language, METH_NOARGS),
    DECLARE_METHOD(t_locale, getISO3Country, METH_NOARGS),
    DECLARE_METHOD(t_locale, getLCID, METH_NOARGS),
    DECLARE_METHOD(t_locale, getDisplayLanguage, METH_VARARGS),
    DECLARE_METHOD(t_locale, getDisplayScript, METH_VARARGS),
    DECLARE_METHOD(t_locale, getDisplayCountry, METH_VARARGS),
    DECLARE_METHOD(t_locale, getDisplayVariant, METH_VARARGS),
    DECLARE_METHOD(t_locale, getDisplayName, METH_VARARGS),
    DECLARE_METHOD(t_locale, createKeywords, METH_NOARGS),
    DECLARE_METHOD(t_locale, getKeywordValue, METH_O),
#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
    DECLARE_METHOD(t_locale, setKeywordValue, METH_VARARGS),
    DECLARE_METHOD(t_locale, removeKeywordValue, METH_O),
#endif
    DECLARE_METHOD(t_locale, isBogus, METH_NOARGS),
    DECLARE_METHOD(t_locale, setToBogus, METH_NOARGS),
#if U_ICU_VERSION_HEX >= 0x04040000
    DECLARE_METHOD(t_locale, getRoot, METH_NOARGS | METH_CLASS),
#endif
    DECLARE_METHOD(t_locale, getEnglish, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getFrench, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getGerman, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getItalian, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getJapanese, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getKorean, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getChinese, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getSimplifiedChinese, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getTraditionalChinese, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getFrance, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getGermany, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getItaly, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getJapan, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getKorea, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getChina, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getPRC, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getTaiwan, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getUK, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getUS, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getCanada, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getCanadaFrench, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getDefault, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, setDefault, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, createFromName, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, createCanonical, METH_O | METH_CLASS),
    DECLARE_METHOD(t_locale, getAvailableLocales, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getISOCountries, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_locale, getISOLanguages, METH_NOARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Locale, t_locale, UObject, Locale, t_locale_init, NULL);

PyObject *wrap_Locale(const Locale &locale)
{
    return wrap_Locale(new Locale(locale), T_OWNED);
}

/* ResourceBundle */

class t_resourcebundle : public _wrapper {
public:
    ResourceBundle *object;
};

static int t_resourcebundle_init(t_resourcebundle *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_resourcebundle_getSize(t_resourcebundle *self);
static PyObject *t_resourcebundle_getString(t_resourcebundle *self,
                                            PyObject *args);
static PyObject *t_resourcebundle_getUInt(t_resourcebundle *self);
static PyObject *t_resourcebundle_getInt(t_resourcebundle *self);
static PyObject *t_resourcebundle_getKey(t_resourcebundle *self);
static PyObject *t_resourcebundle_getName(t_resourcebundle *self);
static PyObject *t_resourcebundle_getType(t_resourcebundle *self);
static PyObject *t_resourcebundle_hasNext(t_resourcebundle *self);
static PyObject *t_resourcebundle_resetIterator(t_resourcebundle *self);
static PyObject *t_resourcebundle_getNext(t_resourcebundle *self);
static PyObject *t_resourcebundle_getNextString(t_resourcebundle *self,
                                                PyObject *args);
static PyObject *t_resourcebundle_get(t_resourcebundle *self, PyObject *arg);
static PyObject *t_resourcebundle_getWithFallback(t_resourcebundle *self,
                                                  PyObject *arg);
static PyObject *t_resourcebundle_getStringEx(t_resourcebundle *self,
                                              PyObject *args);
static PyObject *t_resourcebundle_getVersionNumber(t_resourcebundle *self);
static PyObject *t_resourcebundle_getBinary(t_resourcebundle *self);
static PyObject *t_resourcebundle_getIntVector(t_resourcebundle *self);
static PyObject *t_resourcebundle_getLocale(t_resourcebundle *self,
                                            PyObject *args);

#ifndef PYPY_VERSION
static PyObject *t_resourcebundle_setAppData(PyTypeObject *type,
                                             PyObject *args);
#endif

static PyMethodDef t_resourcebundle_methods[] = {
    DECLARE_METHOD(t_resourcebundle, getSize, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getString, METH_VARARGS),
    DECLARE_METHOD(t_resourcebundle, getUInt, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getInt, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getKey, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getName, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getType, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, hasNext, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, resetIterator, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getNext, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getNextString, METH_VARARGS),
    DECLARE_METHOD(t_resourcebundle, get, METH_O),
    DECLARE_METHOD(t_resourcebundle, getWithFallback, METH_O),
    DECLARE_METHOD(t_resourcebundle, getStringEx, METH_VARARGS),
    DECLARE_METHOD(t_resourcebundle, getVersionNumber, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getBinary, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getIntVector, METH_NOARGS),
    DECLARE_METHOD(t_resourcebundle, getLocale, METH_VARARGS),
#ifndef PYPY_VERSION
    DECLARE_METHOD(t_resourcebundle, setAppData, METH_CLASS | METH_VARARGS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(ResourceBundle, t_resourcebundle, UObject,
             ResourceBundle, t_resourcebundle_init, NULL);

static PyObject *wrap_ResourceBundle(const ResourceBundle &resourcebundle)
{
    return wrap_ResourceBundle(new ResourceBundle(resourcebundle), T_OWNED);
}


/* LocaleData */

class t_localedata : public _wrapper {
public:
    ULocaleData *object;
    char *locale_id;
};

static int t_localedata_init(t_localedata *self,
                             PyObject *args, PyObject *kwds);

static PyObject *t_localedata_getNoSubstitute(t_localedata *self);
static PyObject *t_localedata_setNoSubstitute(t_localedata *self,
                                              PyObject *arg);
static PyObject *t_localedata_getPaperSize(t_localedata *self);
static PyObject *t_localedata_getLocaleDisplayPattern(t_localedata *self);
static PyObject *t_localedata_getLocaleSeparator(t_localedata *self);
static PyObject *t_localedata_getDelimiter(t_localedata *self, PyObject *arg);
static PyObject *t_localedata_getMeasurementSystem(t_localedata *self);
static PyObject *t_localedata_getExemplarSet(t_localedata *self,
                                             PyObject *args);

static PyMethodDef t_localedata_methods[] = {
    DECLARE_METHOD(t_localedata, getNoSubstitute, METH_NOARGS),
    DECLARE_METHOD(t_localedata, setNoSubstitute, METH_O),
    DECLARE_METHOD(t_localedata, getPaperSize, METH_NOARGS),
    DECLARE_METHOD(t_localedata, getLocaleDisplayPattern, METH_NOARGS),
    DECLARE_METHOD(t_localedata, getLocaleSeparator, METH_NOARGS),
    DECLARE_METHOD(t_localedata, getDelimiter, METH_O),
    DECLARE_METHOD(t_localedata, getMeasurementSystem, METH_NOARGS),
    DECLARE_METHOD(t_localedata, getExemplarSet, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_localedata_dealloc(t_localedata *self)
{
    if (self->object)
    {
        ulocdata_close(self->object);
        self->object = NULL;
    }
    free(self->locale_id);
    self->locale_id = NULL;

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(LocaleData, t_localedata, ULocaleData, t_localedata_init,
               t_localedata_dealloc);


/* Locale */

static int t_locale_init(t_locale *self, PyObject *args, PyObject *kwds)
{
    charsArg language, country, variant;
    int lcid, len;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new Locale();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "n", &language))
        {
            self->object = new Locale(language);
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "i", &lcid))
        {
            char code[128];

            INT_STATUS_CALL(len = uloc_getLocaleForLCID(
                lcid, code, sizeof(code), &status));
            if ((size_t) len < sizeof(code))
            {
                self->object = new Locale(code);
                self->flags = T_OWNED;
            }
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "nn", &language, &country))
        {
            self->object = new Locale(language, country);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "nnn", &language, &country, &variant))
        {
            self->object = new Locale(language, country, variant);
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

static PyObject *t_locale_getLanguage(t_locale *self)
{
    return PyString_FromString(self->object->getLanguage());
}

static PyObject *t_locale_getScript(t_locale *self)
{
    return PyString_FromString(self->object->getScript());
}

static PyObject *t_locale_getCountry(t_locale *self)
{
    return PyString_FromString(self->object->getCountry());
}

static PyObject *t_locale_getVariant(t_locale *self)
{
    return PyString_FromString(self->object->getVariant());
}

static PyObject *t_locale_getName(t_locale *self)
{
    return PyString_FromString(self->object->getName());
}

static PyObject *t_locale_getBaseName(t_locale *self)
{
    return PyString_FromString(self->object->getBaseName());
}

static PyObject *t_locale_getISO3Language(t_locale *self)
{
    return PyString_FromString(self->object->getISO3Language());
}

static PyObject *t_locale_getISO3Country(t_locale *self)
{
    return PyString_FromString(self->object->getISO3Country());
}

static PyObject *t_locale_getLCID(t_locale *self)
{
    return PyInt_FromLong(self->object->getLCID());
}

static PyObject *t_locale_getDisplayLanguage(t_locale *self, PyObject *args)
{
    Locale *locale;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getDisplayLanguage(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->getDisplayLanguage(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object->getDisplayLanguage(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Locale),
                       &locale, &u))
        {
            self->object->getDisplayLanguage(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDisplayLanguage", args);
}

static PyObject *t_locale_getDisplayScript(t_locale *self, PyObject *args)
{
    Locale *locale;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getDisplayScript(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->getDisplayScript(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object->getDisplayScript(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Locale),
                       &locale, &u))
        {
            self->object->getDisplayScript(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDisplayScript", args);
}

static PyObject *t_locale_getDisplayCountry(t_locale *self, PyObject *args)
{
    Locale *locale;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getDisplayCountry(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->getDisplayCountry(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object->getDisplayCountry(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Locale),
                       &locale, &u))
        {
            self->object->getDisplayCountry(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDisplayCountry", args);
}

static PyObject *t_locale_getDisplayVariant(t_locale *self, PyObject *args)
{
    Locale *locale;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getDisplayVariant(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->getDisplayVariant(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object->getDisplayVariant(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Locale),
                       &locale, &u))
        {
            self->object->getDisplayVariant(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDisplayVariant", args);
}

static PyObject *t_locale_getDisplayName(t_locale *self, PyObject *args)
{
    Locale *locale;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getDisplayName(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            self->object->getDisplayName(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "U", &u))
        {
            self->object->getDisplayName(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU", TYPE_CLASSID(Locale), &locale, &u))
        {
            self->object->getDisplayName(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getDisplayName", args);
}

static PyObject *t_locale_createKeywords(t_locale *self)
{
    StringEnumeration *se;
    STATUS_CALL(se = self->object->createKeywords(status));

    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_locale_getKeywordValue(t_locale *self, PyObject *arg)
{
    charsArg name;

    if (!parseArg(arg, "n", &name))
    {
        char buf[ULOC_FULLNAME_CAPACITY];
        int32_t len;

        STATUS_CALL(len = self->object->getKeywordValue(
            name, buf, sizeof(buf) - 1, status));

        if (len == 0)
            Py_RETURN_NONE;

        return PyString_FromStringAndSize(buf, len);
    }

    return PyErr_SetArgsError((PyObject *) self, "getKeywordValue", arg);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
static PyObject *t_locale_setKeywordValue(t_locale *self, PyObject *args)
{
    charsArg name, value;

    if (!parseArgs(args, "nn", &name, &value))
    {
        STATUS_CALL(self->object->setKeywordValue(name, value, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setKeywordValue", args);
}

static PyObject *t_locale_removeKeywordValue(t_locale *self, PyObject *arg)
{
    charsArg name;

    if (!parseArg(arg, "n", &name))
    {
        STATUS_CALL(self->object->setKeywordValue(name, "", status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "removeKeywordValue", arg);
}
#endif

static PyObject *t_locale_isBogus(t_locale *self)
{
    int retval = self->object->isBogus();
    Py_RETURN_BOOL(retval);
}

static PyObject *t_locale_setToBogus(t_locale *self)
{
    self->object->setToBogus();
    Py_RETURN_NONE;
}

#if U_ICU_VERSION_HEX >= 0x04040000
static PyObject *t_locale_getRoot(PyTypeObject *self)
{
    return wrap_Locale(Locale::getRoot());
}
#endif

static PyObject *t_locale_getEnglish(PyTypeObject *self)
{
    return wrap_Locale(Locale::getEnglish());
}

static PyObject *t_locale_getFrench(PyTypeObject *self)
{
    return wrap_Locale(Locale::getFrench());
}

static PyObject *t_locale_getGerman(PyTypeObject *self)
{
    return wrap_Locale(Locale::getGerman());
}

static PyObject *t_locale_getItalian(PyTypeObject *self)
{
    return wrap_Locale(Locale::getItalian());
}

static PyObject *t_locale_getJapanese(PyTypeObject *self)
{
    return wrap_Locale(Locale::getJapanese());
}

static PyObject *t_locale_getKorean(PyTypeObject *self)
{
    return wrap_Locale(Locale::getKorean());
}

static PyObject *t_locale_getChinese(PyTypeObject *self)
{
    return wrap_Locale(Locale::getChinese());
}

static PyObject *t_locale_getSimplifiedChinese(PyTypeObject *self)
{
    return wrap_Locale(Locale::getSimplifiedChinese());
}

static PyObject *t_locale_getTraditionalChinese(PyTypeObject *self)
{
    return wrap_Locale(Locale::getTraditionalChinese());
}

static PyObject *t_locale_getFrance(PyTypeObject *self)
{
    return wrap_Locale(Locale::getFrance());
}

static PyObject *t_locale_getGermany(PyTypeObject *self)
{
    return wrap_Locale(Locale::getGermany());
}

static PyObject *t_locale_getItaly(PyTypeObject *self)
{
    return wrap_Locale(Locale::getItaly());
}

static PyObject *t_locale_getJapan(PyTypeObject *self)
{
    return wrap_Locale(Locale::getJapan());
}

static PyObject *t_locale_getKorea(PyTypeObject *self)
{
    return wrap_Locale(Locale::getKorea());
}

static PyObject *t_locale_getChina(PyTypeObject *self)
{
    return wrap_Locale(Locale::getChina());
}

static PyObject *t_locale_getPRC(PyTypeObject *self)
{
    return wrap_Locale(Locale::getPRC());
}

static PyObject *t_locale_getTaiwan(PyTypeObject *self)
{
    return wrap_Locale(Locale::getTaiwan());
}

static PyObject *t_locale_getUK(PyTypeObject *self)
{
    return wrap_Locale(Locale::getUK());
}

static PyObject *t_locale_getUS(PyTypeObject *self)
{
    return wrap_Locale(Locale::getUS());
}

static PyObject *t_locale_getCanada(PyTypeObject *self)
{
    return wrap_Locale(Locale::getCanada());
}

static PyObject *t_locale_getCanadaFrench(PyTypeObject *self)
{
    return wrap_Locale(Locale::getCanadaFrench());
}

static PyObject *t_locale_getDefault(PyTypeObject *self)
{
    return wrap_Locale(Locale::getDefault());
}

static PyObject *t_locale_setDefault(PyTypeObject *type, PyObject *args)
{
    Locale *locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(Locale::setDefault(NULL, status));
        Py_RETURN_NONE;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(Locale::setDefault(*locale, status)); /* transient */
            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError(type, "setDefault", args);
}

static PyObject *t_locale_createFromName(PyTypeObject *type, PyObject *args)
{
    Locale locale;
    charsArg name;

    switch (PyTuple_Size(args)) {
      case 0:
        locale = Locale::createFromName(NULL);
        return wrap_Locale(locale);
      case 1:
        if (!parseArgs(args, "n", &name))
        {
            locale = Locale::createFromName(name);
            return wrap_Locale(locale);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createFromName", args);
}

static PyObject *t_locale_createCanonical(PyTypeObject *type, PyObject *arg)
{
    Locale locale;
    charsArg name;

    if (!parseArg(arg, "n", &name))
    {
        locale = Locale::createCanonical(name);
        return wrap_Locale(locale);
    }

    return PyErr_SetArgsError(type, "createCanonical", arg);
}

static PyObject *t_locale_getAvailableLocales(PyTypeObject *type)
{
    int count;
    const Locale *locales = Locale::getAvailableLocales(count);
    PyObject *dict = PyDict_New();

    for (int32_t i = 0; i < count; i++) {
        Locale *locale = (Locale *) locales + i;
        PyObject *obj = wrap_Locale(locale, 0);
        PyDict_SetItemString(dict, locale->getName(), obj);
        Py_DECREF(obj);
    }

    return dict;
}

static PyObject *t_locale_getISOCountries(PyTypeObject *type)
{
    const char *const *countries = Locale::getISOCountries();
    PyObject *list;
    int len = 0;

    while (countries[len] != NULL) len += 1;
    list = PyList_New(len);

    for (int i = 0; i < len; i++) {
        PyObject *str = PyString_FromStringAndSize(countries[i], 2);
        PyList_SET_ITEM(list, i, str);
    }

    return list;
}

static PyObject *t_locale_getISOLanguages(PyTypeObject *type)
{
    const char *const *languages = Locale::getISOLanguages();
    PyObject *list;
    int len = 0;

    while (languages[len] != NULL) len += 1;
    list = PyList_New(len);

    for (int i = 0; i < len; i++) {
        PyObject *str = PyString_FromString(languages[i]);
        PyList_SET_ITEM(list, i, str);
    }

    return list;
}

static PyObject *t_locale_str(t_locale *self)
{
    return PyString_FromString(self->object->getName());
}

static long t_locale_hash(t_locale *self)
{
    return (long) self->object->hashCode();
}


/* ResourceBundle */

static int t_resourcebundle_init(t_resourcebundle *self,
                                 PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    Locale *locale;
    ResourceBundle *bundle;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(bundle = new ResourceBundle(status));
        self->object = bundle;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(bundle = new ResourceBundle(*u, status));
            self->object = bundle;
            self->flags = T_OWNED;
            break;
        }
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(Locale),
                       &u, &_u, &locale))
        {
            INT_STATUS_CALL(bundle = new ResourceBundle(*u, *locale, status));
            self->object = bundle;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_resourcebundle_getSize(t_resourcebundle *self)
{
    return PyInt_FromLong(self->object->getSize());
}

static PyObject *t_resourcebundle_getString(t_resourcebundle *self,
                                            PyObject *args)
{
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(_u = self->object->getString(status));
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            STATUS_CALL(u->setTo(self->object->getString(status)));
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getString", args);
}

static PyObject *t_resourcebundle_getUInt(t_resourcebundle *self)
{
    int n;

    STATUS_CALL(n = self->object->getUInt(status));
    return PyInt_FromLong(n);
}

static PyObject *t_resourcebundle_getInt(t_resourcebundle *self)
{
    int n;

    STATUS_CALL(n = self->object->getInt(status));
    return PyInt_FromLong(n);
}

static PyObject *t_resourcebundle_getKey(t_resourcebundle *self)
{
    return PyString_FromString(self->object->getKey());
}

static PyObject *t_resourcebundle_getName(t_resourcebundle *self)
{
    return PyString_FromString(self->object->getName());
}

static PyObject *t_resourcebundle_getType(t_resourcebundle *self)
{
    return PyInt_FromLong((long) self->object->getType());
}

static PyObject *t_resourcebundle_hasNext(t_resourcebundle *self)
{
    int b = self->object->hasNext();
    Py_RETURN_BOOL(b);
}

static PyObject *t_resourcebundle_resetIterator(t_resourcebundle *self)
{
    self->object->resetIterator();
    Py_RETURN_NONE;
}

static PyObject *t_resourcebundle_getNext(t_resourcebundle *self)
{
    UErrorCode status = U_ZERO_ERROR;
    ResourceBundle rb = self->object->getNext(status);

    if (U_FAILURE(status))
        return ICUException(status).reportError();

    return wrap_ResourceBundle(rb);
}

static PyObject *t_resourcebundle_getNextString(t_resourcebundle *self,
                                                PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(_u = self->object->getNextString(status));
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            STATUS_CALL(u->setTo(self->object->getNextString(status)));
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getNextString", args);
}

static PyObject *t_resourcebundle_get(t_resourcebundle *self, PyObject *arg)
{
    UErrorCode status = U_ZERO_ERROR;
    charsArg key;
    int i;

    if (!parseArg(arg, "i", &i))
    {
        ResourceBundle rb = self->object->get(i, status);

        if (U_FAILURE(status))
            return ICUException(status).reportError();

        return wrap_ResourceBundle(rb);
    }

    if (!parseArg(arg, "n", &key))
    {
        ResourceBundle rb = self->object->get(key, status);

        if (U_FAILURE(status))
            return ICUException(status).reportError();

        return wrap_ResourceBundle(rb);
    }

    return PyErr_SetArgsError((PyObject *) self, "get", arg);
}

static PyObject *t_resourcebundle_getWithFallback(t_resourcebundle *self,
                                                  PyObject *arg)
{
    UErrorCode status = U_ZERO_ERROR;
    charsArg key;

    if (!parseArg(arg, "n", &key))
    {
        ResourceBundle rb = self->object->getWithFallback(key, status);

        if (U_FAILURE(status))
            return ICUException(status).reportError();

        return wrap_ResourceBundle(rb);
    }

    return PyErr_SetArgsError((PyObject *) self, "getWithFallback", arg);
}

static PyObject *t_resourcebundle_getStringEx(t_resourcebundle *self,
                                              PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    charsArg key;
    int i;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &i))
        {
            STATUS_CALL(_u = self->object->getStringEx(i, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
        if (!parseArgs(args, "n", &key))
        {
            STATUS_CALL(_u = self->object->getStringEx(key, status));
            return PyUnicode_FromUnicodeString(&_u);
        }
      case 2:
        if (!parseArgs(args, "iU", &i, &u))
        {
            STATUS_CALL(u->setTo(self->object->getStringEx(i, status)));
            Py_RETURN_ARG(args, 1);
        }
        if (!parseArgs(args, "nU", &key, &u))
        {
            STATUS_CALL(u->setTo(self->object->getStringEx(key, status)));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getStringEx", args);
}

static PyObject *t_resourcebundle_getVersionNumber(t_resourcebundle *self)
{
    return PyString_FromString(self->object->getVersionNumber());
}

static PyObject *t_resourcebundle_getBinary(t_resourcebundle *self)
{
    int32_t len;
    const uint8_t *data;

    STATUS_CALL(data = self->object->getBinary(len, status));

    return PyString_FromStringAndSize((const char *) data, len);
}

static PyObject *t_resourcebundle_getIntVector(t_resourcebundle *self)
{
    int32_t len;
    const int32_t *data;

    STATUS_CALL(data = self->object->getIntVector(len, status));

    PyObject *list = PyList_New(len);

    for (int i = 0; i < len; i++)
        PyList_SET_ITEM(list, i, PyInt_FromLong(data[i]));

    return list;
}

static PyObject *t_resourcebundle_getLocale(t_resourcebundle *self,
                                            PyObject *args)
{
    ULocDataLocaleType type;

    switch (PyTuple_Size(args)) {
      case 0:
        return wrap_Locale(self->object->getLocale());
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            Locale locale;

            STATUS_CALL(locale = self->object->getLocale(type, status));
            return wrap_Locale(locale);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocale", args);
}

#ifndef PYPY_VERSION
#if defined(_MSC_VER) || defined(__WIN32)

static PyObject *t_resourcebundle_setAppData(PyTypeObject *type,
                                             PyObject *args)
{
    charsArg packageName, path;

    if (!parseArgs(args, "nf", &packageName, &path))
    {
        HANDLE fd = CreateFile(path, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        UErrorCode status = U_ZERO_ERROR;
        DWORD dwSize;
        HANDLE hMap;
        LPVOID data;

        if (fd == INVALID_HANDLE_VALUE)
            return PyErr_SetFromWindowsErrWithFilename(0, path);

        dwSize = GetFileSize(fd, NULL);
        if (dwSize == INVALID_FILE_SIZE)
        {
            PyErr_SetFromWindowsErrWithFilename(0, path);
            CloseHandle(fd);

            return NULL;
        }

        hMap = CreateFileMapping(fd, NULL, PAGE_READONLY, 0, dwSize, NULL);
        if (!hMap)
        {
            PyErr_SetFromWindowsErrWithFilename(0, path);
            CloseHandle(fd);

            return NULL;
        }
        CloseHandle(fd);

        data = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
        if (!data)
        {
            PyErr_SetFromWindowsErrWithFilename(0, path);
            CloseHandle(hMap);

            return NULL;
        }
        CloseHandle(hMap);

        udata_setAppData(packageName, data, &status);
        if (U_FAILURE(status))
        {
            UnmapViewOfFile(data);
            return ICUException(status).reportError();
        }

        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError(type, "setAppData", args);
}

#else

static PyObject *t_resourcebundle_setAppData(PyTypeObject *type,
                                             PyObject *args)
{
    charsArg packageName, path;

    if (!parseArgs(args, "nf", &packageName, &path))
    {
        int fd = open(path, O_RDONLY);
        UErrorCode status = U_ZERO_ERROR;
        struct stat buf;
        void *data;

        if (fd < 0)
            return PyErr_SetFromErrnoWithFilename(PyExc_ValueError, path);

        if (fstat(fd, &buf) < 0)
        {
            PyErr_SetFromErrnoWithFilename(PyExc_ValueError, path);
            close(fd);

            return NULL;
        }

        data = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (data == MAP_FAILED)
        {
            PyErr_SetFromErrnoWithFilename(PyExc_ValueError, path);
            close(fd);

            return NULL;
        }
        close(fd);

        udata_setAppData(packageName, data, &status);
        if (U_FAILURE(status))
        {
            munmap(data, buf.st_size);
            return ICUException(status).reportError();
        }

        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError(type, "setAppData", args);
}
#endif
#endif  // !PYPY_VERSION

static PyObject *t_resourcebundle_iter(t_resourcebundle *self)
{
    self->object->resetIterator();

    Py_INCREF(self);
    return (PyObject *) self;
}

static PyObject *t_resourcebundle_next(t_resourcebundle *self)
{
    if (self->object->hasNext())
    {
        UErrorCode status = U_ZERO_ERROR;
        ResourceBundle rb = self->object->getNext(status);

        if (U_FAILURE(status))
            return ICUException(status).reportError();

        return wrap_ResourceBundle(rb);
    }

    PyErr_SetNone(PyExc_StopIteration);
    return NULL;
}

static PyObject *t_resourcebundle_str(t_resourcebundle *self)
{
    switch (self->object->getType()) {
      case URES_NONE:
        return PyString_FromString("URES_NONE");
      case URES_STRING:
        return PyString_FromString("URES_STRING");
      case URES_BINARY:
        return PyString_FromString("URES_BINARY");
      case URES_TABLE:
        return PyString_FromString("URES_TABLE");
      case URES_ALIAS:
        return PyString_FromString("URES_ALIAS");
      case URES_ARRAY:
        return PyString_FromString("URES_ARRAY");
      case URES_INT_VECTOR:
        return PyString_FromString("URES_INT_VECTOR");
      case RES_RESERVED:
        return PyString_FromString("RES_RESERVED");
      default:
        return PyString_FromString("unknown");
    }
}


/* LocaleData */

static int t_localedata_init(t_localedata *self, PyObject *args, PyObject *kwds)
{
    charsArg id;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "n", &id))
        {
            ULocaleData *locale_data;

            INT_STATUS_CALL(locale_data = ulocdata_open(id, &status));
            self->object = locale_data;
            self->locale_id = strdup((const char *) id);
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

static PyObject *t_localedata_getNoSubstitute(t_localedata *self)
{
    if (ulocdata_getNoSubstitute(self->object))
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_localedata_setNoSubstitute(t_localedata *self, PyObject *arg)
{
    int setting;

    if (!parseArg(arg, "b", &setting))
    {
        ulocdata_setNoSubstitute(self->object, setting);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setNoSubstitute", arg);
}

static PyObject *t_localedata_getPaperSize(t_localedata *self)
{
    int32_t width, height;

    STATUS_CALL(ulocdata_getPaperSize(self->locale_id,
                                      &width, &height, &status));

    return Py_BuildValue("ii", width, height);
}

static PyObject *t_localedata_getLocaleDisplayPattern(t_localedata *self)
{
    UChar buffer[256];
    int size;

    STATUS_CALL(size = ulocdata_getLocaleDisplayPattern(self->object, buffer,
                                                        255, &status));

    return PyUnicode_FromUnicodeString(buffer, size);
}

static PyObject *t_localedata_getLocaleSeparator(t_localedata *self)
{
    UChar buffer[256];
    int size;

    STATUS_CALL(size = ulocdata_getLocaleSeparator(self->object, buffer,
                                                   255, &status));

    return PyUnicode_FromUnicodeString(buffer, size);
}

static PyObject *t_localedata_getDelimiter(t_localedata *self, PyObject *arg)
{
    ULocaleDataDelimiterType type;

    if (!parseArg(arg, "i", &type))
    {
        UChar buffer[256];
        int size;

        STATUS_CALL(size = ulocdata_getDelimiter(self->object, type, buffer,
                                                 255, &status));

        return PyUnicode_FromUnicodeString(buffer, size);
    }

    return PyErr_SetArgsError((PyObject *) self, "getDelimiter", arg);
}

static PyObject *t_localedata_getMeasurementSystem(t_localedata *self)
{
    UMeasurementSystem ms;

    STATUS_CALL(ms = ulocdata_getMeasurementSystem(self->locale_id, &status));

    return PyInt_FromLong(ms);
}

static PyObject *t_localedata_getExemplarSet(t_localedata *self, PyObject *args)
{
    int options;
    ULocaleDataExemplarSetType type;

    switch (PyTuple_Size(args)) {
      case 0:
        {
            USet *set;

            STATUS_CALL(set = ulocdata_getExemplarSet(self->object, NULL,
                                                      0, ULOCDATA_ES_STANDARD,
                                                      &status));
            return wrap_UnicodeSet(UnicodeSet::fromUSet(set), T_OWNED);
        }
        break;
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            USet *set;

            STATUS_CALL(set = ulocdata_getExemplarSet(self->object, NULL,
                                                      0, type, &status));
            return wrap_UnicodeSet(UnicodeSet::fromUSet(set), T_OWNED);
        }
        break;
      case 2:
        if (!parseArgs(args, "ii", &options, &type))
        {
            USet *set;

            STATUS_CALL(set = ulocdata_getExemplarSet(self->object, NULL,
                                                      options, type, &status));
            return wrap_UnicodeSet(UnicodeSet::fromUSet(set), T_OWNED);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "getExemplarSet", args);
}


void _init_locale(PyObject *m)
{
    LocaleType_.tp_str = (reprfunc) t_locale_str;
    LocaleType_.tp_hash = (hashfunc) t_locale_hash;
    ResourceBundleType_.tp_iter = (getiterfunc) t_resourcebundle_iter;
    ResourceBundleType_.tp_iternext = (iternextfunc) t_resourcebundle_next;
    ResourceBundleType_.tp_str = (reprfunc) t_resourcebundle_str;

    INSTALL_CONSTANTS_TYPE(ULocDataLocaleType, m);
    INSTALL_CONSTANTS_TYPE(UResType, m);
    INSTALL_CONSTANTS_TYPE(ULocaleDataDelimiterType, m);
    INSTALL_CONSTANTS_TYPE(ULocaleDataExemplarSetType, m);
    INSTALL_CONSTANTS_TYPE(UMeasurementSystem, m);
    REGISTER_TYPE(Locale, m);
    REGISTER_TYPE(ResourceBundle, m);
    INSTALL_STRUCT(LocaleData, m);

    INSTALL_ENUM(ULocDataLocaleType, "ACTUAL_LOCALE", ULOC_ACTUAL_LOCALE);
    INSTALL_ENUM(ULocDataLocaleType, "VALID_LOCALE", ULOC_VALID_LOCALE);

    INSTALL_ENUM(UResType, "NONE", URES_NONE);
    INSTALL_ENUM(UResType, "STRING", URES_STRING);
    INSTALL_ENUM(UResType, "BINARY", URES_BINARY);
    INSTALL_ENUM(UResType, "TABLE", URES_TABLE);
    INSTALL_ENUM(UResType, "ALIAS", URES_ALIAS);
    INSTALL_ENUM(UResType, "INT", URES_INT);
    INSTALL_ENUM(UResType, "ARRAY", URES_ARRAY);
    INSTALL_ENUM(UResType, "INT_VECTOR", URES_INT_VECTOR);
    INSTALL_ENUM(UResType, "RESERVED", RES_RESERVED);

    INSTALL_ENUM(ULocaleDataDelimiterType, "QUOTATION_START",
                 ULOCDATA_QUOTATION_START);
    INSTALL_ENUM(ULocaleDataDelimiterType, "QUOTATION_END",
                 ULOCDATA_QUOTATION_END);
    INSTALL_ENUM(ULocaleDataDelimiterType, "ALT_QUOTATION_START",
                 ULOCDATA_ALT_QUOTATION_START);
    INSTALL_ENUM(ULocaleDataDelimiterType, "ALT_QUOTATION_END",
                 ULOCDATA_ALT_QUOTATION_END);

    INSTALL_ENUM(ULocaleDataExemplarSetType, "ES_STANDARD",
                 ULOCDATA_ES_STANDARD);
    INSTALL_ENUM(ULocaleDataExemplarSetType, "ES_AUXILIARY",
                 ULOCDATA_ES_AUXILIARY);
#if U_ICU_VERSION_HEX >= 0x04080000
    INSTALL_ENUM(ULocaleDataExemplarSetType, "ES_INDEX",
                 ULOCDATA_ES_INDEX);
#endif

    INSTALL_ENUM(UMeasurementSystem, "SI", UMS_SI);
    INSTALL_ENUM(UMeasurementSystem, "US", UMS_US);

    // options for LocaleData.getExemplarSet()
    INSTALL_MODULE_INT(m, USET_IGNORE_SPACE);
    INSTALL_MODULE_INT(m, USET_CASE_INSENSITIVE);
    INSTALL_MODULE_INT(m, USET_ADD_CASE_MAPPINGS);
}
