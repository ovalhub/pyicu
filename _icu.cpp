/* ====================================================================
 * Copyright (c) 2004-2019 Open Source Applications Foundation.
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

#include <Python.h>
#include "structmember.h"

#include "common.h"
#include "errors.h"
#include "bases.h"
#include "locale.h"
#include "transliterator.h"
#include "iterators.h"
#include "format.h"
#include "dateformat.h"
#include "numberformat.h"
#include "calendar.h"
#include "collator.h"
#include "charset.h"
#include "tzinfo.h"
#include "unicodeset.h"
#include "regex.h"
#include "normalizer.h"
#include "search.h"
#if U_ICU_VERSION_HEX < VERSION_HEX(58, 0, 0)
#include "layoutengine.h"
#endif
#include "script.h"
#include "spoof.h"
#include "idna.h"
#include "char.h"
#include "shape.h"
#include "measureunit.h"
#include "casemap.h"
#include "tries.h"
#include "gender.h"
#include "bidi.h"


/* const variable descriptor */

class t_descriptor {
public:
    PyObject_HEAD
    int flags;
    union {
        PyObject *value;
        PyObject *(*get)(PyObject *);
    } access;
};

#define DESCRIPTOR_STATIC 0x1

static void t_descriptor_dealloc(t_descriptor *self);
static PyObject *t_descriptor___get__(t_descriptor *self,
                                      PyObject *obj, PyObject *type);

static PyMemberDef t_descriptor_members[] = {
    { NULL, 0, 0, 0, NULL }
};

static PyMethodDef t_descriptor_methods[] = {
    { NULL, NULL, 0, NULL }
};


PyTypeObject ConstVariableDescriptorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "icu.ConstVariableDescriptor",       /* tp_name */
    sizeof(t_descriptor),                /* tp_basicsize */
    0,                                   /* tp_itemsize */
    (destructor)t_descriptor_dealloc,    /* tp_dealloc */
    0,                                   /* tp_print */
    0,                                   /* tp_getattr */
    0,                                   /* tp_setattr */
    0,                                   /* tp_compare */
    0,                                   /* tp_repr */
    0,                                   /* tp_as_number */
    0,                                   /* tp_as_sequence */
    0,                                   /* tp_as_mapping */
    0,                                   /* tp_hash  */
    0,                                   /* tp_call */
    0,                                   /* tp_str */
    0,                                   /* tp_getattro */
    0,                                   /* tp_setattro */
    0,                                   /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                  /* tp_flags */
    "const variable descriptor",         /* tp_doc */
    0,                                   /* tp_traverse */
    0,                                   /* tp_clear */
    0,                                   /* tp_richcompare */
    0,                                   /* tp_weaklistoffset */
    0,                                   /* tp_iter */
    0,                                   /* tp_iternext */
    t_descriptor_methods,                /* tp_methods */
    t_descriptor_members,                /* tp_members */
    0,                                   /* tp_getset */
    0,                                   /* tp_base */
    0,                                   /* tp_dict */
    (descrgetfunc)t_descriptor___get__,  /* tp_descr_get */
    0,                                   /* tp_descr_set */
    0,                                   /* tp_dictoffset */
    0,                                   /* tp_init */
    0,                                   /* tp_alloc */
    0,                                   /* tp_new */
};

static void t_descriptor_dealloc(t_descriptor *self)
{
    if (self->flags & DESCRIPTOR_STATIC)
    {
        Py_DECREF(self->access.value);
    }
    Py_TYPE(self)->tp_free((PyObject *) self);
}

PyObject *make_descriptor(PyObject *value)
{
    t_descriptor *self = (t_descriptor *)
        ConstVariableDescriptorType.tp_alloc(&ConstVariableDescriptorType, 0);

    if (self)
    {
        self->access.value = value;
        self->flags = DESCRIPTOR_STATIC;
    }
    else
        Py_DECREF(value);

    return (PyObject *) self;
}

PyObject *make_descriptor(PyTypeObject *value)
{
    t_descriptor *self = (t_descriptor *)
        ConstVariableDescriptorType.tp_alloc(&ConstVariableDescriptorType, 0);

    if (self)
    {
        Py_INCREF(value);
        self->access.value = (PyObject *) value;
        self->flags = DESCRIPTOR_STATIC;
    }

    return (PyObject *) self;
}

PyObject *make_descriptor(PyObject *(*get)(PyObject *))
{
    t_descriptor *self = (t_descriptor *)
        ConstVariableDescriptorType.tp_alloc(&ConstVariableDescriptorType, 0);

    if (self)
    {
        self->access.get = get;
        self->flags = 0;
    }

    return (PyObject *) self;
}

static PyObject *t_descriptor___get__(t_descriptor *self,
                                      PyObject *obj, PyObject *type)
{
    if (self->flags & DESCRIPTOR_STATIC)
    {
        Py_INCREF(self->access.value);
        return self->access.value;
    }
    else if (obj == NULL || obj == Py_None)
    {
        Py_INCREF(self);
        return (PyObject *) self;
    }

    return self->access.get(obj);
}


static PyMethodDef _icu_funcs[] = {
    { NULL, NULL, 0, NULL }
};

static PyObject *PyInit_icu(PyObject *m)
{
    PyObject *ver;

    PyType_Ready(&ConstVariableDescriptorType);
    Py_INCREF(&ConstVariableDescriptorType);

    ver = PyString_FromString(PYICU_VER);
    PyObject_SetAttrString(m, "VERSION", ver); Py_DECREF(ver);

    ver = PyString_FromString(PYICU_ICU_MAX_VER);
    PyObject_SetAttrString(m, "ICU_MAX_MAJOR_VERSION", ver); Py_DECREF(ver);

    ver = PyString_FromString(U_ICU_VERSION);
    PyObject_SetAttrString(m, "ICU_VERSION", ver); Py_DECREF(ver);

    ver = PyString_FromString(U_UNICODE_VERSION);
    PyObject_SetAttrString(m, "UNICODE_VERSION", ver); Py_DECREF(ver);

    ver = PyString_FromString(PY_VERSION);
    PyObject_SetAttrString(m, "PY_VERSION", ver); Py_DECREF(ver);

#ifdef PYPY_VERSION
    ver = PyString_FromString(PYPY_VERSION);
    PyObject_SetAttrString(m, "PYPY_VERSION", ver); Py_DECREF(ver);
#endif

    PyObject *module = PyImport_ImportModule("icu");

    if (!module)
    {
        if (!PyErr_Occurred())
            PyErr_SetString(PyExc_ImportError, "icu");
        return NULL;
    }

    PyExc_ICUError = PyObject_GetAttrString(module, "ICUError");
    PyExc_InvalidArgsError = PyObject_GetAttrString(module, "InvalidArgsError");
    Py_DECREF(module);

    _init_common(m);
    _init_errors(m);
    _init_bases(m);
    _init_locale(m);
    _init_transliterator(m);
    _init_iterators(m);
    _init_format(m);
    _init_dateformat(m);
    _init_numberformat(m);
    _init_calendar(m);
    _init_collator(m);
    _init_charset(m);
    _init_tzinfo(m);
    _init_unicodeset(m);
    _init_regex(m);
    _init_normalizer(m);
    _init_search(m);
#if U_ICU_VERSION_HEX < VERSION_HEX(58, 0, 0)
    _init_layoutengine(m);
#endif
    _init_script(m);
    _init_spoof(m);
    _init_idna(m);
    _init_char(m);
    _init_shape(m);
    _init_measureunit(m);
    _init_casemap(m);
    _init_tries(m);
    _init_gender(m);
    _init_bidi(m);

    return m;
}


#if PY_MAJOR_VERSION >= 3
/* TODO: Properly implement http://www.python.org/dev/peps/pep-3121/ */
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    /* m_name    */ "icu._icu",
    /* m_doc     */ "PyICU extension module",
    /* m_size    */ -1,
    /* m_methods */ _icu_funcs,
    /* m_reload  */ NULL,
    /* m_clear   */ NULL,
    /* m_free    */ NULL,
};
extern "C" {
    PyMODINIT_FUNC PyInit__icu(void)
    {
        PyObject *m = PyModule_Create(&moduledef);
        return PyInit_icu(m);
    }
}
#else
extern "C" {
    void init_icu(void)
    {
        PyObject *m = Py_InitModule3("icu._icu", _icu_funcs, "icu._icu");
        PyInit_icu(m);
    }
}
#endif
