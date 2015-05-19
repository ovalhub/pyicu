/* ====================================================================
 * Copyright (c) 2007-2010 Open Source Applications Foundation.
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
#include "charset.h"
#include "macros.h"


/* CharsetDetector */

class t_charsetdetector : public _wrapper {
public:
    UCharsetDetector *object;
    PyObject *text;
};

static int t_charsetdetector_init(t_charsetdetector *self,
                                  PyObject *args, PyObject *kwds);
static PyObject *t_charsetdetector_setText(t_charsetdetector *self,
                                           PyObject *arg);
static PyObject *t_charsetdetector_setDeclaredEncoding(t_charsetdetector *self,
                                                       PyObject *arg);
static PyObject *t_charsetdetector_detect(t_charsetdetector *self);
static PyObject *t_charsetdetector_detectAll(t_charsetdetector *self);
static PyObject *t_charsetdetector_enableInputFilter(t_charsetdetector *self,
                                                     PyObject *arg);
static PyObject *t_charsetdetector_isInputFilterEnabled(t_charsetdetector *self);
static PyObject *t_charsetdetector_getAllDetectableCharsets(t_charsetdetector *self);

static PyMethodDef t_charsetdetector_methods[] = {
    DECLARE_METHOD(t_charsetdetector, setText, METH_O),
    DECLARE_METHOD(t_charsetdetector, setDeclaredEncoding, METH_O),
    DECLARE_METHOD(t_charsetdetector, detect, METH_NOARGS),
    DECLARE_METHOD(t_charsetdetector, detectAll, METH_NOARGS),
    DECLARE_METHOD(t_charsetdetector, enableInputFilter, METH_O),
    DECLARE_METHOD(t_charsetdetector, isInputFilterEnabled, METH_NOARGS),
    DECLARE_METHOD(t_charsetdetector, getAllDetectableCharsets, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static void t_charsetdetector_dealloc(t_charsetdetector *self)
{
    if (self->object)
    {
        ucsdet_close(self->object);
        self->object = NULL;
    }
    Py_CLEAR(self->text);

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(CharsetDetector, t_charsetdetector, UCharsetDetector,
               t_charsetdetector_init, t_charsetdetector_dealloc);


/* CharsetMatch */

class t_charsetmatch : public _wrapper {
public:
    UCharsetMatch *object;
    t_charsetdetector *detector;
};

static PyObject *t_charsetmatch_getName(t_charsetmatch *self);
static PyObject *t_charsetmatch_getConfidence(t_charsetmatch *self);
static PyObject *t_charsetmatch_getLanguage(t_charsetmatch *self);

static PyMethodDef t_charsetmatch_methods[] = {
    DECLARE_METHOD(t_charsetmatch, getName, METH_NOARGS),
    DECLARE_METHOD(t_charsetmatch, getConfidence, METH_NOARGS),
    DECLARE_METHOD(t_charsetmatch, getLanguage, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static void t_charsetmatch_dealloc(t_charsetmatch *self)
{
    if (self->object) /* not owned */
    {
        self->object = NULL;
        Py_CLEAR(self->detector);
    }

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(CharsetMatch, t_charsetmatch, UCharsetMatch,
               abstract_init, t_charsetmatch_dealloc);


/* CharsetDetector */

static int t_charsetdetector_init(t_charsetdetector *self,
                                  PyObject *args, PyObject *kwds)
{
    const char *text;
    charsArg encoding;
    int textSize;

    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = ucsdet_open(&status));
        break;

      case 1:
        if (!parseArgs(args, "k", &text, &textSize))
        {
            INT_STATUS_CALL(self->object = ucsdet_open(&status));
            INT_STATUS_CALL(ucsdet_setText(self->object, text, textSize,
                                           &status));
            self->text = PyTuple_GetItem(args, 0);
            Py_INCREF(self->text);
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      case 2:
        if (!parseArgs(args, "kn", &text, &textSize, &encoding))
        {
            INT_STATUS_CALL(self->object = ucsdet_open(&status));
            INT_STATUS_CALL(ucsdet_setText(self->object, text,
                                           textSize, &status));
            INT_STATUS_CALL(ucsdet_setDeclaredEncoding(self->object, encoding,
                                                       -1, &status));
            self->text = PyTuple_GetItem(args, 0);
            Py_INCREF(self->text);
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

static PyObject *t_charsetdetector_setText(t_charsetdetector *self,
                                           PyObject *arg)
{
    const char *text;
    int size;

    if (!parseArg(arg, "k", &text, &size))
    {
        /* ref'd */
        STATUS_CALL(ucsdet_setText(self->object, text, size, &status));

        Py_INCREF(arg);
        Py_XDECREF(self->text);
        self->text = arg;

        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setText", arg);
}

static PyObject *t_charsetdetector_setDeclaredEncoding(t_charsetdetector *self,
                                                       PyObject *arg)
{
    const char *encoding;
    int size;

    if (!parseArg(arg, "k", &encoding, &size))
    {
        /* copied */
        STATUS_CALL(ucsdet_setDeclaredEncoding(self->object, encoding, size,
                                               &status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setDeclaredEncoding", arg);
}

static PyObject *t_charsetdetector_detect(t_charsetdetector *self)
{
    const UCharsetMatch *match;
    PyObject *result;

    STATUS_CALL(match = ucsdet_detect(self->object, &status));

    result = wrap_CharsetMatch((UCharsetMatch *) match, 0);
    if (result)
    {
        ((t_charsetmatch *) result)->detector = self;
        Py_INCREF(self);
    }

    return result;
}

static PyObject *t_charsetdetector_detectAll(t_charsetdetector *self)
{
    const UCharsetMatch **matches;
    PyObject *result;
    int found = 0;

    STATUS_CALL(matches = ucsdet_detectAll(self->object, &found, &status));
    result = PyTuple_New(found);

    for (int i = 0; i < found; i++) {
        const UCharsetMatch *match = matches[i];
        PyObject *m = wrap_CharsetMatch((UCharsetMatch *) match, 0);

        if (m)
        {
            ((t_charsetmatch *) m)->detector = self;
            Py_INCREF(self);
            PyTuple_SET_ITEM(result, i, m);
        }
        else
        {
            Py_DECREF(result);
            return NULL;
        }
    }

    return result;
}

static PyObject *t_charsetdetector_enableInputFilter(t_charsetdetector *self,
                                                     PyObject *arg)
{
    UBool filter;

    if (!parseArg(arg, "B", &filter))
    {
        UBool previous = ucsdet_enableInputFilter(self->object, filter);
        Py_RETURN_BOOL(previous);
    }

    return PyErr_SetArgsError((PyObject *) self, "enableInputFilter", arg);
}

static PyObject *t_charsetdetector_isInputFilterEnabled(t_charsetdetector *self)
{
    UBool filter = ucsdet_isInputFilterEnabled(self->object);
    Py_RETURN_BOOL(filter);
}

static PyObject *t_charsetdetector_getAllDetectableCharsets(t_charsetdetector *self)
{
    UEnumeration *_charsets;

    STATUS_CALL(_charsets = ucsdet_getAllDetectableCharsets(self->object,
                                                            &status));

    return wrap_StringEnumeration(new UStringEnumeration(_charsets), T_OWNED);
}


/* CharsetMatch */

static PyObject *t_charsetmatch_getName(t_charsetmatch *self)
{
    const char *name;

    STATUS_CALL(name = ucsdet_getName(self->object, &status));
    return PyString_FromString(name);
}

static PyObject *t_charsetmatch_getConfidence(t_charsetmatch *self)
{
    int confidence;

    STATUS_CALL(confidence = ucsdet_getConfidence(self->object, &status));
    return PyInt_FromLong(confidence);
}

static PyObject *t_charsetmatch_getLanguage(t_charsetmatch *self)
{
    const char *language;

    STATUS_CALL(language = ucsdet_getLanguage(self->object, &status));
    return PyString_FromString(language);
}

static PyObject *t_charsetmatch_str(t_charsetmatch *self)
{
    if (self->detector && self->detector->text)
    {
        UErrorCode status = U_ZERO_ERROR;
        int size = PyBytes_GET_SIZE(self->detector->text);
        UChar *buf = new UChar[size];
        PyObject *u;

        if (!buf)
        {
            PyErr_SetNone(PyExc_MemoryError);
            return NULL;
        }

        size = ucsdet_getUChars(self->object, buf, size, &status);
        if (U_FAILURE(status))
        {
            delete[] buf;
            return ICUException(status).reportError();
        }
        
        u = PyUnicode_FromUnicodeString(buf, size);
        delete[] buf;

        return u;
    }

    return PyUnicode_FromUnicode(NULL, 0);
}


void _init_charset(PyObject *m)
{
    CharsetMatchType_.tp_str = (reprfunc) t_charsetmatch_str;

    INSTALL_STRUCT(CharsetDetector, m);
    INSTALL_STRUCT(CharsetMatch, m);
}
