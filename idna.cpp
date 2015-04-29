/* ====================================================================
 * Copyright (c) 2004-2015 Open Source Applications Foundation.
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

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "idna.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= VERSION_HEX(55, 1, 0)

/* IDNAInfo */

class t_idnainfo : public _wrapper {
public:
    UIDNAInfo *object;
    UIDNAInfo info;
};

static int t_idnainfo_init(t_idnainfo *self, PyObject *args, PyObject *kwds);
static PyObject *t_idnainfo_isTransitionalDifferent(t_idnainfo *self);
static PyObject *t_idnainfo_errors(t_idnainfo *self);

static PyMethodDef t_idnainfo_methods[] = {
    DECLARE_METHOD(t_idnainfo, isTransitionalDifferent, METH_NOARGS),
    DECLARE_METHOD(t_idnainfo, errors, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static void t_idnainfo_dealloc(t_idnainfo *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(IDNAInfo, t_idnainfo, UIDNAInfo, t_idnainfo_init,
               t_idnainfo_dealloc);

/* IDNA */

class t_idna : public _wrapper {
public:
    UIDNA *object;
};

typedef int32_t (*idna_fn)(
    const UIDNA *idna, const UChar *text, int32_t len,
    UChar *dest, int capacity, UIDNAInfo *info,
    UErrorCode *status);

static int t_idna_init(t_idna *self, PyObject *args, PyObject *kwds);
static PyObject *t_idna_labelToASCII(t_idna *self, PyObject *args);
static PyObject *t_idna_labelToUnicode(t_idna *self, PyObject *args);
static PyObject *t_idna_nameToASCII(t_idna *self, PyObject *args);
static PyObject *t_idna_nameToUnicode(t_idna *self, PyObject *args);

static PyMethodDef t_idna_methods[] = {
    DECLARE_METHOD(t_idna, labelToASCII, METH_VARARGS),
    DECLARE_METHOD(t_idna, labelToUnicode, METH_VARARGS),
    DECLARE_METHOD(t_idna, nameToASCII, METH_VARARGS),
    DECLARE_METHOD(t_idna, nameToUnicode, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_idna_dealloc(t_idna *self)
{
    if (self->object != NULL)
    {
        uidna_close(self->object);
        self->object = NULL;
    }

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(IDNA, t_idna, UIDNA, t_idna_init, t_idna_dealloc);


/* IDNAInfo */

static int t_idnainfo_init(t_idnainfo *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        memset(&self->info, 0, sizeof(UIDNAInfo));
        self->info.size = sizeof(UIDNAInfo);

        self->object = &self->info;
        self->flags = T_OWNED;
        return 0;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
}

static PyObject *t_idnainfo_isTransitionalDifferent(t_idnainfo *self)
{
    Py_RETURN_BOOL(self->info.isTransitionalDifferent);
}

static PyObject *t_idnainfo_errors(t_idnainfo *self)
{
    return PyInt_FromLong(self->info.errors);
}

/* IDNA */

static int t_idna_init(t_idna *self, PyObject *args, PyObject *kwds)
{
    uint32_t options;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = uidna_openUTS46(UIDNA_DEFAULT, &status));
        self->flags = T_OWNED;
        return 0;

      case 1:
        if (!parseArgs(args, "i", &options))
        {
            INT_STATUS_CALL(self->object = uidna_openUTS46(options, &status));
            self->flags = T_OWNED;
            return 0;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
}

static PyObject *apply(idna_fn fn, const char *fn_name,
                       t_idna *self, PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;
    t_idnainfo *infoArg;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            const size_t len = u->length();
            const size_t capacity = len * 4 + 32;
            UErrorCode status = U_ZERO_ERROR;
            UChar *dest = new UChar[capacity];
            UIDNAInfo info = UIDNA_INFO_INITIALIZER;
            PyObject *result;
            size_t size;

            if (!dest)
            {
                PyErr_SetNone(PyExc_MemoryError);
                return NULL;
            }

            size = (*fn)(self->object, u->getBuffer(), len, dest, capacity,
                         &info, &status);

            if (U_FAILURE(status))
            {
                delete[] dest;
                return ICUException(status).reportError();
            }

            result = PyUnicode_FromUnicodeString(dest, size);
            delete[] dest;

            return result;
        }
        break;

      case 2:
        if (!parseArgs(args, "SO", &IDNAInfoType_, &u, &_u, &infoArg))
        {
            const size_t len = u->length();
            const size_t capacity = len * 4 + 32;
            UErrorCode status = U_ZERO_ERROR;
            UChar *dest = new UChar[capacity];
            PyObject *result;
            size_t size;

            if (!dest)
            {
                PyErr_SetNone(PyExc_MemoryError);
                return NULL;
            }

            size = (*fn)(self->object, u->getBuffer(), len, dest, capacity,
                         infoArg->object, &status);

            if (U_FAILURE(status))
            {
                delete[] dest;
                return ICUException(status).reportError();
            }

            result = PyUnicode_FromUnicodeString(dest, size);
            delete[] dest;

            return result;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, fn_name, args);
}

static PyObject *t_idna_labelToASCII(t_idna *self, PyObject *args)
{
    return apply(uidna_labelToASCII, "labelToASCII", self, args);
}

static PyObject *t_idna_labelToUnicode(t_idna *self, PyObject *args)
{
    return apply(uidna_labelToUnicode, "labelToUnicode", self, args);
}

static PyObject *t_idna_nameToASCII(t_idna *self, PyObject *args)
{
    return apply(uidna_nameToASCII, "nameToASCII", self, args);
}

static PyObject *t_idna_nameToUnicode(t_idna *self, PyObject *args)
{
    return apply(uidna_nameToUnicode, "nameToUnicode", self, args);
}

#endif

void _init_idna(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(55, 1, 0)
    INSTALL_STRUCT(IDNAInfo, m);
    INSTALL_STRUCT(IDNA, m);

    INSTALL_ENUM(IDNAInfo, "ERROR_EMPTY_LABEL", UIDNA_ERROR_EMPTY_LABEL);
    INSTALL_ENUM(IDNAInfo, "ERROR_LABEL_TOO_LONG", UIDNA_ERROR_LABEL_TOO_LONG);
    INSTALL_ENUM(IDNAInfo, "ERROR_DOMAIN_NAME_TOO_LONG",
                 UIDNA_ERROR_DOMAIN_NAME_TOO_LONG);
    INSTALL_ENUM(IDNAInfo, "ERROR_LEADING_HYPHEN", UIDNA_ERROR_LEADING_HYPHEN);
    INSTALL_ENUM(IDNAInfo, "ERROR_TRAILING_HYPHEN",
                 UIDNA_ERROR_TRAILING_HYPHEN);
    INSTALL_ENUM(IDNAInfo, "ERROR_HYPHEN_3_4", UIDNA_ERROR_HYPHEN_3_4);
    INSTALL_ENUM(IDNAInfo, "ERROR_LEADING_COMBINING_MARK",
                 UIDNA_ERROR_LEADING_COMBINING_MARK);
    INSTALL_ENUM(IDNAInfo, "ERROR_DISALLOWED", UIDNA_ERROR_DISALLOWED);
    INSTALL_ENUM(IDNAInfo, "ERROR_PUNYCODE", UIDNA_ERROR_PUNYCODE);
    INSTALL_ENUM(IDNAInfo, "ERROR_LABEL_HAS_DOT", UIDNA_ERROR_LABEL_HAS_DOT);
    INSTALL_ENUM(IDNAInfo, "ERROR_INVALID_ACE_LABEL",
                 UIDNA_ERROR_INVALID_ACE_LABEL);
    INSTALL_ENUM(IDNAInfo, "ERROR_BIDI", UIDNA_ERROR_BIDI);
    INSTALL_ENUM(IDNAInfo, "ERROR_CONTEXTJ", UIDNA_ERROR_CONTEXTJ);
    INSTALL_ENUM(IDNAInfo, "ERROR_CONTEXTO_PUNCTUATION",
                 UIDNA_ERROR_CONTEXTO_PUNCTUATION);
    INSTALL_ENUM(IDNAInfo, "ERROR_CONTEXTO_DIGITS",
                 UIDNA_ERROR_CONTEXTO_DIGITS);

    INSTALL_ENUM(IDNA, "DEFAULT", UIDNA_DEFAULT);
    INSTALL_ENUM(IDNA, "USE_STD3_RULES", UIDNA_USE_STD3_RULES);
    INSTALL_ENUM(IDNA, "CHECK_BIDI", UIDNA_CHECK_BIDI);
    INSTALL_ENUM(IDNA, "CHECK_CONTEXTJ", UIDNA_CHECK_CONTEXTJ);
    INSTALL_ENUM(IDNA, "CHECK_NONTRANSITIONAL_TO_ASCII",
                 UIDNA_NONTRANSITIONAL_TO_ASCII);
    INSTALL_ENUM(IDNA, "CHECK_NONTRANSITIONAL_TO_UNICODE",
                 UIDNA_NONTRANSITIONAL_TO_UNICODE);
    INSTALL_ENUM(IDNA, "CHECK_CONTEXT0", UIDNA_CHECK_CONTEXTO);
#endif
}
