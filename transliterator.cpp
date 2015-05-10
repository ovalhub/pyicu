/* ====================================================================
 * Copyright (c) 2009-2015 Open Source Applications Foundation.
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
#include "transliterator.h"
#include "unicodeset.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UTransDirection);


/* UTransPosition */

class t_utransposition : public _wrapper {
public:
    UTransPosition *object;
};

static int t_utransposition_init(t_utransposition *self,
                                 PyObject *args, PyObject *kwds);

static PyMethodDef t_utransposition_methods[] = {
    { NULL, NULL, 0, NULL }
};

static void t_utransposition_dealloc(t_utransposition *self)
{
    if (self->object)
    {
        if (self->flags & T_OWNED)
            delete self->object;
            
        self->object = NULL;
    }

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(UTransPosition, t_utransposition, UTransPosition,
               t_utransposition_init, t_utransposition_dealloc);


/* Transliterator */

static int t_transliterator_init(t_transliterator *self,
                                 PyObject *args, PyObject *kwds);
static PyObject *t_transliterator_getMaximumContextLength(t_transliterator *self);
static PyObject *t_transliterator_countElements(t_transliterator *self);
static PyObject *t_transliterator_getElement(t_transliterator *self, PyObject *arg);
static PyObject *t_transliterator_getSourceSet(t_transliterator *self);
static PyObject *t_transliterator_getTargetSet(t_transliterator *self);
static PyObject *t_transliterator_createInverse(t_transliterator *self);
static PyObject *t_transliterator_toRules(t_transliterator *self, PyObject *args);
static PyObject *t_transliterator_transliterate(t_transliterator *self, PyObject *args);
static PyObject *t_transliterator_finishTransliteration(t_transliterator *self, PyObject *args);
static PyObject *t_transliterator_filteredTransliterate(t_transliterator *self, PyObject *args);
static PyObject *t_transliterator_getFilter(t_transliterator *self);
static PyObject *t_transliterator_orphanFilter(t_transliterator *self);
static PyObject *t_transliterator_adoptFilter(t_transliterator *self, PyObject *arg);
static PyObject *t_transliterator_getAvailableIDs(PyTypeObject *type);
static PyObject *t_transliterator_createInstance(PyTypeObject *type, PyObject *args);
static PyObject *t_transliterator_createFromRules(PyTypeObject *type, PyObject *args);
static PyObject *t_transliterator_registerInstance(PyTypeObject *type, PyObject *args);

static PyMethodDef t_transliterator_methods[] = {
    DECLARE_METHOD(t_transliterator, transliterate, METH_VARARGS),
    DECLARE_METHOD(t_transliterator, finishTransliteration, METH_VARARGS),
    DECLARE_METHOD(t_transliterator, filteredTransliterate, METH_VARARGS),
    DECLARE_METHOD(t_transliterator, getMaximumContextLength, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, countElements, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, getElement, METH_O),
    DECLARE_METHOD(t_transliterator, getSourceSet, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, getTargetSet, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, createInverse, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, toRules, METH_VARARGS),
    DECLARE_METHOD(t_transliterator, getFilter, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, orphanFilter, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, adoptFilter, METH_O),
    DECLARE_METHOD(t_transliterator, getAvailableIDs, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_transliterator, createInstance, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_transliterator, createFromRules, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_transliterator, registerInstance, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Transliterator, t_transliterator, UObject,
             Transliterator, t_transliterator_init, NULL);


/* PythonTransliterator */

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(PythonTransliterator);

PythonTransliterator::PythonTransliterator(t_transliterator *self,
                                           UnicodeString &id) :
    Transliterator(id, NULL)
{
    this->self = self;
    Py_XINCREF(this->self);
}

PythonTransliterator::PythonTransliterator(t_transliterator *self,
                                           UnicodeString &id,
                                           UnicodeFilter *adoptedFilter) :
    Transliterator(id, adoptedFilter)
{
    this->self = self;
    Py_XINCREF(this->self);
}

/**
 * Copy constructor.
 */
PythonTransliterator::PythonTransliterator(const PythonTransliterator& p) :
    Transliterator(p)
{
    this->self = p.self;
    Py_XINCREF(this->self);
}

PythonTransliterator::~PythonTransliterator()
{
    Py_XDECREF(this->self);
    this->self = NULL;
}

Transliterator* PythonTransliterator::clone(void) const
{
    return new PythonTransliterator(*this);
}

void PythonTransliterator::handleTransliterate(Replaceable& text,
                                               UTransPosition& pos,
                                               UBool incremental) const
{
    if (ISINSTANCE(&text, UnicodeString))
    {
        PyObject *name = PyString_FromString("handleTransliterate");
        PyObject *p_text = wrap_UnicodeString((UnicodeString *) &text, 0);
        PyObject *p_pos = wrap_UTransPosition(&pos, 0);
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, name, p_text, p_pos,
                                       incremental ? Py_True : Py_False, NULL);

        Py_DECREF(name);
        Py_DECREF(p_text);
        Py_DECREF(p_pos);
        Py_XDECREF(result);
    }
}


/* UTransPosition */

static int t_utransposition_init(t_utransposition *self,
                                 PyObject *args, PyObject *kwds)
{
    static const char *kwnames[] = {
        "contextStart", "contextLimit", "start", "limit", NULL
    };
    int contextStart = 0, contextLimit = 0, start = 0, limit = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", (char **) kwnames,
                                     &contextStart, &contextLimit,
                                     &start, &limit))
        return -1;

    self->object = new UTransPosition();
    if (!self->object)
    {
        PyErr_NoMemory();
        return -1;
    }

    self->object->contextStart = contextStart;
    self->object->contextLimit = contextLimit;
    self->object->start = start;
    self->object->limit = limit;

    self->flags = T_OWNED;

    return 0;
}

static int t_utransposition_setter(int32_t *slot, PyObject *value)
{
    int32_t n;

    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete attribute");
        return -1;
    }

    n = PyInt_AsLong(value);
    if (PyErr_Occurred())
        return -1;

    *slot = n;

    return 0;
}

static PyObject *t_utransposition_getContextLimit(t_utransposition *self,
                                                  void *closure)
{
    return PyInt_FromLong(self->object->contextLimit);
}

static int t_utransposition_setContextLimit(t_utransposition *self,
                                            PyObject *value, void *closure)
{
    return t_utransposition_setter(&self->object->contextLimit, value);
}

static PyObject *t_utransposition_getContextStart(t_utransposition *self,
                                                  void *closure)
{
    return PyInt_FromLong(self->object->contextStart);
}

static int t_utransposition_setContextStart(t_utransposition *self,
                                            PyObject *value, void *closure)
{
    return t_utransposition_setter(&self->object->contextStart, value);
}

static PyObject *t_utransposition_getLimit(t_utransposition *self,
                                           void *closure)
{
    return PyInt_FromLong(self->object->limit);
}

static int t_utransposition_setLimit(t_utransposition *self,
                                     PyObject *value, void *closure)
{
    return t_utransposition_setter(&self->object->limit, value);
}

static PyObject *t_utransposition_getStart(t_utransposition *self,
                                           void *closure)
{
    return PyInt_FromLong(self->object->start);
}

static int t_utransposition_setStart(t_utransposition *self,
                                     PyObject *value, void *closure)
{
    return t_utransposition_setter(&self->object->start, value);
}

static PyGetSetDef t_utransposition_properties[] = {
    {(char *) "contextLimit",
     (getter) t_utransposition_getContextLimit,
     (setter) t_utransposition_setContextLimit,
     (char *) "Ending index, exclusive, of the context to be considered for a transliteration operation.",
     NULL},
    {(char *) "contextStart",
     (getter) t_utransposition_getContextStart,
     (setter) t_utransposition_setContextStart,
     (char *) "Beginning index, inclusive, of the context to be considered for a transliteration operation.",
     NULL},
    {(char *) "limit",
     (getter) t_utransposition_getLimit,
     (setter) t_utransposition_setLimit,
     (char *) "Ending index, exclusive, of the text to be transliterated.",
     NULL},
    {(char *) "start",
     (getter) t_utransposition_getStart,
     (setter) t_utransposition_setStart,
     (char *) "Beginning index, inclusive, of the text to be transliterated.",
     NULL},
    {NULL}  /* Sentinel */
};


/* Transliterator */

static int t_transliterator_init(t_transliterator *self,
                                 PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    UnicodeFilter *adoptedFilter;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            self->object = new PythonTransliterator(self, *u);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "SP", &u, &_u, TYPE_CLASSID(UnicodeFilter),
                       &adoptedFilter))
        {
            self->object = new PythonTransliterator(self, *u, (UnicodeFilter *) adoptedFilter->clone());
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

PyObject *wrap_Transliterator(Transliterator *transliterator)
{
    return wrap_Transliterator(transliterator, T_OWNED);
}

PyObject *wrap_Transliterator(const Transliterator &transliterator)
{
    return wrap_Transliterator(transliterator.clone(), T_OWNED);
}

static PyObject *t_transliterator_toRules(t_transliterator *self,
                                          PyObject *args)
{
    UnicodeString u;
    int b = 0;

    switch (PyTuple_Size(args)) {
      case 0:
        PYTHON_CALL(self->object->toRules(u, 0));
        return PyUnicode_FromUnicodeString(&u);
      case 1:
        if (!parseArgs(args, "b", &b))
        {
            PYTHON_CALL(self->object->toRules(u, b));
            return PyUnicode_FromUnicodeString(&u);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "toRules", args);
}

static PyObject *t_transliterator_transliterate(t_transliterator *self,
                                                PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    t_utransposition *utransposition;
    int32_t start, limit, len;
    UChar32 c;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "U", &u0))
        {
            PYTHON_CALL(self->object->transliterate(*u0));
            Py_RETURN_ARG(args, 0);
        }
        if (!parseArgs(args, "s", &_u0))
        {
            PYTHON_CALL(self->object->transliterate(_u0));
            return PyUnicode_FromUnicodeString(&_u0);
        }
        break;
      case 2:
        if (!parseArgs(args, "UO", &UTransPositionType_, &u0, &utransposition))
        {
            STATUS_PYTHON_CALL(self->object->transliterate(*u0, *utransposition->object, status));
            Py_RETURN_ARG(args, 0);
        }
        if (!parseArgs(args, "sO", &UTransPositionType_, &_u0, &utransposition))
        {
            STATUS_PYTHON_CALL(self->object->transliterate(_u0, *utransposition->object, status));
            return PyUnicode_FromUnicodeString(&_u0);
        }
        break;
      case 3:
        if (!parseArgs(args, "Uii", &u0, &start, &limit))
        {
            PYTHON_CALL(limit = self->object->transliterate(*u0, start, limit));
            return PyInt_FromLong(limit);
        }
        if (!parseArgs(args, "sii", &_u0, &start, &limit))
        {
            PYTHON_CALL(self->object->transliterate(_u0, start, limit));
            return PyUnicode_FromUnicodeString(&_u0);
        }
        if (!parseArgs(args, "UOS", &UTransPositionType_,
                       &u0, &utransposition, &u1, &_u1))
        {
            STATUS_CALL(len = toUChar32(*u1, &c, status));
            if (len == 1)
            {
                STATUS_PYTHON_CALL(self->object->transliterate(*u0, *utransposition->object, c, status));
            }
            else
            {
                STATUS_PYTHON_CALL(self->object->transliterate(*u0, *utransposition->object, _u1, status));
            }
            Py_RETURN_ARG(args, 0);
        }
        if (!parseArgs(args, "sOS", &UTransPositionType_, 
                       &_u0, &utransposition, &u1, &_u1))
        {
            STATUS_CALL(len = toUChar32(*u1, &c, status));
            if (len == 1)
            {
                STATUS_PYTHON_CALL(self->object->transliterate(_u0, *utransposition->object, c, status));
            }
            else
            {
                STATUS_PYTHON_CALL(self->object->transliterate(_u0, *utransposition->object, _u1, status));
            }
            return PyUnicode_FromUnicodeString(&_u0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "transliterate", args);
}

static PyObject *t_transliterator_finishTransliteration(t_transliterator *self,
                                                        PyObject *args)
{
    UnicodeString *u, _u;
    t_utransposition *utransposition;

    if (!parseArgs(args, "UO", &UTransPositionType_, &u, &utransposition))
    {
        self->object->finishTransliteration(*u, *utransposition->object);
        Py_RETURN_ARG(args, 0);
    }
    if (!parseArgs(args, "sO", &UTransPositionType_, &_u, &utransposition))
    {
        self->object->finishTransliteration(_u, *utransposition->object);
        return PyUnicode_FromUnicodeString(&_u);
    }

    return PyErr_SetArgsError((PyObject *) self, "finishTransliteration", args);
}

static PyObject *t_transliterator_filteredTransliterate(t_transliterator *self,
                                                        PyObject *args)
{
    UnicodeString *u, _u;
    t_utransposition *utransposition;
    int incremental;

    if (!parseArgs(args, "UOB", &UTransPositionType_, &u, &utransposition,
                   &incremental))
    {
        self->object->filteredTransliterate(*u, *utransposition->object,
                                            incremental);
        Py_RETURN_ARG(args, 0);
    }
    if (!parseArgs(args, "sOB", &UTransPositionType_, &_u, &utransposition,
                   &incremental))
    {
        self->object->filteredTransliterate(_u, *utransposition->object,
                                            incremental);
        return PyUnicode_FromUnicodeString(&_u);
    }

    return PyErr_SetArgsError((PyObject *) self, "filteredTransliterate", args);
}

static PyObject *t_transliterator_getMaximumContextLength(t_transliterator *self)
{
    return PyInt_FromLong(self->object->getMaximumContextLength());
}

static PyObject *t_transliterator_countElements(t_transliterator *self)
{
    return PyInt_FromLong(self->object->countElements());
}

static PyObject *t_transliterator_getElement(t_transliterator *self,
                                             PyObject *arg)
{
    int32_t i = PyInt_AsLong(arg);
    const Transliterator *transliterator;

    if (PyErr_Occurred())
        return NULL;

    STATUS_CALL(transliterator = &self->object->getElement(i, status));

    return wrap_Transliterator(*transliterator);
}

static PyObject *t_transliterator_getSourceSet(t_transliterator *self)
{
    UnicodeSet set;

    self->object->getSourceSet(set);
    return wrap_UnicodeSet(new UnicodeSet(set), T_OWNED);
}

static PyObject *t_transliterator_getTargetSet(t_transliterator *self)
{
    UnicodeSet set;

    self->object->getTargetSet(set);
    return wrap_UnicodeSet(new UnicodeSet(set), T_OWNED);
}

static PyObject *t_transliterator_createInverse(t_transliterator *self)
{
    Transliterator *transliterator;
    
    STATUS_CALL(transliterator = self->object->createInverse(status));
    return wrap_Transliterator(transliterator);
}

static PyObject *t_transliterator_getFilter(t_transliterator *self)
{
    const UnicodeFilter *filter = self->object->getFilter();

    if (filter == NULL)
        Py_RETURN_NONE;

    return wrap_UnicodeFilter((UnicodeFilter *) filter->clone(), T_OWNED);
}

static PyObject *t_transliterator_orphanFilter(t_transliterator *self)
{
    UnicodeFilter *filter = self->object->orphanFilter();

    if (filter == NULL)
        Py_RETURN_NONE;

    return wrap_UnicodeFilter(filter, T_OWNED);
}

static PyObject *t_transliterator_adoptFilter(t_transliterator *self,
                                              PyObject *arg)
{
    UnicodeFilter *filter;

    if (arg == Py_None)
        self->object->adoptFilter(NULL);
    else if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeFilter), &filter))
        self->object->adoptFilter((UnicodeFilter *) filter->clone());
    else
        return PyErr_SetArgsError((PyObject *) self, "adoptFilter", arg);

    Py_RETURN_NONE;
}

static PyObject *t_transliterator_getAvailableIDs(PyTypeObject *type)
{
    StringEnumeration *se;

    STATUS_CALL(se = Transliterator::getAvailableIDs(status));
    return wrap_StringEnumeration(se, T_OWNED);
}

static PyObject *t_transliterator_createInstance(PyTypeObject *type,
                                                 PyObject *args)
{
    Transliterator *transliterator;
    UnicodeString *u, _u;
    UTransDirection direction = UTRANS_FORWARD;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            STATUS_CALL(transliterator = Transliterator::createInstance(
                *u, direction, status));
            return wrap_Transliterator(transliterator);
        }
        break;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &direction))
        {
            STATUS_CALL(transliterator = Transliterator::createInstance(
                *u, direction, status));
            return wrap_Transliterator(transliterator);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createInstance", args);
}

static PyObject *t_transliterator_createFromRules(PyTypeObject *type,
                                                  PyObject *args)
{
    Transliterator *transliterator;
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    UTransDirection direction = UTRANS_FORWARD;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            STATUS_PARSER_CALL(transliterator = Transliterator::createFromRules(
                *u0, *u1, direction, parseError, status));
            return wrap_Transliterator(transliterator);
        }
        break;
      case 3:
        if (!parseArgs(args, "SSi", &u0, &_u0, &u1, &_u1, &direction))
        {
            STATUS_PARSER_CALL(transliterator = Transliterator::createFromRules(
                *u0, *u1, direction, parseError, status));
            return wrap_Transliterator(transliterator);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createFromRules", args);
}

static PyObject *t_transliterator_registerInstance(PyTypeObject *type,
                                                   PyObject *args)
{
    Transliterator *transliterator;

    if (!parseArgs(args, "P", TYPE_CLASSID(Transliterator), &transliterator))
    {
        Transliterator::registerInstance(transliterator);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError(type, "registerInstance", args);
}

static PyObject *t_transliterator_str(t_transliterator *self)
{
    UnicodeString _u = self->object->getID();
    return PyUnicode_FromUnicodeString(&_u);
}


void _init_transliterator(PyObject *m)
{
    TransliteratorType_.tp_str = (reprfunc) t_transliterator_str;
    UTransPositionType_.tp_getset = t_utransposition_properties;

    INSTALL_CONSTANTS_TYPE(UTransDirection, m);
    INSTALL_STRUCT(UTransPosition, m);
    REGISTER_TYPE(Transliterator, m);

    INSTALL_ENUM(UTransDirection, "FORWARD", UTRANS_FORWARD);
    INSTALL_ENUM(UTransDirection, "REVERSE", UTRANS_REVERSE);
}
