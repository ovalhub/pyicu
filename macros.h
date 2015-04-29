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

#ifndef _macros_h
#define _macros_h

PyObject *make_descriptor(PyObject *value);
PyObject *make_descriptor(PyTypeObject *value);
PyObject *make_descriptor(PyObject *(*get)(PyObject *));


#define PYTHON_CALL(action)                                             \
    {                                                                   \
        action;                                                         \
        if (PyErr_Occurred())                                           \
            return NULL;                                                \
    }

#define INT_PYTHON_CALL(action)                                         \
    {                                                                   \
        action;                                                         \
        if (PyErr_Occurred())                                           \
            return -1;                                                  \
    }

#define STATUS_CALL(action)                                             \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(status).reportError();                  \
    }

#define STATUS_PYTHON_CALL(action)                                      \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(status).reportError();                  \
        if (PyErr_Occurred())                                           \
            return NULL;                                                \
    }

#define STATUS_PARSER_CALL(action)                                      \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        UParseError parseError;                                         \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(parseError, status).reportError();      \
    }

#define STATUS_PARSER_PYTHON_CALL(action)                               \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        UParseError parseError;                                         \
        action;                                                         \
        if (U_FAILURE(status))                                          \
            return ICUException(parseError, status).reportError();      \
        if (PyErr_Occurred())                                           \
            return NULL;                                                \
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

#define INT_STATUS_PYTHON_CALL(action)                                  \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        action;                                                         \
        if (U_FAILURE(status))                                          \
        {                                                               \
            ICUException(status).reportError();                         \
            return -1;                                                  \
        }                                                               \
        if (PyErr_Occurred())                                           \
            return -1;                                                  \
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

#define INT_STATUS_PARSER_PYTHON_CALL(action)                           \
    {                                                                   \
        UErrorCode status = U_ZERO_ERROR;                               \
        UParseError parseError;                                         \
        action;                                                         \
        if (U_FAILURE(status))                                          \
        {                                                               \
            ICUException(parseError, status).reportError();             \
            return -1;                                                  \
        }                                                               \
        if (PyErr_Occurred())                                           \
            return -1;                                                  \
    }


#define DECLARE_METHOD(type, name, flags)                               \
    { #name, (PyCFunction) type##_##name, flags, "" }

#define DECLARE_TYPE(name, t_name, base, icuClass, init, dealloc)           \
PyTypeObject name##Type_ = {                                                \
    PyVarObject_HEAD_INIT(NULL, 0)                                          \
    /* tp_name            */   "icu."#name,                                 \
    /* tp_basicsize       */   sizeof(t_name),                              \
    /* tp_itemsize        */   0,                                           \
    /* tp_dealloc         */   (destructor)dealloc,                         \
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
    /* tp_doc             */   #name" objects",                             \
    /* tp_traverse        */   0,                                           \
    /* tp_clear           */   0,                                           \
    /* tp_richcompare     */   0,                                           \
    /* tp_weaklistoffset  */   0,                                           \
    /* tp_iter            */   0,                                           \
    /* tp_iternext        */   0,                                           \
    /* tp_methods         */   t_name##_methods,                            \
    /* tp_members         */   0,                                           \
    /* tp_getset          */   0,                                           \
    /* tp_base            */   &base##Type_,                                \
    /* tp_dict            */   0,                                           \
    /* tp_descr_get       */   0,                                           \
    /* tp_descr_set       */   0,                                           \
    /* tp_dictoffset      */   0,                                           \
    /* tp_init            */   (initproc)init,                              \
    /* tp_alloc           */   0,                                           \
    /* tp_new             */   0,                                           \
};                                                                          \
PyObject *wrap_##name(icuClass *object, int flags)                        \
{                                                                         \
    if (object)                                                           \
    {                                                                     \
        t_name *self = (t_name *) name##Type_.tp_alloc(&name##Type_, 0);  \
        if (self)                                                         \
        {                                                                 \
            self->object = object;                                        \
            self->flags = flags;                                          \
        }                                                                 \
        return (PyObject *) self;                                         \
    }                                                                     \
    Py_RETURN_NONE;                                                       \
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
PyTypeObject name##Type_ = {                                                \
    PyVarObject_HEAD_INIT(NULL, 0)                                          \
    /* tp_name            */   "icu."#name,                                 \
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
    /* tp_doc             */   #name" objects",                             \
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
PyObject *wrap_##name(icuStruct *object, int flags)                       \
{                                                                         \
    if (object)                                                           \
    {                                                                     \
        t_name *self = (t_name *) name##Type_.tp_alloc(&name##Type_, 0);  \
        if (self)                                                         \
        {                                                                 \
            self->object = object;                                        \
            self->flags = flags;                                          \
        }                                                                 \
        return (PyObject *) self;                                         \
    }                                                                     \
    Py_RETURN_NONE;                                                       \
}


#define DECLARE_CONSTANTS_TYPE(name)                                    \
PyTypeObject name##Type_ = {                                            \
    PyVarObject_HEAD_INIT(NULL, 0)                                      \
    /* tp_name            */   "icu."#name,                             \
    /* tp_basicsize       */   0,                                       \
    /* tp_itemsize        */   0,                                       \
};


#if U_ICU_VERSION_HEX < 0x04060000

#define TYPE_CLASSID(className)                      \
    className::getStaticClassID(), &className##Type_

#define TYPE_ID(className)                           \
    (UClassID) (className##_ID), &className##Type_

#else

#define TYPE_CLASSID(className)                      \
    typeid(className).name(), &className##Type_

#define TYPE_ID(className)                           \
    typeid(className).name(), &className##Type_

#endif


#if U_ICU_VERSION_HEX < 0x04060000

#define INSTALL_TYPE(className, module)                                 \
    if (PyType_Ready(&className##Type_) == 0)                           \
    {                                                                   \
        Py_INCREF(&className##Type_);                                   \
        PyModule_AddObject(module, #className,                          \
                           (PyObject *) &className##Type_);             \
        registerType(&className##Type_, (UClassID) className##_ID);     \
    }

#define REGISTER_TYPE(className, module)                                  \
    if (PyType_Ready(&className##Type_) == 0)                             \
    {                                                                     \
        Py_INCREF(&className##Type_);                                     \
        PyModule_AddObject(module, #className,                            \
                           (PyObject *) &className##Type_);               \
        registerType(&className##Type_, className::getStaticClassID());   \
    }

#else

#define INSTALL_TYPE(className, module)                                 \
    if (PyType_Ready(&className##Type_) == 0)                           \
    {                                                                   \
        Py_INCREF(&className##Type_);                                   \
        PyModule_AddObject(module, #className,                          \
                           (PyObject *) &className##Type_);             \
        registerType(&className##Type_, typeid(className).name());      \
    }

#define REGISTER_TYPE(className, module)                                \
    if (PyType_Ready(&className##Type_) == 0)                           \
    {                                                                   \
        Py_INCREF(&className##Type_);                                   \
        PyModule_AddObject(module, #className,                          \
                           (PyObject *) &className##Type_);             \
        registerType(&className##Type_, typeid(className).name());      \
    }

#endif

#define INSTALL_STRUCT(name, module)                                   \
    if (PyType_Ready(&name##Type_) == 0)                               \
    {                                                                  \
        Py_INCREF(&name##Type_);                                       \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type_);  \
    }

#define INSTALL_CONSTANTS_TYPE(name, module)                           \
    if (PyType_Ready(&name##Type_) == 0)                               \
    {                                                                  \
        Py_INCREF(&name##Type_);                                       \
        PyModule_AddObject(module, #name, (PyObject *) &name##Type_);  \
    }

#define INSTALL_MODULE_INT(module, name)                               \
    PyModule_AddIntConstant(module, #name, name);

#define INSTALL_STATIC_INT(type, name)                                      \
    PyDict_SetItemString(type##Type_.tp_dict, #name,                        \
                         make_descriptor(PyInt_FromLong(type::name)))

#define INSTALL_ENUM(type, name, value)                                 \
    PyDict_SetItemString(type##Type_.tp_dict, name,                     \
                         make_descriptor(PyInt_FromLong(value)))

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

#define Py_RETURN_SELF()                                    \
    {                                                       \
        Py_INCREF(self);                                    \
        return (PyObject *) self;                           \
    }


#define DEFINE_RICHCMP(name, t_name) \
    static PyObject *t_name ## _richcmp(t_name *self,                     \
                                        PyObject *arg, int op)            \
    {                                                                     \
        int b = 0;                                                        \
        name *object;                                                     \
        if (!parseArg(arg, "P", TYPE_CLASSID(name), &object))             \
        {                                                                 \
            switch (op) {                                                 \
              case Py_EQ:                                                 \
              case Py_NE:                                                 \
                b = *self->object == *object;                             \
                if (op == Py_EQ)                                          \
                    Py_RETURN_BOOL(b);                                    \
                Py_RETURN_BOOL(!b);                                       \
              case Py_LT:                                                 \
              case Py_LE:                                                 \
              case Py_GT:                                                 \
              case Py_GE:                                                 \
                PyErr_SetNone(PyExc_NotImplementedError);                 \
                return NULL;                                              \
            }                                                             \
        }                                                                 \
        return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg); \
    }


#define DEFINE_ABSTRACT(t_name, name, method)                           \
    static PyObject *t_name##_##method(t_name *self, PyObject *arg)     \
    {									\
        return PyErr_Format(PyExc_NotImplementedError,                  \
			    "%s.%s() is abstract", #name, #method);	\
    }


#if U_ICU_VERSION_HEX < 0x04060000
#define ISINSTANCE(obj, type)                                   \
    ((obj)->getDynamicClassID() == type::getStaticClassID())
#else
#define ISINSTANCE(obj, type)                                   \
    (dynamic_cast<type *>(obj) != NULL)
#endif

#define RETURN_WRAPPED_IF_ISINSTANCE(obj, type)                 \
    if (ISINSTANCE(obj, type))                                  \
        return wrap_##type((type *)(obj), T_OWNED)


#endif /* _macros_h */
