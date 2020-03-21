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

using EditsIterator = Edits::Iterator;

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

DECLARE_STRUCT(CaseMap, t_casemap, UNone, abstract_init, NULL)

/* Edits */

class t_edits : public _wrapper {
public:
    Edits *object;
};

static int t_edits_init(t_edits *self, PyObject *args, PyObject *kwds);

static PyObject *t_edits_reset(t_edits *self);
static PyObject *t_edits_addUnchanged(t_edits *self, PyObject *arg);
static PyObject *t_edits_addReplace(t_edits *self, PyObject *args);
static PyObject *t_edits_lengthDelta(t_edits *self);
static PyObject *t_edits_hasChanges(t_edits *self);
static PyObject *t_edits_getCoarseChangesIterator(t_edits *self);
static PyObject *t_edits_getCoarseIterator(t_edits *self);
static PyObject *t_edits_getFineChangesIterator(t_edits *self);
static PyObject *t_edits_getFineIterator(t_edits *self);
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
static PyObject *t_edits_mergeAndAppend(t_edits *self, PyObject *args);
static PyObject *t_edits_numberOfChanges(t_edits *self);
#endif

static PyMethodDef t_edits_methods[] = {
    DECLARE_METHOD(t_edits, reset, METH_NOARGS),
    DECLARE_METHOD(t_edits, addUnchanged, METH_O),
    DECLARE_METHOD(t_edits, addReplace, METH_VARARGS),
    DECLARE_METHOD(t_edits, lengthDelta, METH_NOARGS),
    DECLARE_METHOD(t_edits, hasChanges, METH_NOARGS),
    DECLARE_METHOD(t_edits, getCoarseChangesIterator, METH_NOARGS),
    DECLARE_METHOD(t_edits, getCoarseIterator, METH_NOARGS),
    DECLARE_METHOD(t_edits, getFineChangesIterator, METH_NOARGS),
    DECLARE_METHOD(t_edits, getFineIterator, METH_NOARGS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
    DECLARE_METHOD(t_edits, mergeAndAppend, METH_VARARGS),
    DECLARE_METHOD(t_edits, numberOfChanges, METH_NOARGS),
#endif
    { NULL, NULL, 0, NULL }
};

DECLARE_STRUCT(Edits, t_edits, Edits, t_edits_init, NULL)

/* EditsIterator */

class t_editsiterator : public _wrapper {
public:
    EditsIterator *object;
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
static int t_editsiterator_init(t_editsiterator *self, PyObject *args,
                                PyObject *kwds);
#endif

static PyObject *t_editsiterator_findSourceIndex(
    t_editsiterator *self, PyObject *arg);

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
static PyObject *t_editsiterator_findDestinationIndex(
    t_editsiterator *self, PyObject *arg);
static PyObject *t_editsiterator_destinationIndexFromSourceIndex(
    t_editsiterator *self, PyObject *arg);
static PyObject *t_editsiterator_sourceIndexFromdestinationIndex(
    t_editsiterator *self, PyObject *arg);
#endif

static PyObject *t_editsiterator__hasChange(
    t_editsiterator *self, void *closure);
static PyObject *t_editsiterator__newLength(
    t_editsiterator *self, void *closure);
static PyObject *t_editsiterator__oldLength(
    t_editsiterator *self, void *closure);
static PyObject *t_editsiterator__sourceIndex(
    t_editsiterator *self, void *closure);
static PyObject *t_editsiterator__destinationIndex(
    t_editsiterator *self, void *closure);
static PyObject *t_editsiterator__replacementIndex(
    t_editsiterator *self, void *closure);

static PyGetSetDef t_editsiterator_properties[] = {
    { (char *) "hasChange",
      (getter) t_editsiterator__hasChange,
      NULL,
      (char *) "hasChange property", NULL },
    { (char *) "oldLength",
      (getter) t_editsiterator__oldLength,
      NULL,
      (char *) "oldLength property", NULL },
    { (char *) "newLength",
      (getter) t_editsiterator__newLength,
      NULL,
      (char *) "newLength property", NULL },
    { (char *) "sourceIndex",
      (getter) t_editsiterator__sourceIndex,
      NULL,
      (char *) "sourceIndex property", NULL },
    { (char *) "destinationIndex",
      (getter) t_editsiterator__destinationIndex,
      NULL,
      (char *) "destinationIndex property", NULL },
    { (char *) "replacementIndex",
      (getter) t_editsiterator__replacementIndex,
      NULL,
      (char *) "replacementIndex property", NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyMethodDef t_editsiterator_methods[] = {
    DECLARE_METHOD(t_editsiterator, findSourceIndex, METH_O),
#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
    DECLARE_METHOD(t_editsiterator, findDestinationIndex, METH_O),
    DECLARE_METHOD(t_editsiterator, destinationIndexFromSourceIndex, METH_O),
    DECLARE_METHOD(t_editsiterator, sourceIndexFromdestinationIndex, METH_O),
#endif
    { NULL, NULL, 0, NULL }
};

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)
DECLARE_STRUCT(EditsIterator, t_editsiterator, EditsIterator,
               t_editsiterator_init, NULL)
#else
DECLARE_STRUCT(EditsIterator, t_editsiterator, EditsIterator,
               abstract_init, NULL)
#endif

PyObject *wrap_EditsIterator(const EditsIterator &iterator)
{
    return wrap_EditsIterator(new EditsIterator(iterator), T_OWNED);
}

/* CaseMap */

static PyObject *t_casemap_toLower(PyTypeObject *type, PyObject *args)
{
    Locale *locale;
    UnicodeString *u, _u;
    int32_t options;
    PyObject *edits;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "SO", &EditsType_, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    NULL, 0, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "PSO", TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    locale->getBaseName(), 0, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iSO", &EditsType_, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                NULL, options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    NULL, options, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PiS", TYPE_CLASSID(Locale),
                       &locale, &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

      case 4:
        if (!parseArgs(args, "PiSO", TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toLower(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toLower(
                    locale->getBaseName(), options, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

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
    PyObject *edits;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "SO", &EditsType_, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                NULL, 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    NULL, 0, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "PSO", TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), 0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    locale->getBaseName(), 0, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iSO", &EditsType_, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                NULL, options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    NULL, options, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PiS", TYPE_CLASSID(Locale),
                       &locale, &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

      case 4:
        if (!parseArgs(args, "PiSO", TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toUpper(
                locale->getBaseName(), options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toUpper(
                    locale->getBaseName(), options, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

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
    PyObject *edits;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "SO", &EditsType_, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, 0, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PS", TYPE_CLASSID(Locale), &locale, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "PSO", TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), 0, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "PSO", TYPE_CLASSID(BreakIterator), &EditsType_,
                       &iter, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, 0, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, 0, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iSO", &EditsType_, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, options, NULL, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, options, NULL, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "PPS",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(BreakIterator),
                       &locale, &iter, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "PPSO",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(BreakIterator),
                       &EditsType_, &locale, &iter, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), 0, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), 0, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "PiSO",
                       TYPE_CLASSID(Locale), &EditsType_,
                       &locale, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), options, NULL,
                u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), options, NULL,
                    u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        if (!parseArgs(args, "iPSO",
                       TYPE_CLASSID(BreakIterator), &EditsType_,
                       &options, &iter, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                NULL, options, iter, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    NULL, options, iter, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

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

            if (U_SUCCESS(status))
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

      case 5:
        if (!parseArgs(args, "PiPSO",
                       TYPE_CLASSID(Locale), TYPE_CLASSID(BreakIterator),
                       &EditsType_, &locale, &options, &iter, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::toTitle(
                locale->getBaseName(), options, iter,
                u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::toTitle(
                    locale->getBaseName(), options, iter,
                    u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

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
    PyObject *edits;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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
        if (!parseArgs(args, "SO", &EditsType_, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                0, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::fold(
                    0, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }

        if (!parseArgs(args, "iS", &options, &u, &_u))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, NULL, status);

            if (U_SUCCESS(status))
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

      case 3:
        if (!parseArgs(args, "iSO", &EditsType_, &options, &u, &_u, &edits))
        {
            Buffer dest(u->length() + 8);
            UErrorCode status = U_ZERO_ERROR;
            int32_t size = CaseMap::fold(
                options, u->getBuffer(), u->length(),
                dest.buffer, dest.size, ((t_edits *) edits)->object, status);

            if (U_SUCCESS(status))
                return PyUnicode_FromUnicodeString(dest.buffer, size);

            if (status == U_BUFFER_OVERFLOW_ERROR) {
                Buffer dest(size);

                STATUS_CALL(CaseMap::fold(
                    options, u->getBuffer(), u->length(),
                    dest.buffer, size, ((t_edits *) edits)->object, status));

                return PyUnicode_FromUnicodeString(dest.buffer, size);
            }

            return ICUException(status).reportError();
        }
        break;
    }

    return PyErr_SetArgsError(type, "fold", args);
}

/* Edits */

static int t_edits_init(t_edits *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new Edits();
        self->flags = T_OWNED;
        break;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

static PyObject *t_edits_reset(t_edits *self)
{
    self->object->reset();
    Py_RETURN_NONE;
}

static PyObject *t_edits_addUnchanged(t_edits *self, PyObject *arg)
{
    int length;

    if (!parseArg(arg, "i", &length))
    {
        self->object->addUnchanged(length);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "addUnchanged", arg);
}

static PyObject *t_edits_addReplace(t_edits *self, PyObject *args)
{
    int oldLength, newLength;

    if (!parseArgs(args, "ii", &oldLength, &newLength))
    {
        self->object->addReplace(oldLength, newLength);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "addReplace", args);
}

static PyObject *t_edits_lengthDelta(t_edits *self)
{
    return PyInt_FromLong(self->object->lengthDelta());
}

static PyObject *t_edits_hasChanges(t_edits *self)
{
    Py_RETURN_BOOL(self->object->hasChanges());
}

static PyObject *t_edits_getCoarseChangesIterator(t_edits *self)
{
    return wrap_EditsIterator(self->object->getCoarseChangesIterator());
}

static PyObject *t_edits_getCoarseIterator(t_edits *self)
{
    return wrap_EditsIterator(self->object->getCoarseIterator());
}

static PyObject *t_edits_getFineChangesIterator(t_edits *self)
{
    return wrap_EditsIterator(self->object->getFineChangesIterator());
}

static PyObject *t_edits_getFineIterator(t_edits *self)
{
    return wrap_EditsIterator(self->object->getFineIterator());
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

static PyObject *t_edits_mergeAndAppend(t_edits *self, PyObject *args)
{
    PyObject *ab, *bc;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "OO", &EditsType_, &EditsType_, &ab, &bc))
        {
            STATUS_CALL(self->object->mergeAndAppend(
                *((t_edits *) ab)->object, *((t_edits *) bc)->object, status));
            Py_RETURN_NONE;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "mergeAndAppend", args);
}

static PyObject *t_edits_numberOfChanges(t_edits *self)
{
    return PyInt_FromLong(self->object->numberOfChanges());
}

#endif


/* EditsIterator */

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

static int t_editsiterator_init(t_editsiterator *self,
                                PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new EditsIterator();
        self->flags = T_OWNED;
        break;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }

    if (self->object)
        return 0;

    return -1;
}

#endif

static PyObject *t_editsiterator_findSourceIndex(
    t_editsiterator *self, PyObject *arg)
{
    int index;

    if (!parseArg(arg, "i", &index))
    {
        bool found;
        STATUS_CALL(found = self->object->findSourceIndex(index, status));

        Py_RETURN_BOOL(found);
    }

    return PyErr_SetArgsError((PyObject *) self, "findSourceIndex", arg);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(60, 0, 0)

static PyObject *t_editsiterator_findDestinationIndex(
    t_editsiterator *self, PyObject *arg)
{
    int index;

    if (!parseArg(arg, "i", &index))
    {
        bool found;
        STATUS_CALL(found = self->object->findDestinationIndex(index, status));

        Py_RETURN_BOOL(found);
    }

    return PyErr_SetArgsError((PyObject *) self, "findDestinationIndex", arg);
}

static PyObject *t_editsiterator_destinationIndexFromSourceIndex(
    t_editsiterator *self, PyObject *arg)
{
    int index;

    if (!parseArg(arg, "i", &index))
    {
        STATUS_CALL(index = self->object->destinationIndexFromSourceIndex(
            index, status));

        return PyInt_FromLong(index);
    }

    return PyErr_SetArgsError(
        (PyObject *) self, "destinationIndexFromSourceIndex", arg);
}

static PyObject *t_editsiterator_sourceIndexFromdestinationIndex(
    t_editsiterator *self, PyObject *arg)
{
    int index;

    if (!parseArg(arg, "i", &index))
    {
        STATUS_CALL(index = self->object->sourceIndexFromDestinationIndex(
            index, status));

        return PyInt_FromLong(index);
    }

    return PyErr_SetArgsError(
        (PyObject *) self, "sourceIndexFromDestinationIndex", arg);
}

#endif

static PyObject *t_editsiterator__hasChange(
    t_editsiterator *self, void *closure)
{
    Py_RETURN_BOOL(self->object->hasChange());
}

static PyObject *t_editsiterator__newLength(
    t_editsiterator *self, void *closure)
{
    return PyInt_FromLong(self->object->newLength());
}

static PyObject *t_editsiterator__oldLength(
    t_editsiterator *self, void *closure)
{
    return PyInt_FromLong(self->object->oldLength());
}

static PyObject *t_editsiterator__sourceIndex(
    t_editsiterator *self, void *closure)
{
    return PyInt_FromLong(self->object->sourceIndex());
}

static PyObject *t_editsiterator__destinationIndex(
    t_editsiterator *self, void *closure)
{
    return PyInt_FromLong(self->object->destinationIndex());
}

static PyObject *t_editsiterator__replacementIndex(
    t_editsiterator *self, void *closure)
{
    return PyInt_FromLong(self->object->replacementIndex());
}

static PyObject *t_editsiterator_iter_next(t_editsiterator *self)
{
    UBool more;

    STATUS_CALL(more = self->object->next(status));

    if (!more)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return Py_BuildValue(
        "Oiiiii",
        self->object->hasChange() ? Py_True : Py_False,
        (int) self->object->oldLength(),
        (int) self->object->newLength(),
        (int) self->object->sourceIndex(),
        (int) self->object->destinationIndex(),
        (int) self->object->replacementIndex());
}

#endif

void _init_casemap(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(59, 0, 0)
    EditsIteratorType_.tp_getset = t_editsiterator_properties;
    EditsIteratorType_.tp_iter = (getiterfunc) PyObject_SelfIter;
    EditsIteratorType_.tp_iternext = (iternextfunc) t_editsiterator_iter_next;

    INSTALL_STRUCT(CaseMap, m);
    INSTALL_STRUCT(Edits, m);
    INSTALL_STRUCT(EditsIterator, m);
#endif
}
