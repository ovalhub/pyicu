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
#include "collator.h"
#include "iterators.h"
#include "unicodeset.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UCollationResult);
DECLARE_CONSTANTS_TYPE(UCollAttribute);
DECLARE_CONSTANTS_TYPE(UCollAttributeValue);

/* CollationKey */

class t_collationkey : public _wrapper {
public:
    CollationKey *object;
};

static int t_collationkey_init(t_collationkey *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_collationkey_isBogus(t_collationkey *self);
static PyObject *t_collationkey_compareTo(t_collationkey *self, PyObject *arg);
static PyObject *t_collationkey_getByteArray(t_collationkey *self);

static PyMethodDef t_collationkey_methods[] = {
    DECLARE_METHOD(t_collationkey, isBogus, METH_NOARGS),
    DECLARE_METHOD(t_collationkey, compareTo, METH_O),
    DECLARE_METHOD(t_collationkey, getByteArray, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CollationKey, t_collationkey, UObject, CollationKey,
             t_collationkey_init, NULL);

/* Collator */

class t_collator : public _wrapper {
public:
    Collator *object;
};

static PyObject *t_collator_compare(t_collator *self, PyObject *args);
static PyObject *t_collator_greater(t_collator *self, PyObject *args);
static PyObject *t_collator_greaterOrEqual(t_collator *self, PyObject *args);
static PyObject *t_collator_equals(t_collator *self, PyObject *args);
static PyObject *t_collator_getCollationKey(t_collator *self, PyObject *args);
static PyObject *t_collator_getSortKey(t_collator *self, PyObject *args);
static PyObject *t_collator_getStrength(t_collator *self);
static PyObject *t_collator_setStrength(t_collator *self, PyObject *arg);
static PyObject *t_collator_getLocale(t_collator *self, PyObject *args);
static PyObject *t_collator_getAttribute(t_collator *self, PyObject *arg);
static PyObject *t_collator_setAttribute(t_collator *self, PyObject *args);
static PyObject *t_collator_getTailoredSet(t_collator *self);
static PyObject *t_collator_getVariableTop(t_collator *self);
static PyObject *t_collator_setVariableTop(t_collator *self, PyObject *arg);
static PyObject *t_collator_createInstance(PyTypeObject *type, PyObject *args);
static PyObject *t_collator_getAvailableLocales(PyTypeObject *type);
static PyObject *t_collator_getKeywords(PyTypeObject *type);
static PyObject *t_collator_getKeywordValues(PyTypeObject *type, PyObject *arg);
static PyObject *t_collator_getFunctionalEquivalent(PyTypeObject *type,
                                                    PyObject *args);

static PyMethodDef t_collator_methods[] = {
    DECLARE_METHOD(t_collator, compare, METH_VARARGS),
    DECLARE_METHOD(t_collator, greater, METH_VARARGS),
    DECLARE_METHOD(t_collator, greaterOrEqual, METH_VARARGS),
    DECLARE_METHOD(t_collator, equals, METH_VARARGS),
    DECLARE_METHOD(t_collator, getCollationKey, METH_VARARGS),
    DECLARE_METHOD(t_collator, getSortKey, METH_VARARGS),
    DECLARE_METHOD(t_collator, getStrength, METH_NOARGS),
    DECLARE_METHOD(t_collator, setStrength, METH_O),
    DECLARE_METHOD(t_collator, getLocale, METH_VARARGS),
    DECLARE_METHOD(t_collator, getAttribute, METH_O),
    DECLARE_METHOD(t_collator, setAttribute, METH_VARARGS),
    DECLARE_METHOD(t_collator, getTailoredSet, METH_O),
    DECLARE_METHOD(t_collator, getVariableTop, METH_NOARGS),
    DECLARE_METHOD(t_collator, setVariableTop, METH_O),
    DECLARE_METHOD(t_collator, createInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_collator, getAvailableLocales, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_collator, getKeywords, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_collator, getKeywordValues, METH_O | METH_CLASS),
    DECLARE_METHOD(t_collator, getFunctionalEquivalent, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Collator, t_collator, UObject, Collator, abstract_init, NULL);

/* RuleBasedCollator */

class t_rulebasedcollator : public _wrapper {
public:
    RuleBasedCollator *object;
    PyObject *buf;
    PyObject *base;
};

static int t_rulebasedcollator_init(t_rulebasedcollator *self,
                                    PyObject *args, PyObject *kwds);
static PyObject *t_rulebasedcollator_getRules(t_rulebasedcollator *self,
                                              PyObject *args);
static PyObject *t_rulebasedcollator_createCollationElementIterator(t_rulebasedcollator *self, PyObject *arg);
static PyObject *t_rulebasedcollator_cloneBinary(t_rulebasedcollator *self);

static PyMethodDef t_rulebasedcollator_methods[] = {
    DECLARE_METHOD(t_rulebasedcollator, getRules, METH_VARARGS),
    DECLARE_METHOD(t_rulebasedcollator, createCollationElementIterator, METH_O),
    DECLARE_METHOD(t_rulebasedcollator, cloneBinary, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static void t_rulebasedcollator_dealloc(t_rulebasedcollator *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->buf);
    Py_CLEAR(self->base);

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(RuleBasedCollator, t_rulebasedcollator, Collator,
             RuleBasedCollator, t_rulebasedcollator_init,
             t_rulebasedcollator_dealloc);


/* CollationKey */

static int t_collationkey_init(t_collationkey *self,
                               PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new CollationKey();
        self->flags = T_OWNED;
        break;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
        
    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_collationkey_isBogus(t_collationkey *self)
{
    int b = self->object->isBogus();
    Py_RETURN_BOOL(b);
}

static PyObject *t_collationkey_compareTo(t_collationkey *self, PyObject *arg)
{
    CollationKey *key;

    if (!parseArg(arg, "P", TYPE_CLASSID(CollationKey), &key))
    {
        UCollationResult result;
        STATUS_CALL(result = self->object->compareTo(*key, status));
        return PyInt_FromLong(result);
    }

    return PyErr_SetArgsError((PyObject *) self, "compareTo", arg);
}

static PyObject *t_collationkey_getByteArray(t_collationkey *self)
{
    int32_t count;
    const uint8_t *array = self->object->getByteArray(count);

    return PyBytes_FromStringAndSize((char *) array, count);
}

DEFINE_RICHCMP(CollationKey, t_collationkey);


/* Collator */

static PyObject *t_collator_compare(t_collator *self, PyObject *args)
{
    UCollationResult result;
    UnicodeString *u, *v;
    UnicodeString _u, _v;
    int len;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
        {
            STATUS_CALL(result = self->object->compare(*u, *v, status));
            return PyInt_FromLong(result);
        }
        break;
      case 3:
        if (!parseArgs(args, "SSi", &u, &_u, &v, &_v, &len))
        {
            STATUS_CALL(result = self->object->compare(*u, *v, len, status));
            return PyInt_FromLong(result);
        }
        break;
    }
        
    return PyErr_SetArgsError((PyObject *) self, "compare", args);
}

static PyObject *t_collator_greater(t_collator *self, PyObject *args)
{
    int b;
    UnicodeString *u, *v;
    UnicodeString _u, _v;

    if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
    {
        b = self->object->greater(*u, *v);
        Py_RETURN_BOOL(b);
    }
        
    return PyErr_SetArgsError((PyObject *) self, "greater", args);
}

static PyObject *t_collator_greaterOrEqual(t_collator *self, PyObject *args)
{
    int b;
    UnicodeString *u, *v;
    UnicodeString _u, _v;

    if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
    {
        b = self->object->greaterOrEqual(*u, *v);
        Py_RETURN_BOOL(b);
    }
        
    return PyErr_SetArgsError((PyObject *) self, "greaterOrEqual", args);
}

static PyObject *t_collator_equals(t_collator *self, PyObject *args)
{
    int b;
    UnicodeString *u, *v;
    UnicodeString _u, _v;

    if (!parseArgs(args, "SS", &u, &_u, &v, &_v))
    {
        b = self->object->equals(*u, *v);
        Py_RETURN_BOOL(b);
    }
        
    return PyErr_SetArgsError((PyObject *) self, "equals", args);
}

static PyObject *t_collator_getCollationKey(t_collator *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    CollationKey *key;
    CollationKey _key;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(self->object->getCollationKey(*u, _key, status));
            return wrap_CollationKey(new CollationKey(_key), T_OWNED);
        }
        break;
      case 2:
        if (!parseArgs(args, "SP", TYPE_CLASSID(CollationKey),
                       &u, &_u, &key))
        {
            STATUS_CALL(self->object->getCollationKey(*u, *key, status));
            Py_RETURN_ARG(args, 1);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getCollationKey", args);
}

static PyObject *t_collator_getSortKey(t_collator *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    uint32_t len, size;
    uint8_t *buf;
    PyObject *key;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            len = u->length() * 4 + 8;
            buf = (uint8_t *) malloc(len);
          retry:
            if (buf == NULL)
                return PyErr_NoMemory();

            size = self->object->getSortKey(*u, buf, len);
            if (size <= len)
            {
                key = PyBytes_FromStringAndSize((char *) buf, size);
                free(buf);
            }
            else
            {
                len = size;
                buf = (uint8_t *) realloc(buf, len);
                goto retry;
            }

            return key;
        }
        break;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &len))
        {
            buf = (uint8_t *) calloc(len, 1);
            if (buf == NULL)
                return PyErr_NoMemory();

            len = self->object->getSortKey(*u, buf, len);
            key = PyBytes_FromStringAndSize((char *) buf, len);
            free(buf);

            return key;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getSortKey", args);
}

static PyObject *t_collator_getStrength(t_collator *self)
{
    return PyInt_FromLong(self->object->getStrength());
}

static PyObject *t_collator_setStrength(t_collator *self, PyObject *arg)
{
    Collator::ECollationStrength strength;

    if (!parseArg(arg, "i", &strength))
    {
        self->object->setStrength(strength);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setStrength", arg);
}

static PyObject *t_collator_getLocale(t_collator *self, PyObject *args)
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

static inline PyObject *wrap_Collator(Collator *collator)
{
    RETURN_WRAPPED_IF_ISINSTANCE(collator, RuleBasedCollator);
    return wrap_Collator(collator, T_OWNED);
}

static PyObject *t_collator_createInstance(PyTypeObject *type, PyObject *args)
{
    Locale *locale;
    Collator *collator;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(collator = Collator::createInstance(status));
        return wrap_Collator(collator);
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(Locale), &locale))
        {
            STATUS_CALL(collator = Collator::createInstance(*locale, status));
            return wrap_Collator(collator);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createInstance", args);
}

static PyObject *t_collator_getKeywords(PyTypeObject *type)
{
    StringEnumeration *e;

    STATUS_CALL(e = Collator::getKeywords(status));
    return wrap_StringEnumeration(e, T_OWNED);
}

static PyObject *t_collator_getKeywordValues(PyTypeObject *type, PyObject *arg)
{
    StringEnumeration *e;
    charsArg keyword;

    if (!parseArg(arg, "n", &keyword))
    {
        STATUS_CALL(e = Collator::getKeywordValues(keyword, status));
        return wrap_StringEnumeration(e, T_OWNED);
    }
            
    return PyErr_SetArgsError(type, "getKeywordValues", arg);
}

static PyObject *t_collator_getAvailableLocales(PyTypeObject *type)
{
    int count;
    const Locale *locales = Collator::getAvailableLocales(count);
    PyObject *dict = PyDict_New();

    for (int32_t i = 0; i < count; i++) {
        Locale *locale = (Locale *) locales + i;
        PyObject *obj = wrap_Locale(locale, 0);
        PyDict_SetItemString(dict, locale->getName(), obj);
	Py_DECREF(obj);
    }

    return dict;
}

static PyObject *t_collator_getFunctionalEquivalent(PyTypeObject *type,
                                                    PyObject *args)
{
    UBool isAvailable;
    Locale *locale;
    charsArg keyword;
    
    if (!parseArgs(args, "nP", TYPE_CLASSID(Locale),
                   &keyword, &locale))
    {
        Locale result(*locale);
        STATUS_CALL(Collator::getFunctionalEquivalent(keyword, result,
                                                      isAvailable, status));
        return Py_BuildValue("(OO)", wrap_Locale(result),
                             isAvailable ? Py_True : Py_False);
    }

    return PyErr_SetArgsError(type, "getFunctionalEquivalent", args);
}

static PyObject *t_collator_getAttribute(t_collator *self, PyObject *arg)
{
    UColAttribute attribute;

    if (!parseArg(arg, "i", &attribute))
    {
        UColAttributeValue value;
        STATUS_CALL(value = self->object->getAttribute(attribute, status));

        return PyInt_FromLong(value);
    }

    return PyErr_SetArgsError((PyObject *) self, "getAttribute", arg);
}

static PyObject *t_collator_setAttribute(t_collator *self, PyObject *args)
{
    UColAttribute attribute;
    UColAttributeValue value;

    if (!parseArgs(args, "ii", &attribute, &value))
    {
        STATUS_CALL(self->object->setAttribute(attribute, value, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAttribute", args);
}

static PyObject *t_collator_getTailoredSet(t_collator *self)
{
    UnicodeSet *set;

    STATUS_CALL(set = self->object->getTailoredSet(status));
    return wrap_UnicodeSet(set, T_OWNED);
}

static PyObject *t_collator_getVariableTop(t_collator *self)
{
    uint32_t top;

    STATUS_CALL(top = self->object->getVariableTop(status));
    return PyInt_FromLong(top >> 16);
}

static PyObject *t_collator_setVariableTop(t_collator *self, PyObject *arg)
{
    UnicodeString *u, _u;
    uint32_t top;

    if (!parseArg(arg, "i", &top))
    {
        STATUS_CALL(self->object->setVariableTop(top << 16, status));
        Py_RETURN_NONE;
    }
    else if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->setVariableTop(*u, status)); /* transient */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setVariableTop", arg);
}


static long t_collator_hash(t_collator *self)
{
  return (long) self->object->hashCode();
}


/* RuleBasedCollator */

static int t_rulebasedcollator_init(t_rulebasedcollator *self,
                                    PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    UnicodeString _u;
    RuleBasedCollator *collator;
    Collator::ECollationStrength strength;
    UColAttributeValue decompositionMode;
    PyObject *buf, *base;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            INT_STATUS_CALL(collator = new RuleBasedCollator(*u, status));
            self->object = collator;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "CO", &RuleBasedCollatorType_, &buf, &base))
        {
            INT_STATUS_CALL(collator = new RuleBasedCollator((uint8_t *) PyBytes_AS_STRING(buf), PyBytes_GET_SIZE(buf), ((t_rulebasedcollator *) base)->object, status));
            self->object = collator;
            self->flags = T_OWNED;
            self->buf = buf; Py_INCREF(buf);
            self->base = base; Py_INCREF(base);
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &strength, &decompositionMode))
        {
            INT_STATUS_CALL(collator = new RuleBasedCollator(*u, strength, decompositionMode, status));
            self->object = collator;
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

static PyObject *t_rulebasedcollator_getRules(t_rulebasedcollator *self,
                                              PyObject *args)
{
    UnicodeString u = self->object->getRules();
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_rulebasedcollator_createCollationElementIterator(t_rulebasedcollator *self, PyObject *arg)
{
    UnicodeString *u, _u;
    CharacterIterator *chars;
    CollationElementIterator *iterator;

    if (!parseArg(arg, "S", &u, &_u))
    {
        iterator = self->object->createCollationElementIterator(*u);
        return wrap_CollationElementIterator(iterator, T_OWNED);
    }
    else if (!parseArg(arg, "P", TYPE_ID(CharacterIterator), &chars))
    {
        iterator = self->object->createCollationElementIterator(*chars);
        return wrap_CollationElementIterator(iterator, T_OWNED);
    }

    return PyErr_SetArgsError((PyObject *) self, "createCollationElementIterator", arg);
}

static PyObject *t_rulebasedcollator_cloneBinary(t_rulebasedcollator *self)
{
    UErrorCode status = U_ZERO_ERROR;
    PyObject *result;
    int32_t len;

    len = self->object->cloneBinary(NULL, 0, status);
    result = PyBytes_FromStringAndSize(NULL, len);
    if (!result)
        return NULL;

    STATUS_CALL(len = self->object->cloneBinary((uint8_t *) PyBytes_AS_STRING(result), len, status));

    return result;
}

static PyObject *t_rulebasedcollator_str(t_rulebasedcollator *self)
{
    UnicodeString u = self->object->getRules();
    return PyUnicode_FromUnicodeString(&u);
}

DEFINE_RICHCMP(RuleBasedCollator, t_rulebasedcollator);


void _init_collator(PyObject *m)
{
    CollationKeyType_.tp_richcompare = (richcmpfunc) t_collationkey_richcmp;
    CollatorType_.tp_hash = (hashfunc) t_collator_hash;
    RuleBasedCollatorType_.tp_str = (reprfunc) t_rulebasedcollator_str;
    RuleBasedCollatorType_.tp_richcompare =
        (richcmpfunc) t_rulebasedcollator_richcmp;

    INSTALL_CONSTANTS_TYPE(UCollationResult, m);
    INSTALL_CONSTANTS_TYPE(UCollAttribute, m);
    INSTALL_CONSTANTS_TYPE(UCollAttributeValue, m);
    REGISTER_TYPE(CollationKey, m);
    INSTALL_TYPE(Collator, m);
    REGISTER_TYPE(RuleBasedCollator, m);

    INSTALL_ENUM(UCollationResult, "LESS", UCOL_LESS);
    INSTALL_ENUM(UCollationResult, "EQUAL", UCOL_EQUAL);
    INSTALL_ENUM(UCollationResult, "GREATER", UCOL_GREATER);

    INSTALL_ENUM(UCollAttribute, "FRENCH_COLLATION", UCOL_FRENCH_COLLATION);
    INSTALL_ENUM(UCollAttribute, "ALTERNATE_HANDLING", UCOL_ALTERNATE_HANDLING);
    INSTALL_ENUM(UCollAttribute, "CASE_FIRST", UCOL_CASE_FIRST);
    INSTALL_ENUM(UCollAttribute, "CASE_LEVEL", UCOL_CASE_LEVEL);
    INSTALL_ENUM(UCollAttribute, "NORMALIZATION_MODE", UCOL_NORMALIZATION_MODE);
    INSTALL_ENUM(UCollAttribute, "DECOMPOSITION_MODE", UCOL_DECOMPOSITION_MODE);
    INSTALL_ENUM(UCollAttribute, "STRENGTH", UCOL_STRENGTH);
    INSTALL_ENUM(UCollAttribute, "HIRAGANA_QUATERNARY_MODE", UCOL_HIRAGANA_QUATERNARY_MODE);
    INSTALL_ENUM(UCollAttribute, "NUMERIC_COLLATION", UCOL_NUMERIC_COLLATION);

    INSTALL_ENUM(UCollAttributeValue, "DEFAULT", UCOL_DEFAULT);
    INSTALL_ENUM(UCollAttributeValue, "PRIMARY", UCOL_PRIMARY);
    INSTALL_ENUM(UCollAttributeValue, "SECONDARY", UCOL_SECONDARY);
    INSTALL_ENUM(UCollAttributeValue, "TERTIARY", UCOL_TERTIARY);
    INSTALL_ENUM(UCollAttributeValue, "DEFAULT_STRENGTH", UCOL_DEFAULT_STRENGTH);
    INSTALL_ENUM(UCollAttributeValue, "QUATERNARY", UCOL_QUATERNARY);
    INSTALL_ENUM(UCollAttributeValue, "IDENTICAL", UCOL_IDENTICAL);
    INSTALL_ENUM(UCollAttributeValue, "OFF", UCOL_OFF);
    INSTALL_ENUM(UCollAttributeValue, "ON", UCOL_ON);
    INSTALL_ENUM(UCollAttributeValue, "SHIFTED", UCOL_SHIFTED);
    INSTALL_ENUM(UCollAttributeValue, "NON_IGNORABLE", UCOL_NON_IGNORABLE);
    INSTALL_ENUM(UCollAttributeValue, "LOWER_FIRST", UCOL_LOWER_FIRST);
    INSTALL_ENUM(UCollAttributeValue, "UPPER_FIRST", UCOL_UPPER_FIRST);

    INSTALL_ENUM(UCollationResult, "LESS", UCOL_LESS);
    INSTALL_ENUM(UCollationResult, "EQUAL", UCOL_EQUAL);
    INSTALL_ENUM(UCollationResult, "GREATER", UCOL_GREATER);

    INSTALL_STATIC_INT(Collator, PRIMARY);
    INSTALL_STATIC_INT(Collator, SECONDARY);
    INSTALL_STATIC_INT(Collator, TERTIARY);
    INSTALL_STATIC_INT(Collator, QUATERNARY);
    INSTALL_STATIC_INT(Collator, IDENTICAL);

    INSTALL_STATIC_INT(CollationElementIterator, NULLORDER);
}
