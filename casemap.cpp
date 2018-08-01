/* ====================================================================
 * Copyright (c) 2004-2018 Open Source Applications Foundation.
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
#include "casemap.h"
#include "iterators.h"
#include "locale.h"
#include "macros.h"


/* CaseMap */

#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)

class t_casemap : public _wrapper {
public:
    UNone *object;
};

static PyObject *t_casemap_toLower(PyTypeObject *type, PyObject *args);
static PyObject *t_casemap_toUpper(PyTypeObject *type, PyObject *args);
static PyObject *t_casemap_toTitle(PyTypeObject *type, PyObject *args);
static PyObject *t_casemap_fold(PyTypeObject *type, PyObject *args);

static PyMethodDef t_casemap_methods[] = {
    DECLARE_METHOD(t_casemap, toLower, METH_CLASS | METH_VARARGS),
    DECLARE_METHOD(t_casemap, toUpper, METH_CLASS | METH_VARARGS),
    DECLARE_METHOD(t_casemap, toTitle, METH_CLASS | METH_VARARGS),
    DECLARE_METHOD(t_casemap, fold, METH_CLASS | METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_STRUCT(CaseMap, t_casemap, UNone, abstract_init, NULL);


/* CaseMap */

static PyObject *t_casemap_toLower(PyTypeObject *type, PyObject *args)
{
    Locale *locale;
    UnicodeString *u, _u;
    int32_t options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    NULL, 0, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 2:
        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    locale->getBaseName(), 0, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iS", &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                NULL, options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    NULL, options, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 3:
        if (!parseArgs(args, "PiS", TYPE_CLASSID(Locale),
                       &locale, &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    locale->getBaseName(), options, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;
    }

    return PyErr_SetArgsError(type, "toLower", args);
}

static PyObject *t_casemap_toUpper(PyTypeObject *type, PyObject *args)
{
    Locale *locale;
    UnicodeString *u, _u;
    int32_t options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    NULL, 0, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 2:
        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    locale->getBaseName(), 0, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iS", &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                NULL, options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    NULL, options, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 3:
        if (!parseArgs(args, "PiS", TYPE_CLASSID(Locale),
                       &locale, &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    locale->getBaseName(), options, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;
    }

    return PyErr_SetArgsError(type, "toUpper", args);
}

static PyObject *t_casemap_toTitle(PyTypeObject *type, PyObject *args)
{
    Locale *locale;
    BreakIterator *iter;
    UnicodeString *u, _u;
    int32_t options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, 0, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 2:
        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), 0, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "PS", TYPE_CLASSID(BreakIterator), &iter, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, 0, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, 0, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iS", &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, options, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, options, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 3:
        if (!parseArgs(args, "PPS",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(BreakIterator),
                       &locale, &iter, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), 0, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "PiS",
                       TYPE_CLASSID(Locale),
                       &locale, &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), options, NULL,
                u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), options, NULL,
                    u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iPS",
                       TYPE_CLASSID(BreakIterator),
                       &options, &iter, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, options, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, options, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        break;

      case 4:
        if (!parseArgs(args, "PiPS",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(BreakIterator),
                       &locale, &options, &iter, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), options, iter,
                u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), options, iter,
                    u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;
    }

    return PyErr_SetArgsError(type, "toTitle", args);
}

static PyObject *t_casemap_fold(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    int32_t options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::fold(
                    0, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;

      case 2:
        if (!parseArgs(args, "iS", &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (!U_FAILURE(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::fold(
                    options, u->getBuffer(), u->length(),
                    dest.buffer, size, NULL, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;
    }

    return PyErr_SetArgsError(type, "fold", args);
}

#endif

void _init_casemap(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
    INSTALL_STRUCT(CaseMap, m);
#endif
}
