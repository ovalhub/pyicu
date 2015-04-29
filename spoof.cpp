/* ====================================================================
 * Copyright (c) 2014-2014 Open Source Applications Foundation.
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
#include "spoof.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= 0x04020000

DECLARE_CONSTANTS_TYPE(USpoofChecks);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
DECLARE_CONSTANTS_TYPE(URestrictionLevel);
#endif

/* SpoofChecker */

class t_spoofchecker : public _wrapper {
public:
    USpoofChecker *object;
};

static int t_spoofchecker_init(t_spoofchecker *self, PyObject *args, PyObject *kwds);
static PyObject *t_spoofchecker_setChecks(t_spoofchecker *self, PyObject *arg);
static PyObject *t_spoofchecker_getChecks(t_spoofchecker *self);
static PyObject *t_spoofchecker_setAllowedLocales(t_spoofchecker *self, PyObject *arg);
static PyObject *t_spoofchecker_getAllowedLocales(t_spoofchecker *self);
static PyObject *t_spoofchecker_setAllowedUnicodeSet(t_spoofchecker *self, PyObject *arg);
static PyObject *t_spoofchecker_getAllowedUnicodeSet(t_spoofchecker *self);
static PyObject *t_spoofchecker_check(t_spoofchecker *self, PyObject *arg);
static PyObject *t_spoofchecker_areConfusable(t_spoofchecker *self, PyObject *args);
static PyObject *t_spoofchecker_getSkeleton(t_spoofchecker *self, PyObject *args);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
static PyObject *t_spoofchecker_setRestrictionLevel(t_spoofchecker *self, PyObject *arg);
static PyObject *t_spoofchecker_getRestrictionLevel(t_spoofchecker *self);
static PyObject *t_spoofchecker_getInclusionUnicodeSet(PyTypeObject *type);
static PyObject *t_spoofchecker_getRecommendedUnicodeSet(PyTypeObject *type);
#endif

static PyMethodDef t_spoofchecker_methods[] = {
    DECLARE_METHOD(t_spoofchecker, setChecks, METH_O),
    DECLARE_METHOD(t_spoofchecker, getChecks, METH_NOARGS),
    DECLARE_METHOD(t_spoofchecker, setAllowedLocales, METH_O),
    DECLARE_METHOD(t_spoofchecker, getAllowedLocales, METH_NOARGS),
    DECLARE_METHOD(t_spoofchecker, setAllowedUnicodeSet, METH_O),
    DECLARE_METHOD(t_spoofchecker, getAllowedUnicodeSet, METH_NOARGS),
    DECLARE_METHOD(t_spoofchecker, check, METH_O),
    DECLARE_METHOD(t_spoofchecker, areConfusable, METH_VARARGS),
    DECLARE_METHOD(t_spoofchecker, getSkeleton, METH_VARARGS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    DECLARE_METHOD(t_spoofchecker, setRestrictionLevel, METH_O),
    DECLARE_METHOD(t_spoofchecker, getRestrictionLevel, METH_NOARGS),
    DECLARE_METHOD(t_spoofchecker, getInclusionUnicodeSet, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_spoofchecker, getRecommendedUnicodeSet, METH_NOARGS | METH_CLASS),
#endif
    { NULL, NULL, 0, NULL }
};

static void t_spoofchecker_dealloc(t_spoofchecker *self)
{
    if (self->object != NULL)
    {
        uspoof_close(self->object);
        self->object = NULL;
    }

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(SpoofChecker, t_spoofchecker, USpoofChecker,
               t_spoofchecker_init, t_spoofchecker_dealloc);


/* SpoofChecker */

static int t_spoofchecker_init(t_spoofchecker *self,
                               PyObject *args, PyObject *kwds)
{
    USpoofChecker *usc = NULL;
    t_spoofchecker *sc = NULL;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(usc = uspoof_open(&status));
        self->object = usc;
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "O", &SpoofCheckerType_, &sc))
        {
            INT_STATUS_CALL(usc = uspoof_clone(sc->object, &status));
            self->object = usc;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object != NULL)
        return 0;

    return -1;
}

static PyObject *t_spoofchecker_setChecks(t_spoofchecker *self, PyObject *arg)
{
    int32_t checks = PyInt_AsLong(arg);

    if (PyErr_Occurred())
        return NULL;

    STATUS_CALL(uspoof_setChecks(self->object, (uint32_t) checks, &status));
    Py_RETURN_NONE;
}

static PyObject *t_spoofchecker_getChecks(t_spoofchecker *self)
{
    uint32_t checks;

    STATUS_CALL(checks = uspoof_getChecks(self->object, &status));
    return PyInt_FromLong((int32_t) checks);
}

static PyObject *t_spoofchecker_setAllowedLocales(t_spoofchecker *self,
                                                  PyObject *arg)
{
    char *localesList;

    if (!parseArg(arg, "c", &localesList))
    {
        STATUS_CALL(uspoof_setAllowedLocales(self->object, localesList,
                                             &status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAllowedLocales", arg);
}

static PyObject *t_spoofchecker_getAllowedLocales(t_spoofchecker *self)
{
    const char *localesList;

    STATUS_CALL(localesList = uspoof_getAllowedLocales(self->object, &status));

    return PyString_FromString(localesList);
}

static PyObject *t_spoofchecker_setAllowedUnicodeSet(t_spoofchecker *self,
                                                     PyObject *arg)
{
    const UnicodeSet *set;
    
    if (!parseArg(arg, "P", TYPE_CLASSID(UnicodeSet), &set))
    {
        STATUS_CALL(uspoof_setAllowedUnicodeSet(self->object, set, &status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setAllowedUnicodeSet", arg);
}

static PyObject *t_spoofchecker_getAllowedUnicodeSet(t_spoofchecker *self)
{
    const UnicodeSet *set;

    STATUS_CALL(set = uspoof_getAllowedUnicodeSet(self->object, &status));
    return wrap_UnicodeSet(new UnicodeSet(*set), T_OWNED);
}

static PyObject *t_spoofchecker_check(t_spoofchecker *self, PyObject *arg)
{
    UnicodeString *u, _u;
    int32_t checks;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(checks = uspoof_check(self->object, u->getBuffer(),
                                          u->length(), NULL, &status));
        return PyInt_FromLong(checks);
    }

    return PyErr_SetArgsError((PyObject *) self, "check", arg);
}

static PyObject *t_spoofchecker_areConfusable(t_spoofchecker *self,
                                              PyObject *args)
{
    UnicodeString *u0, _u0;
    UnicodeString *u1, _u1;
    int32_t checks;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "SS", &u0, &_u0, &u1, &_u1))
        {
            STATUS_CALL(checks = uspoof_areConfusable(
                            self->object, u0->getBuffer(), u0->length(),
                            u1->getBuffer(), u1->length(), &status));
            return PyInt_FromLong(checks);
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "areConfusable", args);
}

static PyObject *t_spoofchecker_getSkeleton(t_spoofchecker *self,
                                            PyObject *args)
{
    UnicodeString *u, _u;
    int32_t type;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "iS", &type, &u, &_u))
        {
            class Buffer {
            public:
                explicit Buffer(int32_t len) :
                    size(len), buffer(u.getBuffer(len)) {}
                ~Buffer() {
                    u.releaseBuffer(0);
                }
                UnicodeString u;
                int32_t size;
                UChar *buffer;
            };

            const int32_t len = u->length();
            Buffer dest(len + 32);

            UErrorCode status = U_ZERO_ERROR;
            int32_t size =
                uspoof_getSkeleton(self->object, type, u->getBuffer(), len,
                                   dest.buffer, dest.size, &status);
            
            switch (status) {
              case 0:
                return PyUnicode_FromUnicodeString(dest.buffer, size);

              case U_BUFFER_OVERFLOW_ERROR: {
                  Buffer dest(size);

                  STATUS_CALL(size = uspoof_getSkeleton(
                                  self->object, type, u->getBuffer(), len,
                                  dest.buffer, dest.size, &status));

                  return PyUnicode_FromUnicodeString(dest.buffer, size);
              }

              default:
                return ICUException(status).reportError();
            }
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "getSkeleton", args);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)

static PyObject *t_spoofchecker_setRestrictionLevel(t_spoofchecker *self,
                                                    PyObject *arg)
{
    int32_t level = PyInt_AsLong(arg);

    if (PyErr_Occurred())
        return NULL;

    uspoof_setRestrictionLevel(self->object, (URestrictionLevel) level);
    Py_RETURN_NONE;
}

static PyObject *t_spoofchecker_getRestrictionLevel(t_spoofchecker *self)
{
    URestrictionLevel level = uspoof_getRestrictionLevel(self->object);
    return PyInt_FromLong((int32_t) level);
}

static PyObject *t_spoofchecker_getInclusionUnicodeSet(PyTypeObject *type)
{
    const UnicodeSet *set;

    STATUS_CALL(set = uspoof_getInclusionUnicodeSet(&status));
    if (!set->isFrozen())
        const_cast<UnicodeSet *>(set)->freeze();  // documented to be frozen

    return wrap_UnicodeSet(const_cast<UnicodeSet *>(set), 0);  // owned by icu
}

static PyObject *t_spoofchecker_getRecommendedUnicodeSet(PyTypeObject *type)
{
    const UnicodeSet *set;

    STATUS_CALL(set = uspoof_getRecommendedUnicodeSet(&status));
    if (!set->isFrozen())
        const_cast<UnicodeSet *>(set)->freeze();  // documented to be frozen

    return wrap_UnicodeSet(const_cast<UnicodeSet *>(set), 0);  // owned by icu
}

#endif  /* 51 */

#endif  /* 4.2 */


void _init_spoof(PyObject *m)
{
#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_CONSTANTS_TYPE(USpoofChecks, m);

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_CONSTANTS_TYPE(URestrictionLevel, m);
#endif

    INSTALL_STRUCT(SpoofChecker, m);

    INSTALL_ENUM(USpoofChecks, "SINGLE_SCRIPT_CONFUSABLE", USPOOF_SINGLE_SCRIPT_CONFUSABLE);
    INSTALL_ENUM(USpoofChecks, "MIXED_SCRIPT_CONFUSABLE", USPOOF_MIXED_SCRIPT_CONFUSABLE);
    INSTALL_ENUM(USpoofChecks, "WHOLE_SCRIPT_CONFUSABLE", USPOOF_WHOLE_SCRIPT_CONFUSABLE);
    INSTALL_ENUM(USpoofChecks, "ANY_CASE", USPOOF_ANY_CASE);
    INSTALL_ENUM(USpoofChecks, "INVISIBLE", USPOOF_INVISIBLE);
    INSTALL_ENUM(USpoofChecks, "CHAR_LIMIT", USPOOF_CHAR_LIMIT);

#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(USpoofChecks, "ALL_CHECKS", USPOOF_ALL_CHECKS);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_ENUM(USpoofChecks, "RESTRICTION_LEVEL", USPOOF_RESTRICTION_LEVEL);
    INSTALL_ENUM(USpoofChecks, "MIXED_NUMBERS", USPOOF_MIXED_NUMBERS);
    INSTALL_ENUM(USpoofChecks, "AUX_INFO", USPOOF_AUX_INFO);
#else
    INSTALL_ENUM(USpoofChecks, "SINGLE_SCRIPT", USPOOF_SINGLE_SCRIPT);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_ENUM(URestrictionLevel, "ASCII", USPOOF_ASCII);
    INSTALL_ENUM(URestrictionLevel, "HIGHLY_RESTRICTIVE", USPOOF_HIGHLY_RESTRICTIVE);
    INSTALL_ENUM(URestrictionLevel, "MODERATELY_RESTRICTIVE", USPOOF_MODERATELY_RESTRICTIVE);
    INSTALL_ENUM(URestrictionLevel, "MINIMALLY_RESTRICTIVE", USPOOF_MINIMALLY_RESTRICTIVE);
    INSTALL_ENUM(URestrictionLevel, "UNRESTRICTIVE", USPOOF_UNRESTRICTIVE);
#endif  /* 51 */

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
    INSTALL_ENUM(URestrictionLevel, "SINGLE_SCRIPT_RESTRICTIVE", USPOOF_SINGLE_SCRIPT_RESTRICTIVE);
    INSTALL_ENUM(URestrictionLevel, "RESTRICTION_LEVEL_MASK", USPOOF_RESTRICTION_LEVEL_MASK);
#endif

#endif  /* 4.2 */
}
