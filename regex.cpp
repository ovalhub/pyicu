/* ====================================================================
 * Copyright (c) 2010-2011 Open Source Applications Foundation.
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
#include "regex.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(URegexpFlag);


/* RegexPattern */

class t_regexpattern : public _wrapper {
public:
    RegexPattern *object;
    PyObject *re;  // the wrapped original regex UnicodeString
};

static int t_regexpattern_init(t_regexpattern *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_regexpattern_matcher(t_regexpattern *self, PyObject *args);
static PyObject *t_regexpattern_pattern(t_regexpattern *self);
static PyObject *t_regexpattern_flags(t_regexpattern *self);
static PyObject *t_regexpattern_split(t_regexpattern *self, PyObject *args);
static PyObject *t_regexpattern_compile(PyTypeObject *type, PyObject *args);
static PyObject *t_regexpattern_matches(PyTypeObject *type, PyObject *args);

static PyObject *wrap_RegexPattern(RegexPattern *pattern, PyObject *re);
static PyObject *wrap_RegexMatcher(RegexMatcher *matcher, PyObject *pattern,
                                   PyObject *input);

static PyMethodDef t_regexpattern_methods[] = {
    DECLARE_METHOD(t_regexpattern, matcher, METH_VARARGS),
    DECLARE_METHOD(t_regexpattern, pattern, METH_NOARGS),
    DECLARE_METHOD(t_regexpattern, flags, METH_NOARGS),
    DECLARE_METHOD(t_regexpattern, split, METH_VARARGS),
    DECLARE_METHOD(t_regexpattern, compile, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_regexpattern, matches, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_regexpattern_dealloc(t_regexpattern *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->re);
}

DECLARE_TYPE(RegexPattern, t_regexpattern, UObject, RegexPattern,
             t_regexpattern_init, t_regexpattern_dealloc);

/* RegexMatcher */

class t_regexmatcher : public _wrapper {
public:
    RegexMatcher *object;
    PyObject *re;
    PyObject *input;
    PyObject *pattern;
#if U_ICU_VERSION_HEX >= 0x04000000
    PyObject *callable;
#endif
};

static int t_regexmatcher_init(t_regexmatcher *self,
                               PyObject *args, PyObject *kwds);
static PyObject *t_regexmatcher_matches(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_lookingAt(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_find(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_pattern(t_regexmatcher *self);
static PyObject *t_regexmatcher_group(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_groupCount(t_regexmatcher *self);
static PyObject *t_regexmatcher_start(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_end(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_reset(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_input(t_regexmatcher *self);
#if U_ICU_VERSION_HEX >= 0x04000000
static PyObject *t_regexmatcher_region(t_regexmatcher *self, PyObject *args);
static PyObject *t_regexmatcher_regionStart(t_regexmatcher *self);
static PyObject *t_regexmatcher_regionEnd(t_regexmatcher *self);
static PyObject *t_regexmatcher_hasTransparentBounds(t_regexmatcher *self);
static PyObject *t_regexmatcher_useTransparentBounds(t_regexmatcher *self,
                                                     PyObject *arg);
static PyObject *t_regexmatcher_hasAnchoringBounds(t_regexmatcher *self);
static PyObject *t_regexmatcher_useAnchoringBounds(t_regexmatcher *self,
                                                   PyObject *arg);
static PyObject *t_regexmatcher_hitEnd(t_regexmatcher *self);
static PyObject *t_regexmatcher_requireEnd(t_regexmatcher *self);
#endif
static PyObject *t_regexmatcher_replaceAll(t_regexmatcher *self, PyObject *arg);
static PyObject *t_regexmatcher_replaceFirst(t_regexmatcher *self,
                                             PyObject *arg);
static PyObject *t_regexmatcher_appendReplacement(t_regexmatcher *self,
                                                  PyObject *args);
static PyObject *t_regexmatcher_appendTail(t_regexmatcher *self, PyObject *arg);
static PyObject *t_regexmatcher_split(t_regexmatcher *self, PyObject *args);
#if U_ICU_VERSION_HEX >= 0x04000000
static PyObject *t_regexmatcher_setTimeLimit(t_regexmatcher *self,
                                             PyObject *arg);
static PyObject *t_regexmatcher_getTimeLimit(t_regexmatcher *self);
static PyObject *t_regexmatcher_setStackLimit(t_regexmatcher *self,
                                             PyObject *arg);
static PyObject *t_regexmatcher_getStackLimit(t_regexmatcher *self);
static PyObject *t_regexmatcher_setMatchCallback(t_regexmatcher *self,
                                                 PyObject *arg);
static PyObject *t_regexmatcher_getMatchCallback(t_regexmatcher *self);
#endif

static PyMethodDef t_regexmatcher_methods[] = {
    DECLARE_METHOD(t_regexmatcher, matches, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, lookingAt, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, find, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, pattern, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, group, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, groupCount, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, start, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, end, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, reset, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, input, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, replaceAll, METH_O),
    DECLARE_METHOD(t_regexmatcher, replaceFirst, METH_O),
    DECLARE_METHOD(t_regexmatcher, appendReplacement, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, appendTail, METH_O),
    DECLARE_METHOD(t_regexmatcher, split, METH_VARARGS),
#if U_ICU_VERSION_HEX >= 0x04000000
    DECLARE_METHOD(t_regexmatcher, region, METH_VARARGS),
    DECLARE_METHOD(t_regexmatcher, regionStart, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, regionEnd, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, hasTransparentBounds, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, useTransparentBounds, METH_O),
    DECLARE_METHOD(t_regexmatcher, hasAnchoringBounds, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, useAnchoringBounds, METH_O),
    DECLARE_METHOD(t_regexmatcher, hitEnd, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, requireEnd, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, setTimeLimit, METH_O),
    DECLARE_METHOD(t_regexmatcher, getTimeLimit, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, setStackLimit, METH_O),
    DECLARE_METHOD(t_regexmatcher, getStackLimit, METH_NOARGS),
    DECLARE_METHOD(t_regexmatcher, setMatchCallback, METH_O),
    DECLARE_METHOD(t_regexmatcher, getMatchCallback, METH_NOARGS),
#endif
    { NULL, NULL, 0, NULL }
};

static void t_regexmatcher_dealloc(t_regexmatcher *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->re);
    Py_CLEAR(self->input);
    Py_CLEAR(self->pattern);
#if U_ICU_VERSION_HEX >= 0x04000000
    Py_CLEAR(self->callable);
#endif

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(RegexMatcher, t_regexmatcher, UObject, RegexMatcher,
             t_regexmatcher_init, t_regexmatcher_dealloc);


/* RegexPattern */

static PyObject *wrap_RegexPattern(RegexPattern *pattern, PyObject *re)
{
    t_regexpattern *self = (t_regexpattern *)
        wrap_RegexPattern(pattern, T_OWNED);

    self->re = re;  /* steals reference */

    return (PyObject *) self;
}

static int t_regexpattern_init(t_regexpattern *self,
                               PyObject *args, PyObject *kwds)
{
    RegexPattern *pattern;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new RegexPattern();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "P", TYPE_CLASSID(RegexPattern), &pattern))
        {
            self->object = new RegexPattern(*pattern);
            self->flags = T_OWNED;
            self->re = NULL;
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

static PyObject *t_regexpattern_matcher(t_regexpattern *self, PyObject *args)
{
    UnicodeString *u;
    RegexMatcher *matcher;
    PyObject *input = NULL;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(matcher = self->object->matcher(status));
        return wrap_RegexMatcher(matcher, (PyObject *) self, input);
      case 1:
        if (!parseArgs(args, "W", &u, &input))
        {
            UErrorCode status = U_ZERO_ERROR;

            matcher = self->object->matcher(*u, status);
            if (U_FAILURE(status))
            {
                Py_XDECREF(input);
                return ICUException(status).reportError();
            }

            return wrap_RegexMatcher(matcher, (PyObject *) self, input);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "matcher", args);
}

static PyObject *t_regexpattern_pattern(t_regexpattern *self)
{
    UnicodeString u = self->object->pattern();
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_regexpattern_flags(t_regexpattern *self)
{
    uint32_t flags = self->object->flags();
    return PyInt_FromLong(flags);
}

static PyObject *t_regexpattern_split(t_regexpattern *self, PyObject *args)
{
    UnicodeString *u, _u;
    int capacity, count;

    if (!parseArgs(args, "Si", &u, &_u, &capacity))
    {
        if (capacity < 32)
        {
            UnicodeString array[31];
            PyObject *tuple;

            STATUS_CALL(count = self->object->split(*u, array, capacity,
                                                    status));
            tuple = PyTuple_New(count);
            for (int i = 0; i < count; i++)
                PyTuple_SET_ITEM(tuple, i,
                                 PyUnicode_FromUnicodeString(&array[i]));

            return tuple;
        }
        else
        {
            class finalizer {
            public:
                UnicodeString *array;
                finalizer(int size) {
                    array = new UnicodeString[size];
                }
                ~finalizer() {
                    delete[] array;
                }
            };
            finalizer finally(capacity);
            PyObject *tuple;

            if (!finally.array)
                return PyErr_NoMemory();

            STATUS_CALL(count = self->object->split(*u, finally.array,
                                                    capacity, status));
            tuple = PyTuple_New(count);
            for (int i = 0; i < count; i++)
                PyTuple_SET_ITEM(tuple, i, PyUnicode_FromUnicodeString(&finally.array[i]));

            return tuple;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "split", args);
}

static PyObject *t_regexpattern_compile(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u;
    uint32_t flags;
    RegexPattern *pattern;
    PyObject *re = NULL;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "W", &u, &re))
        {
            UErrorCode status = U_ZERO_ERROR;
            UParseError parseError;

            pattern = RegexPattern::compile(*u, parseError, status);
            if (U_FAILURE(status))
            {
                Py_XDECREF(re);
                return ICUException(parseError, status).reportError();
            }
            return wrap_RegexPattern(pattern, re);
        }
        break;
      case 2:
        if (!parseArgs(args, "Wi", &u, &re, &flags))
        {
            UErrorCode status = U_ZERO_ERROR;
            UParseError parseError;

            pattern = RegexPattern::compile(*u, flags, parseError, status);
            if (U_FAILURE(status))
            {
                Py_XDECREF(re);
                return ICUException(parseError, status).reportError();
            }
            return wrap_RegexPattern(pattern, re);
        }
        break;
    }

    return PyErr_SetArgsError(type, "compile", args);
}

static PyObject *t_regexpattern_matches(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    UBool b;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            STATUS_PARSER_CALL(b = RegexPattern::matches(*u0, *u1, parseError,
                                                         status));
            Py_RETURN_BOOL(b);
        }
        break;
    }

    return PyErr_SetArgsError(type, "matches", args);
}

static PyObject *t_regexpattern_str(t_regexpattern *self)
{
    UnicodeString u = self->object->pattern();
    return PyUnicode_FromUnicodeString(&u);
}

static PyObject *t_regexpattern_richcmp(t_regexpattern *self,
                                        PyObject *arg, int op)
{
    RegexPattern *pattern;
    int b = 0;

    if (!parseArg(arg, "P", TYPE_CLASSID(RegexPattern), &pattern))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *pattern;
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


/* RegexMatcher */

static int t_regexmatcher_init(t_regexmatcher *self,
                               PyObject *args, PyObject *kwds)
{
    RegexMatcher *matcher;
    UnicodeString *u0, *u1;
    uint32_t flags;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Wi", &u0, &self->re, &flags))
        {
            INT_STATUS_CALL(matcher = new RegexMatcher(*u0, flags, status));
            self->object = matcher;
            self->pattern = NULL;
            self->input = NULL;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "WWi", &u0, &self->re, &u1, &self->input, &flags))
        {
            INT_STATUS_CALL(matcher = new RegexMatcher(*u0, *u1, flags,
                                                       status));
            self->object = matcher;
            self->pattern = NULL;
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

static PyObject *wrap_RegexMatcher(RegexMatcher *matcher, PyObject *pattern,
                                   PyObject *input)
{
    t_regexmatcher *self = (t_regexmatcher *)
        wrap_RegexMatcher(matcher, T_OWNED);

    Py_INCREF(pattern);    
    self->pattern = pattern;

    self->input = input;  /* steals reference */
    self->re = NULL;

    return (PyObject *) self;
}

static PyObject *t_regexmatcher_matches(t_regexmatcher *self, PyObject *args)
{
    int32_t startIndex;
    UBool b;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(b = self->object->matches(status));
        Py_RETURN_BOOL(b);
      case 1:
        if (!parseArgs(args, "i", &startIndex))
        {
            STATUS_CALL(b = self->object->matches(startIndex, status));
            Py_RETURN_BOOL(b);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "matches", args);
}

static PyObject *t_regexmatcher_lookingAt(t_regexmatcher *self, PyObject *args)
{
    int32_t startIndex;
    UBool b;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(b = self->object->lookingAt(status));
        Py_RETURN_BOOL(b);
      case 1:
        if (!parseArgs(args, "i", &startIndex))
        {
            STATUS_CALL(b = self->object->lookingAt(startIndex, status));
            Py_RETURN_BOOL(b);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "matches", args);
}

static PyObject *t_regexmatcher_find(t_regexmatcher *self, PyObject *args)
{
    int32_t startIndex;
    UBool b;

    switch (PyTuple_Size(args)) {
      case 0:
        b = self->object->find();
        Py_RETURN_BOOL(b);
      case 1:
        if (!parseArgs(args, "i", &startIndex))
        {
            STATUS_CALL(b = self->object->find(startIndex, status));
            Py_RETURN_BOOL(b);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "matches", args);
}

static PyObject *t_regexmatcher_pattern(t_regexmatcher *self)
{
    const RegexPattern pattern = self->object->pattern();
    return wrap_RegexPattern(pattern.clone(), T_OWNED);
}

static PyObject *t_regexmatcher_group(t_regexmatcher *self, PyObject *args)
{
    UnicodeString u;
    int32_t groupNum;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(u = self->object->group(status));
        return PyUnicode_FromUnicodeString(&u);
      case 1:
        if (!parseArgs(args, "i", &groupNum))
        {
            STATUS_CALL(u = self->object->group(groupNum, status));
            return PyUnicode_FromUnicodeString(&u);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "group", args);
}

static PyObject *t_regexmatcher_groupCount(t_regexmatcher *self)
{
    int32_t count = self->object->groupCount();
    return PyInt_FromLong(count);
}

static PyObject *t_regexmatcher_start(t_regexmatcher *self, PyObject *args)
{
    int32_t index, groupNum;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(index = self->object->start(status));
        return PyInt_FromLong(index);
      case 1:
        if (!parseArgs(args, "i", &groupNum))
        {
            STATUS_CALL(index = self->object->start(groupNum, status));
            return PyInt_FromLong(index);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "start", args);
}

static PyObject *t_regexmatcher_end(t_regexmatcher *self, PyObject *args)
{
    int32_t index, groupNum;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(index = self->object->end(status));
        return PyInt_FromLong(index);
      case 1:
        if (!parseArgs(args, "i", &groupNum))
        {
            STATUS_CALL(index = self->object->end(groupNum, status));
            return PyInt_FromLong(index);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "end", args);
}

static PyObject *t_regexmatcher_reset(t_regexmatcher *self, PyObject *args)
{
    int32_t index;
    UnicodeString *u, _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->reset();
        Py_RETURN_SELF();
      case 1:
        if (!parseArgs(args, "i", &index))
        {
            STATUS_CALL(self->object->reset(index, status));
            Py_RETURN_SELF();
        }
        if (!parseArgs(args, "S", &u, &_u))
        {
            self->object->reset(*u);
            Py_RETURN_SELF();
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "reset", args);
}

static PyObject *t_regexmatcher_input(t_regexmatcher *self)
{
    UnicodeString u = self->object->input();
    return PyUnicode_FromUnicodeString(&u);
}

#if U_ICU_VERSION_HEX >= 0x04000000

static PyObject *t_regexmatcher_region(t_regexmatcher *self, PyObject *args)
{
    int32_t start, end;

    if (!parseArgs(args, "ii", &start, &end))
    {
        STATUS_CALL(self->object->region(start, end, status));
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "region", args);
}

static PyObject *t_regexmatcher_regionStart(t_regexmatcher *self)
{
    int32_t index = self->object->regionStart();
    return PyInt_FromLong(index);
}

static PyObject *t_regexmatcher_regionEnd(t_regexmatcher *self)
{
    int32_t index = self->object->regionEnd();
    return PyInt_FromLong(index);
}

static PyObject *t_regexmatcher_hasTransparentBounds(t_regexmatcher *self)
{
    UBool b = self->object->hasTransparentBounds();
    Py_RETURN_BOOL(b);
}

static PyObject *t_regexmatcher_useTransparentBounds(t_regexmatcher *self,
                                                     PyObject *arg)
{
    UBool b;

    if (!parseArg(arg, "B", &b))
    {
        self->object->useTransparentBounds(b);
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "useTransparentBounds", arg);
}

static PyObject *t_regexmatcher_hasAnchoringBounds(t_regexmatcher *self)
{
    UBool b = self->object->hasAnchoringBounds();
    Py_RETURN_BOOL(b);
}

static PyObject *t_regexmatcher_useAnchoringBounds(t_regexmatcher *self,
                                                   PyObject *arg)
{
    UBool b;

    if (!parseArg(arg, "B", &b))
    {
        self->object->useAnchoringBounds(b);
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "useAnchoringBounds", arg);
}

static PyObject *t_regexmatcher_hitEnd(t_regexmatcher *self)
{
    UBool b = self->object->hitEnd();
    Py_RETURN_BOOL(b);
}

static PyObject *t_regexmatcher_requireEnd(t_regexmatcher *self)
{
    UBool b = self->object->requireEnd();
    Py_RETURN_BOOL(b);
}

#endif

static PyObject *t_regexmatcher_replaceAll(t_regexmatcher *self, PyObject *arg)
{
    UnicodeString *u, _u, result;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(result = self->object->replaceAll(*u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "replaceAll", arg);
}

static PyObject *t_regexmatcher_replaceFirst(t_regexmatcher *self,
                                             PyObject *arg)
{
    UnicodeString *u, _u, result;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(result = self->object->replaceFirst(*u, status));
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "replaceFirst", arg);
}

static PyObject *t_regexmatcher_appendReplacement(t_regexmatcher *self,
                                                  PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;

    if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
    {
        STATUS_CALL(self->object->appendReplacement(*u0, *u1, status));
        Py_RETURN_SELF();
    }

    return PyErr_SetArgsError((PyObject *) self, "appendReplacement", args);
}

static PyObject *t_regexmatcher_appendTail(t_regexmatcher *self, PyObject *arg)
{
    UnicodeString *u, _u, result;

    if (!parseArg(arg, "S", &u, &_u))
    {
        result = self->object->appendTail(*u);
        return PyUnicode_FromUnicodeString(&result);
    }

    return PyErr_SetArgsError((PyObject *) self, "appendTail", arg);
}

static PyObject *t_regexmatcher_split(t_regexmatcher *self, PyObject *args)
{
    UnicodeString *u, _u;
    int capacity, count;

    if (!parseArgs(args, "Si", &u, &_u, &capacity))
    {
        if (capacity < 32)
        {
            UnicodeString array[31];
            PyObject *tuple;

            STATUS_CALL(count = self->object->split(*u, array, capacity,
                                                    status));
            tuple = PyTuple_New(count);
            for (int i = 0; i < count; i++)
                PyTuple_SET_ITEM(tuple, i,
                                 PyUnicode_FromUnicodeString(&array[i]));

            return tuple;
        }
        else
        {
            class finalizer {
            public:
                UnicodeString *array;
                finalizer(int size) {
                    array = new UnicodeString[size];
                }
                ~finalizer() {
                    delete[] array;
                }
            };
            finalizer finally(capacity);
            PyObject *tuple;

            if (!finally.array)
                return PyErr_NoMemory();

            STATUS_CALL(count = self->object->split(*u, finally.array,
                                                    capacity, status));
            tuple = PyTuple_New(count);
            for (int i = 0; i < count; i++)
                PyTuple_SET_ITEM(tuple, i, PyUnicode_FromUnicodeString(&finally.array[i]));

            return tuple;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "split", args);
}

#if U_ICU_VERSION_HEX >= 0x04000000

static PyObject *t_regexmatcher_setTimeLimit(t_regexmatcher *self,
                                             PyObject *arg)
{
    int32_t limit;

    if (!parseArg(arg, "i", &limit))
    {
        STATUS_CALL(self->object->setTimeLimit(limit, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setTimeLimit", arg);
}

static PyObject *t_regexmatcher_getTimeLimit(t_regexmatcher *self)
{
    int32_t limit = self->object->getTimeLimit();
    return PyInt_FromLong(limit);
}

static PyObject *t_regexmatcher_setStackLimit(t_regexmatcher *self,
                                             PyObject *arg)
{
    int32_t limit;

    if (!parseArg(arg, "i", &limit))
    {
        STATUS_CALL(self->object->setStackLimit(limit, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setStackLimit", arg);
}

static PyObject *t_regexmatcher_getStackLimit(t_regexmatcher *self)
{
    int32_t limit = self->object->getStackLimit();
    return PyInt_FromLong(limit);
}

static UBool t_regexmatcher_matchCallback(const void *context, int32_t steps)
{
    t_regexmatcher *self = (t_regexmatcher *) context;
    PyObject *n = PyInt_FromLong(steps);
    PyObject *args = PyTuple_Pack(1, n);
    PyObject *result = PyObject_Call(self->callable, args, NULL);
    int b;

    Py_DECREF(args);
    Py_DECREF(n);
    
    if (!result)
        return 0;

    b = PyObject_IsTrue(result);
    Py_DECREF(result);
    if (b == -1)
        return 0;

    return b;
}

static PyObject *t_regexmatcher_setMatchCallback(t_regexmatcher *self,
                                                 PyObject *arg)
{
    if (PyCallable_Check(arg))
    {
        Py_INCREF(arg);
        Py_XDECREF(self->callable);
        self->callable = arg;

        STATUS_CALL(self->object->setMatchCallback(t_regexmatcher_matchCallback,
                                                   self, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setMatchCallback", arg);
}

static PyObject *t_regexmatcher_getMatchCallback(t_regexmatcher *self)
{
    if (self->callable)
    {
        Py_INCREF(self->callable);
        return self->callable;
    }

    Py_RETURN_NONE;
}

#endif

static PyObject *t_regexmatcher_str(t_regexmatcher *self)
{
    UnicodeString u = self->object->pattern().pattern();
    return PyUnicode_FromUnicodeString(&u);
}

#if U_ICU_VERSION_HEX >= 0x04000000

static int t_regexmatcher_traverse(t_regexmatcher *self, visitproc visit,
                                   void *arg)
{
    Py_VISIT(self->callable);
    return 0;
}

static int t_regexmatcher_clear(t_regexmatcher *self)
{
    Py_CLEAR(self->callable);
    return 0;
}

#endif

void _init_regex(PyObject *m)
{
    RegexPatternType_.tp_str = (reprfunc) t_regexpattern_str;
    RegexPatternType_.tp_richcompare = (richcmpfunc) t_regexpattern_richcmp;

#if U_ICU_VERSION_HEX >= 0x04000000
    RegexMatcherType_.tp_traverse = (traverseproc) t_regexmatcher_traverse;
    RegexMatcherType_.tp_clear = (inquiry) t_regexmatcher_clear;
    RegexMatcherType_.tp_flags |= Py_TPFLAGS_HAVE_GC;
#endif
    RegexMatcherType_.tp_str = (reprfunc) t_regexmatcher_str;

    INSTALL_CONSTANTS_TYPE(URegexpFlag, m);

    REGISTER_TYPE(RegexPattern, m);
    REGISTER_TYPE(RegexMatcher, m);

    INSTALL_ENUM(URegexpFlag, "CANON_EQ", UREGEX_CANON_EQ);
    INSTALL_ENUM(URegexpFlag, "CASE_INSENSITIVE", UREGEX_CASE_INSENSITIVE);
    INSTALL_ENUM(URegexpFlag, "COMMENTS", UREGEX_COMMENTS);
    INSTALL_ENUM(URegexpFlag, "DOTALL", UREGEX_DOTALL);
    INSTALL_ENUM(URegexpFlag, "MULTILINE", UREGEX_MULTILINE);
    INSTALL_ENUM(URegexpFlag, "UWORD", UREGEX_UWORD);
#if U_ICU_VERSION_HEX >= 0x04000000
    INSTALL_ENUM(URegexpFlag, "LITERAL", UREGEX_LITERAL);
    INSTALL_ENUM(URegexpFlag, "UNIX_LINES", UREGEX_UNIX_LINES);
    INSTALL_ENUM(URegexpFlag, "ERROR_ON_UNKNOWN_ESCAPES", UREGEX_ERROR_ON_UNKNOWN_ESCAPES);
#endif
}
