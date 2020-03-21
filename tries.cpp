/* ====================================================================
 * Copyright (c) 2019 Open Source Applications Foundation.
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
#include "tries.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= 0x04080000

using BytesTrieIterator = BytesTrie::Iterator;
using BytesTrieState = BytesTrie::State;
using UCharsTrieIterator = UCharsTrie::Iterator;
using UCharsTrieState = UCharsTrie::State;

DECLARE_CONSTANTS_TYPE(UStringTrieBuildOption)
DECLARE_CONSTANTS_TYPE(UStringTrieResult)

/* StringTrieBuilder */

class t_stringtriebuilder : public _wrapper {
public:
    StringTrieBuilder *object;
};

static PyMethodDef t_stringtriebuilder_methods[] = {
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(StringTrieBuilder, t_stringtriebuilder, UObject,
             StringTrieBuilder, abstract_init, NULL)

/* BytesTrieBuilder */

class t_bytestriebuilder : public _wrapper {
public:
    BytesTrieBuilder *object;
};

static int t_bytestriebuilder_init(
    t_bytestriebuilder *self, PyObject *args, PyObject *kwds);
static PyObject *t_bytestriebuilder_add(
    t_bytestriebuilder *self, PyObject *args);
static PyObject *t_bytestriebuilder_clear(t_bytestriebuilder *self);
static PyObject *t_bytestriebuilder_build(
    t_bytestriebuilder *self, PyObject *arg);

static PyMethodDef t_bytestriebuilder_methods[] = {
    DECLARE_METHOD(t_bytestriebuilder, add, METH_VARARGS),
    DECLARE_METHOD(t_bytestriebuilder, clear, METH_NOARGS),
    DECLARE_METHOD(t_bytestriebuilder, build, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(BytesTrieBuilder, t_bytestriebuilder, StringTrieBuilder,
             BytesTrieBuilder, t_bytestriebuilder_init, NULL)

/* BytesTrieIterator */

class t_bytestrieiterator : public _wrapper {
public:
    BytesTrieIterator *object;
};

int t_bytestrieiterator_init(
    t_bytestrieiterator *self, PyObject *args, PyObject *kwds);
static PyObject *t_bytestrieiterator_reset(t_bytestrieiterator *self);
static PyObject *t_bytestrieiterator_hasNext(t_bytestrieiterator *self);
static PyObject *t_bytestrieiterator_next(t_bytestrieiterator *self);
static PyObject *t_bytestrieiterator_getString(t_bytestrieiterator *self);
static PyObject *t_bytestrieiterator_getValue(t_bytestrieiterator *self);

static PyMethodDef t_bytestrieiterator_methods[] = {
    DECLARE_METHOD(t_bytestrieiterator, reset, METH_NOARGS),
    DECLARE_METHOD(t_bytestrieiterator, hasNext, METH_NOARGS),
    DECLARE_METHOD(t_bytestrieiterator, next, METH_NOARGS),
    DECLARE_METHOD(t_bytestrieiterator, getString, METH_NOARGS),
    DECLARE_METHOD(t_bytestrieiterator, getValue, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(BytesTrieIterator, t_bytestrieiterator, UMemory,
             BytesTrieIterator, t_bytestrieiterator_init, NULL)

/* BytesTrieState */

class t_bytestriestate : public _wrapper {
public:
    BytesTrieState *object;
};

static PyMethodDef t_bytestriestate_methods[] = {
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(BytesTrieState, t_bytestriestate, UMemory,
             BytesTrieState, abstract_init, NULL)

/* BytesTrie */

class t_bytestrie : public _wrapper {
public:
    BytesTrie *object;
};

static PyObject *t_bytestrie_reset(t_bytestrie *self);
static PyObject *t_bytestrie_saveState(t_bytestrie *self);
static PyObject *t_bytestrie_resetToState(t_bytestrie *self, PyObject *arg);
static PyObject *t_bytestrie_current(t_bytestrie *self);
static PyObject *t_bytestrie_first(t_bytestrie *self, PyObject *arg);
static PyObject *t_bytestrie_next(t_bytestrie *self, PyObject *arg);
static PyObject *t_bytestrie_hasUniqueValue(t_bytestrie *self);
static PyObject *t_bytestrie_getNextBytes(t_bytestrie *self);
static PyObject *t_bytestrie_getValue(t_bytestrie *self);

static PyMethodDef t_bytestrie_methods[] = {
    DECLARE_METHOD(t_bytestrie, reset, METH_NOARGS),
    DECLARE_METHOD(t_bytestrie, saveState, METH_NOARGS),
    DECLARE_METHOD(t_bytestrie, resetToState, METH_O),
    DECLARE_METHOD(t_bytestrie, current, METH_NOARGS),
    DECLARE_METHOD(t_bytestrie, first, METH_O),
    DECLARE_METHOD(t_bytestrie, next, METH_O),
    DECLARE_METHOD(t_bytestrie, hasUniqueValue, METH_NOARGS),
    DECLARE_METHOD(t_bytestrie, getNextBytes, METH_NOARGS),
    DECLARE_METHOD(t_bytestrie, getValue, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(BytesTrie, t_bytestrie, UMemory, BytesTrie, abstract_init, NULL)

/* UCharsTrieBuilder */

class t_ucharstriebuilder : public _wrapper {
public:
    UCharsTrieBuilder *object;
};

static int t_ucharstriebuilder_init(
    t_ucharstriebuilder *self, PyObject *args, PyObject *kwds);
static PyObject *t_ucharstriebuilder_add(
    t_ucharstriebuilder *self, PyObject *args);
static PyObject *t_ucharstriebuilder_clear(t_ucharstriebuilder *self);
static PyObject *t_ucharstriebuilder_build(
    t_ucharstriebuilder *self, PyObject *arg);

static PyMethodDef t_ucharstriebuilder_methods[] = {
    DECLARE_METHOD(t_ucharstriebuilder, add, METH_VARARGS),
    DECLARE_METHOD(t_ucharstriebuilder, clear, METH_NOARGS),
    DECLARE_METHOD(t_ucharstriebuilder, build, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UCharsTrieBuilder, t_ucharstriebuilder, StringTrieBuilder,
             UCharsTrieBuilder, t_ucharstriebuilder_init, NULL)

/* UCharsTrieIterator */

class t_ucharstrieiterator : public _wrapper {
public:
    UCharsTrieIterator *object;
};

int t_ucharstrieiterator_init(
    t_ucharstrieiterator *self, PyObject *args, PyObject *kwds);
static PyObject *t_ucharstrieiterator_reset(t_ucharstrieiterator *self);
static PyObject *t_ucharstrieiterator_hasNext(t_ucharstrieiterator *self);
static PyObject *t_ucharstrieiterator_next(t_ucharstrieiterator *self);
static PyObject *t_ucharstrieiterator_getString(t_ucharstrieiterator *self);
static PyObject *t_ucharstrieiterator_getValue(t_ucharstrieiterator *self);

static PyMethodDef t_ucharstrieiterator_methods[] = {
    DECLARE_METHOD(t_ucharstrieiterator, reset, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrieiterator, hasNext, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrieiterator, next, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrieiterator, getString, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrieiterator, getValue, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UCharsTrieIterator, t_ucharstrieiterator, UMemory,
             UCharsTrieIterator, t_ucharstrieiterator_init, NULL)

/* UCharsTrieState */

class t_ucharstriestate : public _wrapper {
public:
    UCharsTrieState *object;
};

static PyMethodDef t_ucharstriestate_methods[] = {
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UCharsTrieState, t_ucharstriestate, UMemory,
             UCharsTrieState, abstract_init, NULL)

/* UCharsTrie */

class t_ucharstrie : public _wrapper {
public:
    UCharsTrie *object;
};

static PyObject *t_ucharstrie_reset(t_ucharstrie *self);
static PyObject *t_ucharstrie_saveState(t_ucharstrie *self);
static PyObject *t_ucharstrie_resetToState(t_ucharstrie *self, PyObject *arg);
static PyObject *t_ucharstrie_current(t_ucharstrie *self);
static PyObject *t_ucharstrie_first(t_ucharstrie *self, PyObject *arg);
static PyObject *t_ucharstrie_firstForCodePoint(t_ucharstrie *self, PyObject *arg);
static PyObject *t_ucharstrie_next(t_ucharstrie *self, PyObject *arg);
static PyObject *t_ucharstrie_nextForCodePoint(t_ucharstrie *self, PyObject *arg);
static PyObject *t_ucharstrie_hasUniqueValue(t_ucharstrie *self);
static PyObject *t_ucharstrie_getNextUChars(t_ucharstrie *self);
static PyObject *t_ucharstrie_getValue(t_ucharstrie *self);

static PyMethodDef t_ucharstrie_methods[] = {
    DECLARE_METHOD(t_ucharstrie, reset, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrie, saveState, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrie, resetToState, METH_O),
    DECLARE_METHOD(t_ucharstrie, current, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrie, first, METH_O),
    DECLARE_METHOD(t_ucharstrie, firstForCodePoint, METH_O),
    DECLARE_METHOD(t_ucharstrie, next, METH_O),
    DECLARE_METHOD(t_ucharstrie, nextForCodePoint, METH_O),
    DECLARE_METHOD(t_ucharstrie, hasUniqueValue, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrie, getNextUChars, METH_NOARGS),
    DECLARE_METHOD(t_ucharstrie, getValue, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(UCharsTrie, t_ucharstrie, UMemory,
             UCharsTrie, abstract_init, NULL)

/* BytesTrieBuilder */

static int t_bytestriebuilder_init(t_bytestriebuilder *self, PyObject *args,
                                   PyObject *kwds)
{
    BytesTrieBuilder *builder;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(builder = new BytesTrieBuilder(status));
        self->object = builder;
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

static PyObject *t_bytestriebuilder_add(
    t_bytestriebuilder *self, PyObject *args)
{
    charsArg key;
    int value;

    if (!parseArgs(args, "ni", &key, &value))
    {
        STATUS_CALL(self->object->add(key.c_str(), value, status));
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "add", args);
}

static PyObject *t_bytestriebuilder_clear(t_bytestriebuilder *self)
{
    self->object->clear();
    Py_RETURN_SELF();
}

static PyObject *t_bytestriebuilder_build(
    t_bytestriebuilder *self, PyObject *arg)
{
    int option;

    if (!parseArg(arg, "i", &option))
    {
        BytesTrie *trie;

        STATUS_CALL(trie = self->object->build(
            (UStringTrieBuildOption) option, status));
        self->object->clear();  // builder data is now owned by trie

        return wrap_BytesTrie(trie, T_OWNED);
    }

    return PyErr_SetArgsError((PyObject *) self, "build", arg);
}


/* BytesTrie */

static PyObject *t_bytestrie_reset(t_bytestrie *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_bytestrie_saveState(t_bytestrie *self)
{
    BytesTrieState state;
    self->object->saveState(state);

    return wrap_BytesTrieState(new BytesTrieState(state), T_OWNED);
}

static PyObject *t_bytestrie_resetToState(t_bytestrie *self, PyObject *arg)
{
    PyObject *state;

    if (!parseArg(arg, "O", &BytesTrieStateType_, &state))
    {
        self->object->resetToState(*((t_bytestriestate *) state)->object);
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "resetToState", arg);
}

static PyObject *t_bytestrie_iter(t_bytestrie *self)
{
    BytesTrieIterator *iter;
    STATUS_CALL(iter = new BytesTrieIterator(*self->object, 0, status));

    return wrap_BytesTrieIterator(iter, T_OWNED);
}

static PyObject *t_bytestrie_current(t_bytestrie *self)
{
    return PyInt_FromLong(self->object->current());
}

static PyObject *t_bytestrie_first(t_bytestrie *self, PyObject *arg)
{
    int b;
    charsArg s;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->first(b));

    if (!parseArg(arg, "n", &s) && s.size() == 1)
        return PyInt_FromLong(self->object->first(s.c_str()[0]));

    return PyErr_SetArgsError((PyObject *) self, "first", arg);
}

static PyObject *t_bytestrie_next(t_bytestrie *self, PyObject *arg)
{
    int b;
    charsArg s;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->next(b));

    if (!parseArg(arg, "n", &s))
        return PyInt_FromLong(self->object->next(s.c_str(), s.size()));

    return PyErr_SetArgsError((PyObject *) self, "next", arg);
}

static PyObject *t_bytestrie_hasUniqueValue(t_bytestrie *self)
{
    int result;

    if (self->object->hasUniqueValue(result))
        return PyInt_FromLong(result);

    Py_RETURN_NONE;
}

static PyObject *t_bytestrie_getNextBytes(t_bytestrie *self)
{
    struct sink {
        PyObject *bytes = PyBytes_FromStringAndSize("", 0);
        void append(const char *data, int32_t n)
        {
            PyBytes_ConcatAndDel(&bytes, PyBytes_FromStringAndSize(data, n));
        }
    } buffer;
    StringByteSink<struct sink> sbs(&buffer);

    self->object->getNextBytes(sbs);

    return buffer.bytes;
}

static PyObject *t_bytestrie_getValue(t_bytestrie *self)
{
    if (USTRINGTRIE_HAS_VALUE(self->object->current()))
        return PyInt_FromLong(self->object->getValue());

    Py_RETURN_NONE;
}


/* BytesTrieIterator */

int t_bytestrieiterator_init(t_bytestrieiterator *self,
                             PyObject *args, PyObject *kwds)
{
    BytesTrieIterator *iterator;
    PyObject *trie;
    int len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "O", &BytesTrieType_, &trie))
        {
            INT_STATUS_CALL(iterator = new BytesTrieIterator(
                *((t_bytestrie *) trie)->object, 0, status));
            self->object = iterator;
            self->flags = T_OWNED;
        }
        else
            PyErr_SetArgsError((PyObject *) self, "__init__", args);
        break;

      case 2:
        if (!parseArgs(args, "Oi", &BytesTrieType_, &trie, &len))
        {
            INT_STATUS_CALL(iterator = new BytesTrieIterator(
                *((t_bytestrie *) trie)->object, len, status));
            self->object = iterator;
            self->flags = T_OWNED;
        }
        else
            PyErr_SetArgsError((PyObject *) self, "__init__", args);
        break;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_bytestrieiterator_reset(t_bytestrieiterator *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_bytestrieiterator_hasNext(t_bytestrieiterator *self)
{
    if (self->object->hasNext())
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_bytestrieiterator_next(t_bytestrieiterator *self)
{
    UBool result;
    STATUS_CALL(result = self->object->next(status));

    Py_RETURN_BOOL(result);
}

static PyObject *t_bytestrieiterator_getString(t_bytestrieiterator *self)
{
    StringPiece key = self->object->getString();
    return PyString_FromStringAndSize(key.data(), key.size());
}

static PyObject *t_bytestrieiterator_getValue(t_bytestrieiterator *self)
{
    return PyInt_FromLong(self->object->getValue());
}

static PyObject *t_bytestrieiterator_iter(t_bytestrieiterator *self)
{
    Py_RETURN_SELF();
}

static PyObject *t_bytestrieiterator_iter_next(t_bytestrieiterator *self)
{
    UBool found;

    STATUS_CALL(found = self->object->next(status));

    if (!found)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    PyObject *result = PyTuple_New(2);
    StringPiece key = self->object->getString();

    PyTuple_SET_ITEM(result, 0, PyString_FromStringAndSize(
        key.data(), key.size()));
    PyTuple_SET_ITEM(result, 1, PyInt_FromLong(self->object->getValue()));

    return result;
}


/* UCharsTrieBuilder */

static int t_ucharstriebuilder_init(t_ucharstriebuilder *self, PyObject *args,
                                    PyObject *kwds)
{
    UCharsTrieBuilder *builder;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(builder = new UCharsTrieBuilder(status));
        self->object = builder;
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

static PyObject *t_ucharstriebuilder_add(
    t_ucharstriebuilder *self, PyObject *args)
{
    UnicodeString *u, _u;
    int value;

    if (!parseArgs(args, "Si", &u, &_u, &value))
    {
        STATUS_CALL(self->object->add(*u, value, status));
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "add", args);
}

static PyObject *t_ucharstriebuilder_clear(t_ucharstriebuilder *self)
{
    self->object->clear();
    Py_RETURN_SELF();
}

static PyObject *t_ucharstriebuilder_build(
    t_ucharstriebuilder *self, PyObject *arg)
{
    int option;

    if (!parseArg(arg, "i", &option))
    {
        UCharsTrie *trie;

        STATUS_CALL(trie = self->object->build(
            (UStringTrieBuildOption) option, status));
        self->object->clear();  // builder data is now owned by trie

        return wrap_UCharsTrie(trie, T_OWNED);
    }

    return PyErr_SetArgsError((PyObject *) self, "build", arg);
}

/* UCharsTrie */

static PyObject *t_ucharstrie_reset(t_ucharstrie *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_ucharstrie_saveState(t_ucharstrie *self)
{
    UCharsTrieState state;
    self->object->saveState(state);

    return wrap_UCharsTrieState(new UCharsTrieState(state), T_OWNED);
}

static PyObject *t_ucharstrie_resetToState(t_ucharstrie *self, PyObject *arg)
{
    PyObject *state;

    if (!parseArg(arg, "O", &UCharsTrieStateType_, &state))
    {
        self->object->resetToState(*((t_ucharstriestate *) state)->object);
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "resetToState", arg);
}

static PyObject *t_ucharstrie_iter(t_ucharstrie *self)
{
    UCharsTrieIterator *iter;
    STATUS_CALL(iter = new UCharsTrieIterator(*self->object, 0, status));

    return wrap_UCharsTrieIterator(iter, T_OWNED);
}

static PyObject *t_ucharstrie_current(t_ucharstrie *self)
{
    return PyInt_FromLong(self->object->current());
}

static PyObject *t_ucharstrie_first(t_ucharstrie *self, PyObject *arg)
{
    int b;
    UnicodeString *u, _u;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->first(b));

    if (!parseArg(arg, "S", &u, &_u) && u->length() == 1)
        return PyInt_FromLong(self->object->first(u->charAt(0)));

    return PyErr_SetArgsError((PyObject *) self, "first", arg);
}

static PyObject *t_ucharstrie_firstForCodePoint(
    t_ucharstrie *self, PyObject *arg)
{
    int b;
    UnicodeString *u, _u;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->firstForCodePoint(b));

    if (!parseArg(arg, "S", &u, &_u) && u->countChar32() == 1)
        return PyInt_FromLong(self->object->firstForCodePoint(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) self, "firstForCodePoint", arg);
}

static PyObject *t_ucharstrie_next(t_ucharstrie *self, PyObject *arg)
{
    int b;
    UnicodeString *u, _u;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->next(b));

    if (!parseArg(arg, "S", &u, &_u))
        return PyInt_FromLong(self->object->next(u->getBuffer(), u->length()));

    return PyErr_SetArgsError((PyObject *) self, "next", arg);
}

static PyObject *t_ucharstrie_nextForCodePoint(
    t_ucharstrie *self, PyObject *arg)
{
    int b;
    UnicodeString *u, _u;

    if (!parseArg(arg, "i", &b))
        return PyInt_FromLong(self->object->nextForCodePoint(b));

    if (!parseArg(arg, "S", &u, &_u) && u->countChar32() == 1)
        return PyInt_FromLong(self->object->next(u->char32At(0)));

    return PyErr_SetArgsError((PyObject *) self, "nextForCodePoint", arg);
}

static PyObject *t_ucharstrie_hasUniqueValue(t_ucharstrie *self)
{
    int result;

    if (self->object->hasUniqueValue(result))
        return PyInt_FromLong(result);

    Py_RETURN_NONE;
}

static PyObject *t_ucharstrie_getNextUChars(t_ucharstrie *self)
{
    UnicodeString u;
    UnicodeStringAppendable a(u);

    self->object->getNextUChars(a);

    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_ucharstrie_getValue(t_ucharstrie *self)
{
    if (USTRINGTRIE_HAS_VALUE(self->object->current()))
        return PyInt_FromLong(self->object->getValue());

    Py_RETURN_NONE;
}

/* UCharsTrieIterator */

int t_ucharstrieiterator_init(t_ucharstrieiterator *self,
                              PyObject *args, PyObject *kwds)
{
    UCharsTrieIterator *iterator;
    PyObject *trie;
    int len;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "O", &UCharsTrieType_, &trie))
        {
            INT_STATUS_CALL(iterator = new UCharsTrieIterator(
                *((t_ucharstrie *) trie)->object, 0, status));
            self->object = iterator;
            self->flags = T_OWNED;
        }
        else
            PyErr_SetArgsError((PyObject *) self, "__init__", args);
        break;

      case 2:
        if (!parseArgs(args, "Oi", &UCharsTrieType_, &trie, &len))
        {
            INT_STATUS_CALL(iterator = new UCharsTrieIterator(
                *((t_ucharstrie *) trie)->object, len, status));
            self->object = iterator;
            self->flags = T_OWNED;
        }
        else
            PyErr_SetArgsError((PyObject *) self, "__init__", args);
        break;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_ucharstrieiterator_reset(t_ucharstrieiterator *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_ucharstrieiterator_hasNext(t_ucharstrieiterator *self)
{
    if (self->object->hasNext())
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_ucharstrieiterator_next(t_ucharstrieiterator *self)
{
    UBool result;
    STATUS_CALL(result = self->object->next(status));

    Py_RETURN_BOOL(result);
}

static PyObject *t_ucharstrieiterator_getString(t_ucharstrieiterator *self)
{
    const UnicodeString &u = self->object->getString();

    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_ucharstrieiterator_getValue(t_ucharstrieiterator *self)
{
    return PyInt_FromLong(self->object->getValue());
}

static PyObject *t_ucharstrieiterator_iter(t_ucharstrieiterator *self)
{
    Py_RETURN_SELF();
}

static PyObject *t_ucharstrieiterator_iter_next(t_ucharstrieiterator *self)
{
    UBool found;

    STATUS_CALL(found = self->object->next(status));

    if (!found)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    PyObject *result = PyTuple_New(2);
    const UnicodeString &u = self->object->getString();

    PyTuple_SET_ITEM(result, 0, PyUnicode_FromUnicodeString(&u));
    PyTuple_SET_ITEM(result, 1, PyInt_FromLong(self->object->getValue()));

    return result;
}

#endif

void _init_tries(PyObject *m)
{
#if U_ICU_VERSION_HEX >= 0x04080000
    BytesTrieType_.tp_iter = (getiterfunc) t_bytestrie_iter;
    BytesTrieIteratorType_.tp_iter = (getiterfunc) t_bytestrieiterator_iter;
    BytesTrieIteratorType_.tp_iternext =
        (iternextfunc) t_bytestrieiterator_iter_next;
    UCharsTrieType_.tp_iter = (getiterfunc) t_ucharstrie_iter;
    UCharsTrieIteratorType_.tp_iter = (getiterfunc) t_ucharstrieiterator_iter;
    UCharsTrieIteratorType_.tp_iternext =
        (iternextfunc) t_ucharstrieiterator_iter_next;

    INSTALL_CONSTANTS_TYPE(UStringTrieBuildOption, m);
    INSTALL_CONSTANTS_TYPE(UStringTrieResult, m);
    REGISTER_TYPE(StringTrieBuilder, m);
    REGISTER_TYPE(BytesTrieBuilder, m);
    INSTALL_STRUCT(BytesTrieIterator, m);
    INSTALL_STRUCT(BytesTrieState, m);
    INSTALL_STRUCT(BytesTrie, m);
    REGISTER_TYPE(UCharsTrieBuilder, m);
    INSTALL_STRUCT(UCharsTrieIterator, m);
    INSTALL_STRUCT(UCharsTrieState, m);
    INSTALL_STRUCT(UCharsTrie, m);

    PyDict_SetItemString(BytesTrieType_.tp_dict, "Builder",
                         (PyObject *) &BytesTrieBuilderType_);
    PyDict_SetItemString(BytesTrieType_.tp_dict, "Iterator",
                         (PyObject *) &BytesTrieIteratorType_);
    PyDict_SetItemString(BytesTrieType_.tp_dict, "State",
                         (PyObject *) &BytesTrieStateType_);
    PyDict_SetItemString(UCharsTrieType_.tp_dict, "Builder",
                         (PyObject *) &UCharsTrieBuilderType_);
    PyDict_SetItemString(UCharsTrieType_.tp_dict, "Iterator",
                         (PyObject *) &UCharsTrieIteratorType_);
    PyDict_SetItemString(UCharsTrieType_.tp_dict, "State",
                         (PyObject *) &UCharsTrieStateType_);

    INSTALL_ENUM(UStringTrieBuildOption, "FAST", USTRINGTRIE_BUILD_FAST);
    INSTALL_ENUM(UStringTrieBuildOption, "SMALL", USTRINGTRIE_BUILD_SMALL);

    INSTALL_ENUM(UStringTrieResult, "NO_MATCH", USTRINGTRIE_NO_MATCH);
    INSTALL_ENUM(UStringTrieResult, "NO_VALUE", USTRINGTRIE_NO_VALUE);
    INSTALL_ENUM(UStringTrieResult, "FINAL_VALUE", USTRINGTRIE_FINAL_VALUE);
    INSTALL_ENUM(UStringTrieResult, "INTERMEDIATE_VALUE", USTRINGTRIE_INTERMEDIATE_VALUE);
#endif
}
