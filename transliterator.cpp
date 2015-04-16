/* ====================================================================
 * Copyright (c) 2009-2010 Open Source Applications Foundation.
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
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UTransDirection);


/* Transliterator */

class t_transliterator : public _wrapper {
public:
    Transliterator *object;
};

static PyObject *t_transliterator_getMaximumContextLength(t_transliterator *self);
static PyObject *t_transliterator_countElements(t_transliterator *self);
static PyObject *t_transliterator_getElement(t_transliterator *self, PyObject *arg);
static PyObject *t_transliterator_createInverse(t_transliterator *self);
static PyObject *t_transliterator_transliterate(t_transliterator *self, PyObject *args);
static PyObject *t_transliterator_getAvailableIDs(PyTypeObject *type);
static PyObject *t_transliterator_createInstance(PyTypeObject *type, PyObject *args);

static PyMethodDef t_transliterator_methods[] = {
    DECLARE_METHOD(t_transliterator, transliterate, METH_VARARGS),
    DECLARE_METHOD(t_transliterator, getMaximumContextLength, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, countElements, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, getElement, METH_O),
    DECLARE_METHOD(t_transliterator, createInverse, METH_NOARGS),
    DECLARE_METHOD(t_transliterator, getAvailableIDs, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_transliterator, createInstance, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(Transliterator, t_transliterator, UObject,
             Transliterator, abstract_init);

PyObject *wrap_Transliterator(Transliterator *transliterator)
{
    return wrap_Transliterator(transliterator, T_OWNED);
}

PyObject *wrap_Transliterator(const Transliterator &transliterator)
{
    return wrap_Transliterator(transliterator.clone(), T_OWNED);
}


static PyObject *t_transliterator_transliterate(t_transliterator *self,
                                                PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    int32_t start, limit;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            self->object->transliterate(_u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u, &_u, &start, &limit))
        {
            self->object->transliterate(_u, start, limit);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "transliterate", args);
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

static PyObject *t_transliterator_createInverse(t_transliterator *self)
{
    Transliterator *transliterator;
    
    STATUS_CALL(transliterator = self->object->createInverse(status));
    return wrap_Transliterator(transliterator);
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
    UnicodeString *u;
    UnicodeString _u;
    UTransDirection direction;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &direction))
        {
            STATUS_CALL(transliterator =
                        Transliterator::createInstance(*u, direction, status));
            return wrap_Transliterator(transliterator);
        }
        break;
    }

    return PyErr_SetArgsError(type, "createInstance", args);
}

static PyObject *t_transliterator_str(t_transliterator *self)
{
    UnicodeString _u = self->object->getID();
    return PyUnicode_FromUnicodeString(&_u);
}


void _init_transliterator(PyObject *m)
{
    TransliteratorType.tp_str = (reprfunc) t_transliterator_str;

    INSTALL_CONSTANTS_TYPE(UTransDirection, m);
    REGISTER_TYPE(Transliterator, m);

    INSTALL_ENUM(UTransDirection, UTRANS_FORWARD);
    INSTALL_ENUM(UTransDirection, UTRANS_REVERSE);
}
