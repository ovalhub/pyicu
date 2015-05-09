/* ====================================================================
 * Copyright (c) 2010-2015 Open Source Applications Foundation.
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
#include "unicodeset.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UMatchDegree);
DECLARE_CONSTANTS_TYPE(USetSpanCondition);


/* UnicodeFunctor */

class t_unicodefunctor : public _wrapper {
public:
    UnicodeFunctor *object;
};

static PyObject *t_unicodefunctor_toMatcher(t_unicodefunctor *self);

static PyMethodDef t_unicodefunctor_methods[] = {
    DECLARE_METHOD(t_unicodefunctor, toMatcher, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UnicodeFunctor, t_unicodefunctor, UObject, UnicodeFunctor,
             abstract_init, NULL);


/* UnicodeMatcher */

class t_unicodematcher : public _wrapper {
public:
    UnicodeMatcher *object;
};

static PyObject *t_unicodematcher_matches(t_unicodematcher *self,
                                          PyObject *args);
static PyObject *t_unicodematcher_toPattern(t_unicodematcher *self,
                                            PyObject *args);
static PyObject *t_unicodematcher_matchesIndexValue(t_unicodematcher *self,
                                                    PyObject *arg);
static PyObject *t_unicodematcher_addMatchSetTo(t_unicodematcher *self,
                                                PyObject *arg);

static PyMethodDef t_unicodematcher_methods[] = {
    DECLARE_METHOD(t_unicodematcher, matches, METH_VARARGS),
    DECLARE_METHOD(t_unicodematcher, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_unicodematcher, matchesIndexValue, METH_O),
    DECLARE_METHOD(t_unicodematcher, addMatchSetTo, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UnicodeMatcher, t_unicodematcher, UObject, UnicodeMatcher,
             abstract_init, NULL);


/* UnicodeFilter */

class t_unicodefilter : public _wrapper {
public:
    UnicodeFilter *object;
};

static PyObject *t_unicodefilter_toMatcher(t_unicodefilter *self);
static PyObject *t_unicodefilter_matches(t_unicodefilter *self,
                                         PyObject *args);
static PyObject *t_unicodefilter_toPattern(t_unicodefilter *self,
                                           PyObject *args);
static PyObject *t_unicodefilter_matchesIndexValue(t_unicodefilter *self,
                                                   PyObject *arg);
static PyObject *t_unicodefilter_addMatchSetTo(t_unicodefilter *self,
                                               PyObject *arg);
static PyObject *t_unicodefilter_contains(t_unicodefilter *self, PyObject *arg);

static PyMethodDef t_unicodefilter_methods[] = {
    DECLARE_METHOD(t_unicodefilter, toMatcher, METH_NOARGS),
    DECLARE_METHOD(t_unicodefilter, matches, METH_VARARGS),
    DECLARE_METHOD(t_unicodefilter, toPattern, METH_VARARGS),
    DECLARE_METHOD(t_unicodefilter, matchesIndexValue, METH_O),
    DECLARE_METHOD(t_unicodefilter, addMatchSetTo, METH_O),
    DECLARE_METHOD(t_unicodefilter, contains, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UnicodeFilter, t_unicodefilter, UObject, UnicodeFilter,
             abstract_init, NULL);


/* UnicodeSet */

class t_unicodeset : public _wrapper {
public:
    UnicodeSet *object;
};

static int t_unicodeset_init(t_unicodeset *self,
                             PyObject *args, PyObject *kwds);
#if U_ICU_VERSION_HEX >= 0x04000000
static PyObject *t_unicodeset_isBogus(t_unicodeset *self);
static PyObject *t_unicodeset_setToBogus(t_unicodeset *self);
#endif
static PyObject *t_unicodeset_isEmpty(t_unicodeset *self);
static PyObject *t_unicodeset_isFrozen(t_unicodeset *self);
static PyObject *t_unicodeset_freeze(t_unicodeset *self);
static PyObject *t_unicodeset_set(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_applyPattern(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_applyIntPropertyValue(t_unicodeset *self,
                                                    PyObject *args);
static PyObject *t_unicodeset_applyPropertyAlias(t_unicodeset *self,
                                                 PyObject *args);
static PyObject *t_unicodeset_contains(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_containsAll(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_containsNone(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_containsSome(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_span(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_spanBack(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_add(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_addAll(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_retainAll(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_complementAll(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_removeAll(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_retain(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_remove(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_complement(t_unicodeset *self, PyObject *args);
static PyObject *t_unicodeset_clear(t_unicodeset *self);
static PyObject *t_unicodeset_closeOver(t_unicodeset *self, PyObject *arg);
#if U_ICU_VERSION_HEX >= 0x04020000
static PyObject *t_unicodeset_removeAllStrings(t_unicodeset *self);
#endif
static PyObject *t_unicodeset_compact(t_unicodeset *self);
static PyObject *t_unicodeset_getRangeCount(t_unicodeset *self);
static PyObject *t_unicodeset_getRangeStart(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_getRangeEnd(t_unicodeset *self, PyObject *arg);
static PyObject *t_unicodeset_resemblesPattern(PyTypeObject *type,
                                               PyObject *args);
static PyObject *t_unicodeset_createFrom(PyTypeObject *type, PyObject *arg);
static PyObject *t_unicodeset_createFromAll(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_unicodeset_methods[] = {
#if U_ICU_VERSION_HEX >= 0x04000000
    DECLARE_METHOD(t_unicodeset, isBogus, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, setToBogus, METH_NOARGS),
#endif
    DECLARE_METHOD(t_unicodeset, isEmpty, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, isFrozen, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, freeze, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, set, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, applyPattern, METH_O),
    DECLARE_METHOD(t_unicodeset, applyIntPropertyValue, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, applyPropertyAlias, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, contains, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, containsAll, METH_O),
    DECLARE_METHOD(t_unicodeset, containsNone, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, containsSome, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, span, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, spanBack, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, add, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, addAll, METH_O),
    DECLARE_METHOD(t_unicodeset, retainAll, METH_O),
    DECLARE_METHOD(t_unicodeset, complementAll, METH_O),
    DECLARE_METHOD(t_unicodeset, removeAll, METH_O),
    DECLARE_METHOD(t_unicodeset, retain, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, remove, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, complement, METH_VARARGS),
    DECLARE_METHOD(t_unicodeset, clear, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, closeOver, METH_O),
#if U_ICU_VERSION_HEX >= 0x04020000
    DECLARE_METHOD(t_unicodeset, removeAllStrings, METH_NOARGS),
#endif
    DECLARE_METHOD(t_unicodeset, compact, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, getRangeCount, METH_NOARGS),
    DECLARE_METHOD(t_unicodeset, getRangeStart, METH_O),
    DECLARE_METHOD(t_unicodeset, getRangeEnd, METH_O),
    DECLARE_METHOD(t_unicodeset, resemblesPattern, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_unicodeset, createFrom, METH_O | METH_CLASS),
    DECLARE_METHOD(t_unicodeset, createFromAll, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UnicodeSet, t_unicodeset, UnicodeFilter, UnicodeSet,
             t_unicodeset_init, NULL);


/* UnicodeSetIterator */

class t_unicodesetiterator : public _wrapper {
public:
    UnicodeSetIterator *object;
    PyObject *set;
};

static int t_unicodesetiterator_init(t_unicodesetiterator *self,
                                     PyObject *args, PyObject *kwds);
static PyObject *t_unicodesetiterator_isString(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_getCodepoint(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_getCodepointEnd(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_getString(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_next(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_nextRange(t_unicodesetiterator *self);
static PyObject *t_unicodesetiterator_reset(t_unicodesetiterator *self,
                                            PyObject *args);

static PyMethodDef t_unicodesetiterator_methods[] = {
    DECLARE_METHOD(t_unicodesetiterator, isString, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, getCodepoint, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, getCodepointEnd, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, getString, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, next, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, nextRange, METH_NOARGS),
    DECLARE_METHOD(t_unicodesetiterator, reset, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_unicodesetiterator_dealloc(t_unicodesetiterator *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->set);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(UnicodeSetIterator, t_unicodesetiterator, UObject,
             UnicodeSetIterator, t_unicodesetiterator_init,
             t_unicodesetiterator_dealloc);


/* UnicodeFunctor */

static PyObject *t_unicodefunctor_toMatcher(t_unicodefunctor *self)
{
    return wrap_UnicodeMatcher(self->object->clone()->toMatcher(), T_OWNED);
}


/* UnicodeMatcher */

static PyObject *t_unicodematcher_matches(t_unicodematcher *self,
                                          PyObject *args)
{
    UnicodeString *u, _u;
    int32_t offset, limit, incremental;

    if (!parseArgs(args, "SiiB", &u, &_u, &offset, &limit, &incremental))
    {
        UMatchDegree degree =
            self->object->matches(*(Replaceable const *) u, offset, limit,
                                  (UBool) incremental);

        return Py_BuildValue("(ii)", degree, offset);
    }

    return PyErr_SetArgsError((PyObject *) self, "matches", args);
}

static PyObject *t_unicodematcher_toPattern(t_unicodematcher *self,
                                            PyObject *args)
{
    UnicodeString u;
    int escapeUnprintable = 0;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toPattern(u);
        return PyUnicode_FromUnicodeString(&u);
      case 1:
        if (!parseArgs(args, "B", &escapeUnprintable))
        {
            self->object->toPattern(u, (UBool) escapeUnprintable);
            return PyUnicode_FromUnicodeString(&u);
        }
    }
            
    return PyErr_SetArgsError((PyObject *) self, "toPattern", args);
}

static PyObject *t_unicodematcher_matchesIndexValue(t_unicodematcher *self,
                                                    PyObject *arg)
{
    int v;

    if (!parseArg(arg, "i", &v))
    {
        UBool b = self->object->matchesIndexValue((uint8_t) v);
        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError((PyObject *) self, "matchesIndexValue", arg);
}

static PyObject *t_unicodematcher_addMatchSetTo(t_unicodematcher *self,
                                                PyObject *arg)
{
    UnicodeSet *set;

    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->addMatchSetTo(*set);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "addMatchSetTo", arg);
}


/* UnicodeFilter */

static PyObject *t_unicodefilter_toMatcher(t_unicodefilter *self)
{
    return wrap_UnicodeMatcher(self->object->clone()->toMatcher(), T_OWNED);
}

static PyObject *t_unicodefilter_matches(t_unicodefilter *self,
                                         PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int32_t offset, limit, incremental;

    if (!parseArgs(args, "SiiB", &u, &_u, &offset, &limit, &incremental))
    {
        UMatchDegree degree =
            self->object->matches(*(Replaceable const *) u, offset, limit,
                                  (UBool) incremental);

        return Py_BuildValue("(ii)", degree, offset);
    }

    return PyErr_SetArgsError((PyObject *) self, "matches", args);
}

static PyObject *t_unicodefilter_toPattern(t_unicodefilter *self,
                                           PyObject *args)
{
    UnicodeString *u, _u;
    int escapeUnprintable = 0;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->toPattern(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->toPattern(*u, (UBool) escapeUnprintable);
            Py_RETURN_ARG(args, 0);
        }
        if (!parseArgs(args, "B", &escapeUnprintable))
        {
            self->object->toPattern(_u, (UBool) escapeUnprintable);
            return PyUnicode_FromUnicodeString(&_u);
        }
      case 2:
        if (!parseArgs(args, "UB", &u, &escapeUnprintable))
        {
            self->object->toPattern(*u, (UBool) escapeUnprintable);
            Py_RETURN_ARG(args, 0);
        }
    }
            
    return PyErr_SetArgsError((PyObject *) self, "toPattern", args);
}

static PyObject *t_unicodefilter_matchesIndexValue(t_unicodefilter *self,
                                                   PyObject *arg)
{
    int v;

    if (!parseArg(arg, "i", &v))
    {
        UBool b = self->object->matchesIndexValue((uint8_t) v);
        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError((PyObject *) self, "matchesIndexValue", arg);
}

static PyObject *t_unicodefilter_addMatchSetTo(t_unicodefilter *self,
                                               PyObject *arg)
{
    UnicodeSet *set;

    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->addMatchSetTo(*set);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "addMatchSetTo", arg);
}

static PyObject *t_unicodefilter_contains(t_unicodefilter *self, PyObject *arg)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UChar32 c;
        int32_t len;

        STATUS_CALL(len = toUChar32(*u, &c, status));
        if (len == 1)
        {
            UBool b = self->object->contains(c);
            Py_RETURN_BOOL(b);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "contains", arg);
}


/* UnicodeSet */

static int t_unicodeset_init(t_unicodeset *self,
                             PyObject *args, PyObject *kwds)
{
    UnicodeSet *set;
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new UnicodeSet();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            INT_STATUS_CALL(set = new UnicodeSet(*u0, status));
            self->object = set;
            self->flags = T_OWNED;
            break;
        }
        if (!parseArgs(args, "P", TYPE_CLASSID(UnicodeSet), &set))
        {
            self->object = new UnicodeSet(*set);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            INT_STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            INT_STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                self->object = new UnicodeSet(c0, c1);
                self->flags = T_OWNED;
                break;
            }
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

#if U_ICU_VERSION_HEX >= 0x04000000

static PyObject *t_unicodeset_isBogus(t_unicodeset *self)
{
    UBool b = self->object->isBogus();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodeset_setToBogus(t_unicodeset *self)
{
    self->object->setToBogus();
    Py_RETURN_NONE;
}

#endif

static PyObject *t_unicodeset_isEmpty(t_unicodeset *self)
{
    UBool b = self->object->isEmpty();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodeset_isFrozen(t_unicodeset *self)
{
    UBool b = self->object->isFrozen();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodeset_freeze(t_unicodeset *self)
{
    self->object->freeze();
    Py_RETURN_NONE;
}

static PyObject *t_unicodeset_set(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
    {
        UChar32 c0, c1;
        int32_t l0, l1;

        STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
        STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
        if (l0 == 1 && l1 == 1)
        {
            self->object->set(c0, c1);
            Py_RETURN_SELF();
        }
    }
     
    PyErr_SetArgsError((PyObject *) self, "set", args);
    return NULL;
}

static PyObject *t_unicodeset_add(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UChar32 c0;
            int32_t l0;

            if (u0->length() == 1)
            {
                STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
                if (l0 == 1)
                {
                    self->object->add(c0);
                    Py_RETURN_SELF();
                }
            }
            else
            {
                self->object->add(*u0);
                Py_RETURN_SELF();
            }
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                self->object->add(c0, c1);
                Py_RETURN_SELF();
            }
        }
        break;
    }

    PyErr_SetArgsError((PyObject *) self, "add", args);
    return NULL;
}

static PyObject *t_unicodeset_addAll(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;
    UnicodeSet *set;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->addAll(*u);
        Py_RETURN_SELF();
    }
    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->addAll(*set);
        Py_RETURN_SELF();
    }

    PyErr_SetArgsError((PyObject *) self, "addAll", arg);
    return NULL;
}

static PyObject *t_unicodeset_retain(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UChar32 c0;
            int32_t l0;

            if (u0->length() == 1)
            {
                STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
                if (l0 == 1)
                {
                    self->object->retain(c0);
                    Py_RETURN_SELF();
                }
            }
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                self->object->retain(c0, c1);
                Py_RETURN_SELF();
            }
        }
        break;
    }

    PyErr_SetArgsError((PyObject *) self, "retain", args);
    return NULL;
}

static PyObject *t_unicodeset_retainAll(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;
    UnicodeSet *set;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->retainAll(*u);
        Py_RETURN_SELF();
    }
    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->retainAll(*set);
        Py_RETURN_SELF();
    }


    PyErr_SetArgsError((PyObject *) self, "retainAll", arg);
    return NULL;
}

static PyObject *t_unicodeset_complement(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->complement();
        break;
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UChar32 c0;
            int32_t l0;

            if (u0->length() == 1)
            {
                STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
                if (l0 == 1)
                {
                    self->object->complement(c0);
                    Py_RETURN_SELF();
                }
            }
            else
            {
                self->object->complement(*u0);
                Py_RETURN_SELF();
            }
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                self->object->complement(c0, c1);
                Py_RETURN_SELF();
            }
        }
        break;
    }

    PyErr_SetArgsError((PyObject *) self, "complement", args);
    return NULL;
}

static PyObject *t_unicodeset_complementAll(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;
    UnicodeSet *set;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->complementAll(*u);
        Py_RETURN_SELF();
    }
    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->complementAll(*set);
        Py_RETURN_SELF();
    }

    PyErr_SetArgsError((PyObject *) self, "complementAll", arg);
    return NULL;
}

static PyObject *t_unicodeset_remove(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UChar32 c0;
            int32_t l0;

            if (u0->length() == 1)
            {
                STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
                if (l0 == 1)
                {
                    self->object->remove(c0);
                    Py_RETURN_SELF();
                }
            }
            else
            {
                self->object->remove(*u0);
                Py_RETURN_SELF();
            }
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                self->object->remove(c0, c1);
                Py_RETURN_SELF();
            }
        }
        break;
    }

    PyErr_SetArgsError((PyObject *) self, "remove", args);
    return NULL;
}

static PyObject *t_unicodeset_removeAll(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;
    UnicodeSet *set;

    if (!parseArg(arg, "S", &u, &_u))
    {
        self->object->removeAll(*u);
        Py_RETURN_SELF();
    }
    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        self->object->removeAll(*set);
        Py_RETURN_SELF();
    }


    PyErr_SetArgsError((PyObject *) self, "removeAll", arg);
    return NULL;
}

static PyObject *t_unicodeset_applyPattern(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->applyPattern(*u, status));
        Py_RETURN_SELF();
    }

    PyErr_SetArgsError((PyObject *) self, "applyPattern", arg);
    return NULL;
}

static PyObject *t_unicodeset_applyIntPropertyValue(t_unicodeset *self,
                                                    PyObject *args)
{
    UProperty prop;
    int32_t value;

    if (!parseArgs(args, "ii", &prop, &value))
    {
        STATUS_CALL(self->object->applyIntPropertyValue(prop, value, status));
        Py_RETURN_SELF();
    }

    PyErr_SetArgsError((PyObject *) self, "applyIntPropertyValue", args);
    return NULL;
}

static PyObject *t_unicodeset_applyPropertyAlias(t_unicodeset *self,
                                                 PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
    {
        STATUS_CALL(self->object->applyPropertyAlias(*u0, *u1, status));
        Py_RETURN_SELF();
    }

    PyErr_SetArgsError((PyObject *) self, "applyPropertyAlias", args);
    return NULL;
}

static PyObject *t_unicodeset_contains(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UChar32 c0;
            int32_t l0;

            if (u0->length() == 1)
            {
                STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
                if (l0 == 1)
                {
                    UBool b = self->object->contains(c0);
                    Py_RETURN_BOOL(b);
                }
            }
            else
            {
                UBool b = self->object->contains(*u0);
                Py_RETURN_BOOL(b);
            }
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                UBool b = self->object->contains(c0, c1);
                Py_RETURN_BOOL(b);
            }
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "contains", args);
}

static PyObject *t_unicodeset_containsAll(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;
    UnicodeSet *set;
    UBool b;

    if (!parseArg(arg, "S", &u, &_u))
        b = self->object->containsAll(*u);
    else if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
        b = self->object->containsAll(*set);
    else
        return PyErr_SetArgsError((PyObject *) self, "containsAll", arg);

    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodeset_containsNone(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;
    UnicodeSet *set;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UBool b = self->object->containsNone(*u0);
            Py_RETURN_BOOL(b);
        }
        if (!parseArgs(args, "P", TYPE_CLASSID(UnicodeSet), &set))
        {
            UBool b = self->object->containsNone(*u0);
            Py_RETURN_BOOL(b);
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                UBool b = self->object->containsNone(c0, c1);
                Py_RETURN_BOOL(b);
            }
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "containsNone", args);
}

static PyObject *t_unicodeset_containsSome(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u0, *u1;
    UnicodeString _u0, _u1;
    UnicodeSet *set;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            UBool b = self->object->containsSome(*u0);
            Py_RETURN_BOOL(b);
        }
        if (!parseArgs(args, "P", TYPE_CLASSID(UnicodeSet), &set))
        {
            UBool b = self->object->containsSome(*u0);
            Py_RETURN_BOOL(b);
        }
        break;
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            UChar32 c0, c1;
            int32_t l0, l1;

            STATUS_CALL(l0 = toUChar32(*u0, &c0, status));
            STATUS_CALL(l1 = toUChar32(*u1, &c1, status));
            if (l0 == 1 && l1 == 1)
            {
                UBool b = self->object->containsSome(c0, c1);
                Py_RETURN_BOOL(b);
            }
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "containsSome", args);
}

static PyObject *t_unicodeset_span(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u, _u;
    USetSpanCondition spanCondition;
    int32_t length;

    if (!parseArgs(args, "Si", &u, &_u, &spanCondition))
    {
        length = self->object->span(u->getBuffer(), u->length(), spanCondition);
        return PyInt_FromLong(length);
    }

    return PyErr_SetArgsError((PyObject *) self, "span", args);
}

static PyObject *t_unicodeset_spanBack(t_unicodeset *self, PyObject *args)
{
    UnicodeString *u, _u;
    USetSpanCondition spanCondition;
    int length;

    if (!parseArgs(args, "Si", &u, &_u, &spanCondition))
    {
        length = self->object->spanBack(u->getBuffer(), u->length(),
                                        spanCondition);
        return PyInt_FromLong(length);
    }

    return PyErr_SetArgsError((PyObject *) self, "spanBack", args);
}

static PyObject *t_unicodeset_clear(t_unicodeset *self)
{
    self->object->clear();
    Py_RETURN_SELF();
}

#if U_ICU_VERSION_HEX >= 0x04020000

static PyObject *t_unicodeset_removeAllStrings(t_unicodeset *self)
{
    self->object->removeAllStrings();
    Py_RETURN_SELF();
}

#endif

static PyObject *t_unicodeset_closeOver(t_unicodeset *self, PyObject *arg)
{
    int32_t attribute;

    if (!parseArg(arg, "i", &attribute))
    {
        self->object->closeOver(attribute);
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "closeOver", arg);
}

static PyObject *t_unicodeset_compact(t_unicodeset *self)
{
    self->object->compact();
    Py_RETURN_SELF();
}

static PyObject *t_unicodeset_getRangeCount(t_unicodeset *self)
{
    int32_t count = self->object->getRangeCount();
    return PyInt_FromLong(count);
}

static PyObject *t_unicodeset_getRangeStart(t_unicodeset *self, PyObject *arg)
{
    int32_t index;

    if (!parseArg(arg, "i", &index))
    {
        UnicodeString u = UnicodeString(self->object->getRangeStart(index));
        return PyUnicode_FromUnicodeString(&u);
    }

    return PyErr_SetArgsError((PyObject *) self, "getRangeStart", arg);
}

static PyObject *t_unicodeset_getRangeEnd(t_unicodeset *self, PyObject *arg)
{
    int32_t index;

    if (!parseArg(arg, "i", &index))
    {
        UnicodeString u = UnicodeString(self->object->getRangeEnd(index));
        return PyUnicode_FromUnicodeString(&u);
    }

    return PyErr_SetArgsError((PyObject *) self, "getRangeEnd", arg);
}

static PyObject *t_unicodeset_resemblesPattern(PyTypeObject *type,
                                               PyObject *args)
{
    UnicodeString *u, _u;
    int32_t pos;

    if (!parseArgs(args, "Si", &u, &_u, &pos))
    {
        UBool b = UnicodeSet::resemblesPattern(*u, pos);
        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError(type, "resemblesPattern", args);
}

static PyObject *t_unicodeset_createFrom(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
        return wrap_UnicodeSet(UnicodeSet::createFrom(*u), T_OWNED);

    return PyErr_SetArgsError(type, "createFrom", arg);
}

static PyObject *t_unicodeset_createFromAll(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
        return wrap_UnicodeSet(UnicodeSet::createFromAll(*u), T_OWNED);

    return PyErr_SetArgsError(type, "createFromAll", arg);
}


static PyObject *t_unicodeset_str(t_unicodeset *self)
{
    UnicodeString u;

    self->object->toPattern(u);
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_unicodeset_richcmp(t_unicodeset *self, PyObject *arg, int op)
{
    UnicodeSet *set;
    int b = 0;

    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *set;
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

static PyObject *t_unicodeset_iter(t_unicodeset *self)
{
    return PyObject_CallFunctionObjArgs((PyObject *) &UnicodeSetIteratorType_,
                                        (PyObject *) self, NULL);
}

static long t_unicodeset_hash(t_unicodeset *self)
{
  return (long) self->object->hashCode();
}


static Py_ssize_t _t_unicodeset_length(t_unicodeset *self)
{
    return self->object->size();
}

static int _t_unicodeset_contains(t_unicodeset *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UChar32 c;
        int32_t l;

        if (u->length() == 1)
        {
            INT_STATUS_CALL(l = toUChar32(*u, &c, status));
            if (l == 1)
                return self->object->contains(c);
        }
        else
            return self->object->contains(*u);
    }

    PyErr_SetArgsError((PyObject *) self, "in", arg);
    return -1;
}

static PyObject *_t_unicodeset_item(t_unicodeset *self, int n)
{
    int len = self->object->size();

    if (n < 0)
        n += len;

    if (n >= 0 && n < len)
    {
        UnicodeString u = UnicodeString(self->object->charAt(n));
        return PyUnicode_FromUnicodeString(&u);
    }

    PyErr_SetNone(PyExc_IndexError);
    return NULL;
}

static PySequenceMethods t_unicodeset_as_sequence = {
    (lenfunc) _t_unicodeset_length,              /* sq_length */
    NULL,                                        /* sq_concat */
    NULL,                                        /* sq_repeat */
    (ssizeargfunc) _t_unicodeset_item,           /* sq_item */
    NULL,                                        /* sq_slice */
    NULL,                                        /* sq_ass_item */
    NULL,                                        /* sq_ass_slice */
    (objobjproc) _t_unicodeset_contains,         /* sq_contains */
    NULL,                                        /* sq_inplace_concat */
    NULL,                                        /* sq_inplace_repeat */
};


/* UnicodeSetIterator */

static int t_unicodesetiterator_init(t_unicodesetiterator *self,
                                     PyObject *args, PyObject *kwds)
{
    UnicodeSet *set;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new UnicodeSetIterator();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "p", TYPE_CLASSID(UnicodeSet), &set, &self->set))
        {
            self->object = new UnicodeSetIterator(*set);
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

static PyObject *t_unicodesetiterator_isString(t_unicodesetiterator *self)
{
    UBool b = self->object->isString();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodesetiterator_getCodepoint(t_unicodesetiterator *self)
{
    UChar32 c = self->object->getCodepoint();
    UnicodeString u = fromUChar32(c);

    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_unicodesetiterator_getCodepointEnd(t_unicodesetiterator *self)
{
    UChar32 c = self->object->getCodepointEnd();
    UnicodeString u = fromUChar32(c);

    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_unicodesetiterator_getString(t_unicodesetiterator *self)
{
    UnicodeString u = self->object->getString();
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_unicodesetiterator_next(t_unicodesetiterator *self)
{
    UBool b = self->object->next();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodesetiterator_nextRange(t_unicodesetiterator *self)
{
    UBool b = self->object->nextRange();
    Py_RETURN_BOOL(b);
}

static PyObject *t_unicodesetiterator_reset(t_unicodesetiterator *self,
                                            PyObject *args)
{
    UnicodeSet *set;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->reset();
        Py_RETURN_NONE;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(UnicodeSet), &set))
        {
            PyObject *setObject = PyTuple_GetItem(args, 0);

            Py_INCREF(setObject); Py_XDECREF(self->set); self->set = setObject;
            self->object->reset(*set);

            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "reset", args);
}

static PyObject *t_unicodesetiterator_iter(t_unicodesetiterator *self)
{
    Py_RETURN_SELF();
}

static PyObject *t_unicodesetiterator_iter_next(t_unicodesetiterator *self)
{
    if (!self->object->next())
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return t_unicodesetiterator_getString(self);
}


void _init_unicodeset(PyObject *m)
{
    UnicodeSetType_.tp_str = (reprfunc) t_unicodeset_str;
    UnicodeSetType_.tp_richcompare = (richcmpfunc) t_unicodeset_richcmp;
    UnicodeSetType_.tp_hash = (hashfunc) t_unicodeset_hash;
    UnicodeSetType_.tp_iter = (getiterfunc) t_unicodeset_iter;
    UnicodeSetType_.tp_as_sequence = &t_unicodeset_as_sequence;
    UnicodeSetIteratorType_.tp_iter =
        (getiterfunc) t_unicodesetiterator_iter;
    UnicodeSetIteratorType_.tp_iternext =
        (iternextfunc) t_unicodesetiterator_iter_next;

    INSTALL_CONSTANTS_TYPE(UMatchDegree, m);
    INSTALL_CONSTANTS_TYPE(USetSpanCondition, m);

    REGISTER_TYPE(UnicodeFunctor, m);
    INSTALL_TYPE(UnicodeMatcher, m);
    REGISTER_TYPE(UnicodeFilter, m);
    REGISTER_TYPE(UnicodeSet, m);
    REGISTER_TYPE(UnicodeSetIterator, m);

    INSTALL_ENUM(UMatchDegree, "MISMATCH", U_MISMATCH);
    INSTALL_ENUM(UMatchDegree, "PARTIAL_MATCH", U_PARTIAL_MATCH);
    INSTALL_ENUM(UMatchDegree, "MATCH", U_MATCH);

    INSTALL_ENUM(USetSpanCondition, "SPAN_NOT_CONTAINED", USET_SPAN_NOT_CONTAINED);
    INSTALL_ENUM(USetSpanCondition, "SPAN_CONTAINED", USET_SPAN_CONTAINED);
    INSTALL_ENUM(USetSpanCondition, "SPAN_SIMPLE", USET_SPAN_SIMPLE);
}
