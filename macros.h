/* ====================================================================
 * Copyright (c) 2004-2006 Open Source Applications Foundation.
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

#ifndef _macros_h
#define _macros_h

PyObject *make_descriptor(PyObject *value);
PyObject *make_descriptor(PyTypeObject *value);
PyObject *make_descriptor(PyObject *(*get)(PyObject *));


#define STATUS_CALL(action)                                             \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(status).reportError();                  \
    }

#define STATUS_PARSER_CALL(action)                                      \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        UParseError parseError;                                         \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(parseError, status).reportError();      \
    }

#define INT_STATUS_CALL(action)                                         \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        action;                                                         \
        if (U_FAILURE(status))                                          \
        {                                                               \
            ICUException(status).reportError();                         \
            return -1;                                                  \
        }                                                               \
    }

#define INT_STATUS_PARSER_CALL(action)                                  \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        UParseError parseError;                                         \
        action;                                                         \
        if (U_FAILURE(status))                                          \
        {                                                               \
            ICUException(parseError, status).reportError();             \
            return -1;                                                  \
        }                                                               \
    }


#define DECLARE_METHOD(type, name, flags)                               \
    { #name, (PyCFunction) type##_##name, flags, "" }

#define DECLARE_TYPE(name, t_name, base, icuClass, init)                    \
PyTypeObject name##Type = {                                                 \
    PyObject_HEAD_INIT(NULL)                                                \
    /* ob_size            */   0,                                           \
    /* tp_name            */   "PyICU."#name,                               \
    /* tp_basicsize       */   sizeof(t_name),                              \
    /* tp_itemsize        */   0,                                           \
    /* tp_dealloc         */   0,                                           \
    /* tp_print           */   0,                                           \
    /* tp_getattr         */   0,                                           \
    /* tp_setattr         */   0,                                           \
    /* tp_compare         */   0,                                           \
    /* tp_repr            */   0,                                           \
    /* tp_as_number       */   0,                                           \
    /* tp_as_sequence     */   0,                                           \
    /* tp_as_mapping      */   0,                                           \
    /* tp_hash            */   0,                                           \
    /* tp_call            */   0,                                           \
    /* tp_str             */   0,                                           \
    /* tp_getattro        */   0,                                           \
    /* tp_setattro        */   0,                                           \
    /* tp_as_buffer       */   0,                                           \
    /* tp_flags           */   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,    \
    /* tp_doc             */   #t_name" objects",                           \
    /* tp_traverse        */   0,                                           \
    /* tp_clear           */   0,                                           \
    /* tp_richcompare     */   0,                                           \
    /* tp_weaklistoffset  */   0,                                           \
    /* tp_iter            */   0,                                           \
    /* tp_iternext        */   0,                                           \
    /* tp_methods         */   t_name##_methods,                            \
    /* tp_members         */   0,                                           \
    /* tp_getset          */   0,                                           \
    /* tp_base            */   &base##Type,                                 \
    /* tp_dict            */   0,                                           \
    /* tp_descr_get       */   0,                                           \
    /* tp_descr_set       */   0,                                           \
    /* tp_dictoffset      */   0,                                           \
    /* tp_init            */   (initproc)init,                              \
    /* tp_alloc           */   0,                                           \
    /* tp_new             */   0,                                           \
};                                                                          \
PyObject *wrap_##name(icuClass *object, int flags)                      \
{                                                                       \
    if (object)                                                         \
    {                                                                   \
        t_name *self = (t_name *) name##Type.tp_alloc(&name##Type, 0);  \
        if (self)                                                       \
        {                                                               \
            self->object = object;                                      \
            self->flags = flags;                                        \
        }                                                               \
        return (PyObject *) self;                                       \
    }                                                                   \
    Py_RETURN_NONE;                                                     \
}


#define DECLARE_STRUCT(name, t_name, icuStruct, init, dealloc)          \
static PyObject *t_name##_new(PyTypeObject *type,                       \
                              PyObject *args, PyObject *kwds)           \
{                                                                       \
    t_name *self = (t_name *) type->tp_alloc(type, 0);                  \
    if (self)                                                           \
    {                                                                   \
        self->object = NULL;                                            \
        self->flags = 0;                                                \
    }                                                                   \
    return (PyObject *) self;                                           \
}                                                                       \
PyTypeObject name##Type = {                                                 \
    PyObject_HEAD_INIT(NULL)                                                \
    /* ob_size            */   0,                                           \
    /* tp_name            */   "PyICU."#name,                               \
    /* tp_basicsize       */   sizeof(t_name),                              \
    /* tp_itemsize        */   0,                                           \
    /* tp_dealloc         */   (destructor)t_name##_dealloc,                \
    /* tp_print           */   0,                                           \
    /* tp_getattr         */   0,                                           \
    /* tp_setattr         */   0,                                           \
    /* tp_compare         */   0,                                           \
    /* tp_repr            */   0,                                           \
    /* tp_as_number       */   0,                                           \
    /* tp_as_sequence     */   0,                                           \
    /* tp_as_mapping      */   0,                                           \
    /* tp_hash            */   0,                                           \
    /* tp_call            */   0,                                           \
    /* tp_str             */   0,                                           \
    /* tp_getattro        */   0,                                           \
    /* tp_setattro        */   0,                                           \
    /* tp_as_buffer       */   0,                                           \
    /* tp_flags           */   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,    \
    /* tp_doc             */   #t_name" objects",                           \
    /* tp_traverse        */   0,                                           \
    /* tp_clear           */   0,                                           \
    /* tp_richcompare     */   0,                                           \
    /* tp_weaklistoffset  */   0,                                           \
    /* tp_iter            */   0,                                           \
    /* tp_iternext        */   0,                                           \
    /* tp_methods         */   t_name##_methods,                            \
    /* tp_members         */   0,                                           \
    /* tp_getset          */   0,                                           \
    /* tp_base            */   0,                                           \
    /* tp_dict            */   0,                                           \
    /* tp_descr_get       */   0,                                           \
    /* tp_descr_set       */   0,                                           \
    /* tp_dictoffset      */   0,                                           \
    /* tp_init            */   (initproc)init,                              \
    /* tp_alloc           */   0,                                           \
    /* tp_new             */   (newfunc)t_name##_new,                       \
};                                                                          \
PyObject *wrap_##name(icuStruct *object, int flags)                     \
{                                                                       \
    if (object)                                                         \
    {                                                                   \
        t_name *self = (t_name *) name##Type.tp_alloc(&name##Type, 0);  \
        if (self)                                                       \
        {                                                               \
            self->object = object;                                      \
            self->flags = flags;                                        \
        }                                                               \
        return (PyObject *) self;                                       \
    }                                                                   \
    Py_RETURN_NONE;                                                     \
}


#define DECLARE_CONSTANTS_TYPE(name)                                    \
PyTypeObject name##Type = {                                             \
    PyObject_HEAD_INIT(NULL)                                            \
    /* ob_size            */   0,                                       \
    /* tp_name            */   "PyICU."#name,                           \
    /* tp_basicsize       */   0,                                       \
    /* tp_itemsize        */   0,                                       \
};

#define TYPE_CLASSID(name)                      \
    name::getStaticClassID(), &name##Type

#define TYPE_ID(name)                           \
    name##_ID, &name##Type

#define INSTALL_TYPE(name, module)                                   \
    if (PyType_Ready(&name##Type) == 0)                              \
    {                                                                \
        Py_INCREF(&name##Type);                                      \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type); \
        registerType(&name##Type, (UClassID) name##_ID);             \
    }

#define INSTALL_STRUCT(name, module)                                 \
    if (PyType_Ready(&name##Type) == 0)                              \
    {                                                                \
        Py_INCREF(&name##Type);                                      \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type); \
    }

#define REGISTER_TYPE(name, module)                                  \
    if (PyType_Ready(&name##Type) == 0)                              \
    {                                                                \
        Py_INCREF(&name##Type);                                      \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type); \
        registerType(&name##Type, name::getStaticClassID());    \
    }

#define INSTALL_CONSTANTS_TYPE(name, module)                         \
    if (PyType_Ready(&name##Type) == 0)                              \
    {                                                                \
        Py_INCREF(&name##Type);                                      \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type); \
    }

#define INSTALL_MODULE_INT(module, name)                                \
    PyModule_AddIntConstant(module, #name, name);

#define INSTALL_STATIC_INT(type, name)                                      \
    PyDict_SetItemString(type##Type.tp_dict, #name,                         \
                         make_descriptor(PyInt_FromLong(type::name)))

#define INSTALL_ENUM(type, name)                                        \
    PyDict_SetItemString(type##Type.tp_dict, #name,                     \
                         make_descriptor(PyInt_FromLong(name)))

#define Py_RETURN_BOOL(b)                       \
    {                                           \
        if (b)                                  \
            Py_RETURN_TRUE;                     \
        else                                    \
            Py_RETURN_FALSE;                    \
    }

#define Py_RETURN_ARG(args, n)                          \
    {                                                   \
        PyObject *arg = PyTuple_GET_ITEM(args, n);      \
        Py_INCREF(arg);                                 \
        return arg;                                     \
    }

#define Py_RETURN_SELF()                                \
    Py_INCREF(self);                                    \
    return (PyObject *) self;

#endif /* _macros_h */
