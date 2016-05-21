/* ====================================================================
 * Copyright (c) 2007-2014 Open Source Applications Foundation.
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
#include "datetime.h"

#include "bases.h"
#include "calendar.h"
#include "tzinfo.h"
#include "macros.h"

#ifdef PYPY_VERSION
#if !defined(PYPY_VERSION_NUM) || PYPY_VERSION_NUM < 0x05020000
typedef PyObject PyDateTime_TZInfo;
#endif
#endif

/* A tzinfo extension that wraps an ICU timezone wrapper.
 * The tz field is supposed to be immutable.
 */
typedef struct {
    PyDateTime_TZInfo dt_tzinfo;
    t_timezone *tz;
} t_tzinfo;

/* A tzinfo extension that wraps an ICU tzinfo wrapper.
 * The tzinfo field can be changed and defaults to the default ICU tzinfo
 * when not set. When this field changes or the default ICU tzinfo is changed,
 * times expressed with this pseudo-timezone, named "World/Floating", appear
 * to float.
 */
typedef struct {
    PyDateTime_TZInfo dt_tzinfo;
    t_tzinfo *tzinfo;
} t_floatingtz;

static void t_tzinfo_dealloc(t_tzinfo *self);
static PyObject *t_tzinfo_new(PyTypeObject *type,
                              PyObject *args, PyObject *kwds);
static int t_tzinfo_init(t_tzinfo *self, PyObject *args, PyObject *kwds);
static PyObject *t_tzinfo_repr(t_tzinfo *self);
static PyObject *t_tzinfo_str(t_tzinfo *self);
static long t_tzinfo_hash(t_tzinfo *self);
static PyObject *t_tzinfo_richcmp(t_tzinfo *self, PyObject *other, int op);

static PyObject *t_tzinfo__resetDefault(PyTypeObject *cls);
static PyObject *t_tzinfo_getDefault(PyTypeObject *cls);
static PyObject *t_tzinfo_setDefault(PyTypeObject *cls, PyObject *tz);
static PyObject *t_tzinfo_getFloating(PyTypeObject *cls);
static PyObject *t_tzinfo_getInstances(PyTypeObject *cls);
static PyObject *t_tzinfo_getInstance(PyTypeObject *cls, PyObject *arg);

static PyObject *t_tzinfo_utcoffset(t_tzinfo *self, PyObject *dt);
static PyObject *t_tzinfo_dst(t_tzinfo *self, PyObject *dt);
static PyObject *t_tzinfo_tzname(t_tzinfo *self, PyObject *dt);

static PyObject *t_tzinfo__getTimezone(t_tzinfo *self, void *data);
static PyObject *t_tzinfo__getTZID(t_tzinfo *self, void *data);

static PyObject *_instances;
static t_tzinfo *_default, *_floating;
static PyTypeObject *datetime_tzinfoType, *datetime_deltaType;
static PyObject *FLOATING_TZNAME;
static PyObject *toordinal_NAME;
static PyObject *weekday_NAME;


static PyMethodDef t_tzinfo_methods[] = {
    { "_resetDefault", (PyCFunction) t_tzinfo__resetDefault, METH_NOARGS | METH_CLASS, "" },
    { "getDefault", (PyCFunction) t_tzinfo_getDefault, METH_NOARGS | METH_CLASS, "" },
    { "setDefault", (PyCFunction) t_tzinfo_setDefault, METH_O | METH_CLASS, "" },
    { "getFloating", (PyCFunction) t_tzinfo_getFloating, METH_NOARGS | METH_CLASS, "" },
    { "getInstances", (PyCFunction) t_tzinfo_getInstances, METH_NOARGS | METH_CLASS, "" },
    { "getInstance", (PyCFunction) t_tzinfo_getInstance, METH_O | METH_CLASS, "" },
    { "utcoffset", (PyCFunction) t_tzinfo_utcoffset, METH_O, "" },
    { "dst", (PyCFunction) t_tzinfo_dst, METH_O, "" },
    { "tzname", (PyCFunction) t_tzinfo_tzname, METH_O, "" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef t_tzinfo_properties[] = {
    { (char *) "timezone", (getter) t_tzinfo__getTimezone, NULL,
      (char *) "timezone property", NULL },
    { (char *) "tzid", (getter) t_tzinfo__getTZID, NULL,
      (char *) "tzid property", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject TZInfoType_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "icu.ICUtzinfo",                    /* tp_name */
    sizeof(t_tzinfo),                   /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor) t_tzinfo_dealloc,      /* tp_dealloc */
    0,                                  /* tp_print */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_compare */
    (reprfunc) t_tzinfo_repr,           /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    (hashfunc) t_tzinfo_hash,           /* tp_hash  */
    0,                                  /* tp_call */
    (reprfunc) t_tzinfo_str,            /* tp_str */
    0,                                  /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    (Py_TPFLAGS_DEFAULT |
     Py_TPFLAGS_BASETYPE),              /* tp_flags */
    "",                                 /* tp_doc */
    0,                                  /* tp_traverse */
    0,                                  /* tp_clear */
    (richcmpfunc) t_tzinfo_richcmp,     /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    0,                                  /* tp_iter */
    0,                                  /* tp_iternext */
    t_tzinfo_methods,                   /* tp_methods */
    0,                                  /* tp_members */
    t_tzinfo_properties,                /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    0,                                  /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc) t_tzinfo_init,           /* tp_init */
    0,                                  /* tp_alloc */
    (newfunc) t_tzinfo_new,             /* tp_new */
    0,                                  /* tp_free */
};


static void t_floatingtz_dealloc(t_floatingtz *self);
static PyObject *t_floatingtz_new(PyTypeObject *type,
                                  PyObject *args, PyObject *kwds);
static int t_floatingtz_init(t_floatingtz *self,
                             PyObject *args, PyObject *kwds);
static PyObject *t_floatingtz_repr(t_floatingtz *self);
static PyObject *t_floatingtz_str(t_floatingtz *self);
static PyObject *t_floatingtz_richcmp(t_floatingtz *self,
                                      PyObject *other, int op);
static long t_floatingtz_hash(t_floatingtz *self);

static PyObject *t_floatingtz_utcoffset(t_floatingtz *self, PyObject *dt);
static PyObject *t_floatingtz_dst(t_floatingtz *self, PyObject *dt);
static PyObject *t_floatingtz_tzname(t_floatingtz *self, PyObject *dt);

static PyObject *t_floatingtz__getTimezone(t_floatingtz *self, void *data);
static PyObject *t_floatingtz__getTZID(t_floatingtz *self, void *data);

static PyMemberDef t_floatingtz_members[] = {
    { (char *) "tzinfo", T_OBJECT, offsetof(t_floatingtz, tzinfo), 0,
      (char *) "" },
    { NULL, 0, 0, 0, NULL }
};

static PyMethodDef t_floatingtz_methods[] = {
    { "utcoffset", (PyCFunction) t_floatingtz_utcoffset, METH_O, "" },
    { "dst", (PyCFunction) t_floatingtz_dst, METH_O, "" },
    { "tzname", (PyCFunction) t_floatingtz_tzname, METH_O, "" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef t_floatingtz_properties[] = {
    { (char *) "timezone", (getter) t_floatingtz__getTimezone, NULL,
      (char *) "timezone property", NULL },
    { (char *) "tzid", (getter) t_floatingtz__getTZID, NULL,
      (char *) "tzid property", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject FloatingTZType_ = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "icu.FloatingTZ",                   /* tp_name */
    sizeof(t_floatingtz),               /* tp_basicsize */
    0,                                  /* tp_itemsize */
    (destructor) t_floatingtz_dealloc,  /* tp_dealloc */
    0,                                  /* tp_print */
    0,                                  /* tp_getattr */
    0,                                  /* tp_setattr */
    0,                                  /* tp_compare */
    (reprfunc) t_floatingtz_repr,       /* tp_repr */
    0,                                  /* tp_as_number */
    0,                                  /* tp_as_sequence */
    0,                                  /* tp_as_mapping */
    (hashfunc) t_floatingtz_hash,       /* tp_hash  */
    0,                                  /* tp_call */
    (reprfunc) t_floatingtz_str,        /* tp_str */
    0,                                  /* tp_getattro */
    0,                                  /* tp_setattro */
    0,                                  /* tp_as_buffer */
    (Py_TPFLAGS_DEFAULT |
     Py_TPFLAGS_BASETYPE),              /* tp_flags */
    "",                                 /* tp_doc */
    0,                                  /* tp_traverse */
    0,                                  /* tp_clear */
    (richcmpfunc) t_floatingtz_richcmp, /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    0,                                  /* tp_iter */
    0,                                  /* tp_iternext */
    t_floatingtz_methods,               /* tp_methods */
    t_floatingtz_members,               /* tp_members */
    t_floatingtz_properties,            /* tp_getset */
    0,                                  /* tp_base */
    0,                                  /* tp_dict */
    0,                                  /* tp_descr_get */
    0,                                  /* tp_descr_set */
    0,                                  /* tp_dictoffset */
    (initproc) t_floatingtz_init,       /* tp_init */
    0,                                  /* tp_alloc */
    (newfunc) t_floatingtz_new,         /* tp_new */
    0,                                  /* tp_free */
};


static void t_tzinfo_dealloc(t_tzinfo *self)
{
    Py_CLEAR(self->tz);
    Py_TYPE(&self->dt_tzinfo)->tp_free((PyObject *) self);
}

static void t_floatingtz_dealloc(t_floatingtz *self)
{
    Py_CLEAR(self->tzinfo);
    Py_TYPE(&self->dt_tzinfo)->tp_free((PyObject *) self);
}

static PyObject *t_tzinfo_new(PyTypeObject *type,
                              PyObject *args, PyObject *kwds)
{
    t_tzinfo *tzinfo = (t_tzinfo *) type->tp_alloc(type, 0);

    if (tzinfo)
        tzinfo->tz = NULL;

    return (PyObject *) tzinfo;
}

static PyObject *t_floatingtz_new(PyTypeObject *type,
                                  PyObject *args, PyObject *kwds)
{
    t_floatingtz *floatingtz = (t_floatingtz *) type->tp_alloc(type, 0);

    if (floatingtz)
        floatingtz->tzinfo = NULL;

    return (PyObject *) floatingtz;
}

static int t_tzinfo_init(t_tzinfo *self, PyObject *args, PyObject *kwds)
{
    PyObject *tz;

    if (!PyArg_ParseTuple(args, "O", &tz))
        return -1;

    if (!PyObject_TypeCheck(tz, &TimeZoneType_))
    {
        PyErr_SetObject(PyExc_TypeError, tz);
        return -1;
    }

    Py_INCREF(tz);
    Py_XDECREF(self->tz);
    self->tz = (t_timezone *) tz;

    return 0;
}

static int t_floatingtz_init(t_floatingtz *self, PyObject *args, PyObject *kwds)
{
    PyObject *tzinfo = NULL;

    if (!PyArg_ParseTuple(args, "|O", &tzinfo))
        return -1;

    if (tzinfo && !PyObject_TypeCheck(tzinfo, &TZInfoType_))
    {
        PyErr_SetObject(PyExc_TypeError, tzinfo);
        return -1;
    }

    Py_XINCREF(tzinfo);
    Py_XDECREF((PyObject *) self->tzinfo);
    self->tzinfo = (t_tzinfo *) tzinfo;

    return 0;
}

static PyObject *t_tzinfo_repr(t_tzinfo *self)
{
    PyObject *format = PyString_FromString("<ICUtzinfo: %s>");
    PyObject *str = PyObject_Str((PyObject *) self->tz);
#if PY_VERSION_HEX < 0x02040000
    PyObject *args = Py_BuildValue("(O)", str);
#else
    PyObject *args = PyTuple_Pack(1, str);
#endif
    PyObject *repr = PyString_Format(format, args);

    Py_DECREF(args);
    Py_DECREF(str);
    Py_DECREF(format);

    return repr;
}

static PyObject *t_tzinfo_str(t_tzinfo *self)
{
    return PyObject_Str((PyObject *) self->tz);
}

static PyObject *t_floatingtz_repr(t_floatingtz *self)
{
    t_tzinfo *tzinfo = self->tzinfo ? self->tzinfo : _default;
    PyObject *format = PyString_FromString("<FloatingTZ: %s>");
    PyObject *str = PyObject_Str((PyObject *) tzinfo->tz);
#if PY_VERSION_HEX < 0x02040000
    PyObject *args = Py_BuildValue("(O)", str);
#else
    PyObject *args = PyTuple_Pack(1, str);
#endif
    PyObject *repr = PyString_Format(format, args);

    Py_DECREF(args);
    Py_DECREF(str);
    Py_DECREF(format);

    return repr;
}

static PyObject *t_floatingtz_str(t_floatingtz *self)
{
    Py_INCREF(FLOATING_TZNAME);
    return FLOATING_TZNAME;
}

static long t_tzinfo_hash(t_tzinfo *self)
{
    PyObject *str = PyObject_Str((PyObject *) self->tz);
    long hash = PyObject_Hash(str);

    Py_DECREF(str);
    return hash;
}

static long t_floatingtz_hash(t_floatingtz *self)
{
    return PyObject_Hash(FLOATING_TZNAME);
}

static PyObject *t_tzinfo_richcmp(t_tzinfo *self, PyObject *other, int op)
{
    if (PyObject_TypeCheck(other, &TZInfoType_))
    {
        PyObject *s1 = PyObject_Str((PyObject *) self->tz);
        PyObject *s2 = PyObject_Str((PyObject *) ((t_tzinfo *) other)->tz);
        PyObject *result = PyObject_RichCompare(s1, s2, op);

        Py_DECREF(s1);
        Py_DECREF(s2);

        return result;
    }

    if (PyObject_TypeCheck(other, &FloatingTZType_))
    {
        PyObject *s1 = PyObject_Str((PyObject *) self->tz);
        PyObject *result = PyObject_RichCompare(s1, FLOATING_TZNAME, op);

        Py_DECREF(s1);

        return result;
    }

    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

static PyObject *t_floatingtz_richcmp(t_floatingtz *self,
                                      PyObject *other, int op)
{
    if (PyObject_TypeCheck(other, &FloatingTZType_))
    {
        t_tzinfo *tzi1 = self->tzinfo;
        t_tzinfo *tzi2 = ((t_floatingtz *) other)->tzinfo;

        return PyObject_RichCompare((PyObject *) (tzi1 ? tzi1 : _default),
                                    (PyObject *) (tzi2 ? tzi2 : _default),
                                    op);
    }

    if (PyObject_TypeCheck(other, &TZInfoType_))
    {
        PyObject *s2 = PyObject_Str((PyObject *) ((t_tzinfo *) other)->tz);
        PyObject *result = PyObject_RichCompare(FLOATING_TZNAME, s2, op);

        Py_DECREF(s2);

        return result;
    }

    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

static PyObject *t_tzinfo__resetDefault(PyTypeObject *cls)
{
    PyObject *tz = wrap_TimeZone(TimeZone::createDefault());

    if (tz)
    {
#if PY_VERSION_HEX < 0x02040000
        PyObject *args = Py_BuildValue("(O)", tz);
#else
        PyObject *args = PyTuple_Pack(1, tz);
#endif
        PyObject *tzinfo = PyObject_Call((PyObject *) &TZInfoType_, args, NULL);

        Py_DECREF(args);
        Py_DECREF(tz);

        if (tzinfo)
        {
            if (!PyObject_TypeCheck(tzinfo, &TZInfoType_))
            {
                PyErr_SetObject(PyExc_TypeError, tzinfo);
                return NULL;
            }

            Py_XDECREF((PyObject *) _default);
            _default = (t_tzinfo *) tzinfo;

            Py_RETURN_NONE;
        }
    }

    return NULL;
}

static PyObject *t_tzinfo_getFloating(PyTypeObject *cls)
{
    if (_floating)
    {
        Py_INCREF((PyObject *) _floating);
        return (PyObject *) _floating;
    }

    Py_RETURN_NONE;
}

static PyObject *t_tzinfo_getDefault(PyTypeObject *cls)
{
    if (_default)
    {
        Py_INCREF((PyObject *) _default);
        return (PyObject *) _default;
    }

    Py_RETURN_NONE;
}

static PyObject *t_tzinfo_setDefault(PyTypeObject *cls, PyObject *arg)
{
    if (!PyObject_TypeCheck(arg, &TZInfoType_))
    {
        PyErr_SetObject(PyExc_TypeError, arg);
        return NULL;
    }

    PyObject *prev = (PyObject *) _default;

    Py_INCREF(arg);
    _default = (t_tzinfo *) arg;

    if (prev)
        return prev;

    Py_RETURN_NONE;
}

static PyObject *t_tzinfo_getInstances(PyTypeObject *cls)
{
    Py_INCREF(_instances);
    return _instances;
}

static PyObject *t_tzinfo_getInstance(PyTypeObject *cls, PyObject *id)
{
    PyObject *instance = PyDict_GetItem(_instances, id);

    if (instance)
    {
        Py_INCREF(instance);
        return instance;
    }

    int cmp = PyObject_RichCompareBool(id, FLOATING_TZNAME, Py_EQ);
    if (cmp == -1)
        return NULL;
    if (cmp)
        instance = t_tzinfo_getFloating(cls);
    else
    {
        PyObject *tz = t_timezone_createTimeZone(&TimeZoneType_, id);

        if (!tz)
            return NULL;

#if PY_VERSION_HEX < 0x02040000
        PyObject *args = Py_BuildValue("(O)", tz);
#else
        PyObject *args = PyTuple_Pack(1, tz);
#endif
        instance = PyObject_Call((PyObject *) &TZInfoType_, args, NULL);
        Py_DECREF(args);
        Py_DECREF(tz);
    }

    if (instance)
        PyDict_SetItem(_instances, id, instance);

    return instance;
}

static double _udate(PyObject *dt)
{
    PyObject *result = PyObject_CallMethodObjArgs(dt, toordinal_NAME, NULL);

    if (!result)
        return 0.0;

#if PY_MAJOR_VERSION >= 3
    unsigned long ordinal = PyLong_AsUnsignedLong(result);
#else
    unsigned long ordinal = PyInt_AS_LONG(result);
#endif

    Py_DECREF(result);
    return ((ordinal - 719163) * 86400.0 +
            PyDateTime_DATE_GET_HOUR(dt) * 3600.0 +
            PyDateTime_DATE_GET_MINUTE(dt) * 60.0 +
            PyDateTime_DATE_GET_SECOND(dt) +
            PyDateTime_DATE_GET_MICROSECOND(dt) / 1e6) * 1000.0;
}

static PyObject *t_tzinfo_utcoffset(t_tzinfo *self, PyObject *dt)
{
    PyObject *weekday = PyObject_CallMethodObjArgs(dt, weekday_NAME, NULL);
    if (!weekday)
        return NULL;

    // python's MINYEAR is 1
    int era = GregorianCalendar::AD;
    int year = PyDateTime_GET_YEAR(dt);

    // python's month is 1-based, 1 is January
    // ICU's month is 0-based, 0 is January
    int month = PyDateTime_GET_MONTH(dt) - 1;
    int day = PyDateTime_GET_DAY(dt);

    // python's weekday is 0-based, 0 is Monday
    // ICU's dayofweek is 1-based, 1 is Sunday
    int dayofweek = ((PyInt_AsLong(weekday) + 1) % 7) + 1;
    Py_DECREF(weekday);

    int millis = (int) ((PyDateTime_DATE_GET_HOUR(dt) * 3600.0 +
                         PyDateTime_DATE_GET_MINUTE(dt) * 60.0 +
                         PyDateTime_DATE_GET_SECOND(dt) +
                         PyDateTime_DATE_GET_MICROSECOND(dt) / 1e6) * 1000.0);
    int offset;

    STATUS_CALL(offset = self->tz->object->getOffset(era, year, month, day,
                                                     dayofweek, millis,
                                                     status));

    PyObject *args = PyTuple_New(2);
    PyObject *result;

    PyTuple_SET_ITEM(args, 0, PyInt_FromLong(0));
    PyTuple_SET_ITEM(args, 1, PyInt_FromLong(offset / 1000));
    result = PyObject_Call((PyObject *) datetime_deltaType, args, NULL);
    Py_DECREF(args);

    return result;
}

static PyObject *t_tzinfo_dst(t_tzinfo *self, PyObject *dt)
{
    UDate date = _udate(dt);
    int raw, dst;

    if (date == 0.0 && PyErr_Occurred())
        return NULL;

    STATUS_CALL(self->tz->object->getOffset(date, 1, raw, dst, status));

    PyObject *args = PyTuple_New(2);
    PyObject *result;

    PyTuple_SET_ITEM(args, 0, PyInt_FromLong(0));
    PyTuple_SET_ITEM(args, 1, PyInt_FromLong(dst / 1000));
    result = PyObject_Call((PyObject *) datetime_deltaType, args, NULL);
    Py_DECREF(args);

    return result;
}

static PyObject *t_tzinfo_tzname(t_tzinfo *self, PyObject *dt)
{
    return PyObject_Str((PyObject *) self->tz);
}

static PyObject *t_tzinfo__getTimezone(t_tzinfo *self, void *data)
{
    Py_INCREF(self->tz);
    return (PyObject *) self->tz;
}

static PyObject *t_tzinfo__getTZID(t_tzinfo *self, void *data)
{
    return PyObject_Str((PyObject *) self);
}

static PyObject *t_floatingtz_utcoffset(t_floatingtz *self, PyObject *dt)
{
    return t_tzinfo_utcoffset(self->tzinfo ? self->tzinfo : _default, dt);
}

static PyObject *t_floatingtz_dst(t_floatingtz *self, PyObject *dt)
{
    return t_tzinfo_dst(self->tzinfo ? self->tzinfo : _default, dt);
}

static PyObject *t_floatingtz_tzname(t_floatingtz *self, PyObject *dt)
{
    Py_INCREF(FLOATING_TZNAME);
    return FLOATING_TZNAME;
}

static PyObject *t_floatingtz__getTimezone(t_floatingtz *self, void *data)
{
    t_tzinfo *tzinfo = self->tzinfo ? self->tzinfo : _default;

    Py_INCREF(tzinfo->tz);
    return (PyObject *) tzinfo->tz;
}

static PyObject *t_floatingtz__getTZID(t_floatingtz *self, void *data)
{
    Py_INCREF(FLOATING_TZNAME);
    return FLOATING_TZNAME;
}


void _init_tzinfo(PyObject *m)
{
#if PY_VERSION_HEX > 0x02040000 && !defined(PYPY_VERSION)
    PyDateTime_IMPORT;

    datetime_tzinfoType = PyDateTimeAPI->TZInfoType;
    datetime_deltaType = PyDateTimeAPI->DeltaType;
#else
    PyObject *datetime = PyImport_ImportModule("datetime");

    if (datetime)
    {
        datetime_tzinfoType = (PyTypeObject *)
            PyObject_GetAttrString(datetime, "tzinfo");
        datetime_deltaType = (PyTypeObject *)
            PyObject_GetAttrString(datetime, "timedelta");
        Py_DECREF(datetime);
    }
#endif

    _instances = PyDict_New();
    TZInfoType_.tp_base = datetime_tzinfoType;
    FloatingTZType_.tp_base = datetime_tzinfoType;

    if (PyType_Ready(&TZInfoType_) >= 0 &&
        PyType_Ready(&FloatingTZType_) >= 0)
    {
        if (m)
        {
            Py_INCREF(&TZInfoType_);
            PyModule_AddObject(m, "ICUtzinfo", (PyObject *) &TZInfoType_);

            Py_INCREF(&FloatingTZType_);
            PyModule_AddObject(m, "FloatingTZ", (PyObject *) &FloatingTZType_);

            FLOATING_TZNAME = PyString_FromString("World/Floating");
            toordinal_NAME = PyString_FromString("toordinal");
            weekday_NAME = PyString_FromString("weekday");

            Py_INCREF(FLOATING_TZNAME);
            PyModule_AddObject(m, "FLOATING_TZNAME", FLOATING_TZNAME);

            t_tzinfo__resetDefault(&TZInfoType_);

            PyObject *args = PyTuple_New(0);
            PyObject *floating =
                PyObject_Call((PyObject *) &FloatingTZType_, args, NULL);

            if (floating && PyObject_TypeCheck(floating, &FloatingTZType_))
                _floating = (t_tzinfo *) floating;
            else
                Py_XDECREF(floating);
            Py_DECREF(args);
        }
    }
}
