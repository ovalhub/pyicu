/* ====================================================================
 * Copyright (c) 2020 Open Source Applications Foundation.
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

#include "common.h"
#include "structmember.h"

#include "bases.h"
#include "bidi.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UBiDiDirection)
DECLARE_CONSTANTS_TYPE(UBiDiReorderingMode)
DECLARE_CONSTANTS_TYPE(UBiDiReorderingOption)

#if U_ICU_VERSION_HEX >= VERSION_HEX(58, 0, 0)
DECLARE_CONSTANTS_TYPE(UBiDiMirroring)
DECLARE_CONSTANTS_TYPE(UBiDiOrder)
#endif


/* Bidi */

class t_bidi : public _wrapper {
public:
    UBiDi *object;
    PyObject *text;
    PyObject *parent;
#if U_ICU_VERSION_HEX >= 0x04080000
    PyObject *prologue;
    PyObject *epilogue;
#endif
};

static int t_bidi_init(t_bidi *self, PyObject *args, PyObject *kwds);
static PyObject *t_bidi_setPara(t_bidi *self, PyObject *args);
static PyObject *t_bidi_getText(t_bidi *self);
static PyObject *t_bidi__getText(t_bidi *self, void *closure);
#if U_ICU_VERSION_HEX >= 0x04080000
static PyObject *t_bidi_setContext(t_bidi *self, PyObject *args);
static PyObject *t_bidi__getPrologue(t_bidi *self, void *closure);
static PyObject *t_bidi__getEpilogue(t_bidi *self, void *closure);
#endif
static PyObject *t_bidi_setLine(t_bidi *self, PyObject *args);
static PyObject *t_bidi__getParent(t_bidi *self, void *closure);
static PyObject *t_bidi_getLength(t_bidi *self);
static PyObject *t_bidi_getProcessedLength(t_bidi *self);
static PyObject *t_bidi_getResultLength(t_bidi *self);
static PyObject *t_bidi_getParaLevel(t_bidi *self);
static PyObject *t_bidi_getLevelAt(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getLevels(t_bidi *self);
static PyObject *t_bidi_countParagraphs(t_bidi *self);
static PyObject *t_bidi_getParagraph(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getParagraphByIndex(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_countRuns(t_bidi *self);
static PyObject *t_bidi_getLogicalRun(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getVisualRun(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getLogicalIndex(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getVisualIndex(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getLogicalMap(t_bidi *self);
static PyObject *t_bidi_getVisualMap(t_bidi *self);
static PyObject *t_bidi_reorderLogical(PyTypeObject *type, PyObject *arg);
static PyObject *t_bidi_reorderVisual(PyTypeObject *type, PyObject *arg);
static PyObject *t_bidi_invertMap(PyTypeObject *type, PyObject *arg);
static PyObject *t_bidi_setInverse(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_isInverse(t_bidi *self);
static PyObject *t_bidi_orderParagraphsLTR(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_isOrderParagraphsLTR(t_bidi *self);
static PyObject *t_bidi_setReorderingMode(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getReorderingMode(t_bidi *self);
static PyObject *t_bidi_setReorderingOptions(t_bidi *self, PyObject *arg);
static PyObject *t_bidi_getReorderingOptions(t_bidi *self);
static PyObject *t_bidi_getDirection(t_bidi *self);
static PyObject *t_bidi_getBaseDirection(PyTypeObject *type, PyObject *arg);
static PyObject *t_bidi_writeReordered(t_bidi *self, PyObject *args);
static PyObject *t_bidi_writeReverse(PyTypeObject *type, PyObject *args);

static PyGetSetDef t_bidi_properties[] = {
    { (char *) "text",
      (getter) t_bidi__getText,
      NULL,
      (char *) "text property", NULL },
    { (char *) "parent",
      (getter) t_bidi__getParent,
      NULL,
      (char *) "parent property", NULL },
#if U_ICU_VERSION_HEX >= 0x04080000
    { (char *) "prologue",
      (getter) t_bidi__getPrologue,
      NULL,
      (char *) "prologue property", NULL },
    { (char *) "epilogue",
      (getter) t_bidi__getEpilogue,
      NULL,
      (char *) "epilogue property", NULL },
#endif
    { NULL, NULL, NULL, NULL, NULL }
};

static PyMethodDef t_bidi_methods[] = {
    DECLARE_METHOD(t_bidi, setPara, METH_VARARGS),
    DECLARE_METHOD(t_bidi, getText, METH_NOARGS),
#if U_ICU_VERSION_HEX >= 0x04080000
    DECLARE_METHOD(t_bidi, setContext, METH_VARARGS),
#endif
    DECLARE_METHOD(t_bidi, setLine, METH_VARARGS),
    DECLARE_METHOD(t_bidi, getLength, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getProcessedLength, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getResultLength, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getParaLevel, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getLevelAt, METH_O),
    DECLARE_METHOD(t_bidi, getLevels, METH_NOARGS),
    DECLARE_METHOD(t_bidi, countParagraphs, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getParagraph, METH_O),
    DECLARE_METHOD(t_bidi, getParagraphByIndex, METH_O),
    DECLARE_METHOD(t_bidi, countRuns, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getLogicalRun, METH_O),
    DECLARE_METHOD(t_bidi, getVisualRun, METH_O),
    DECLARE_METHOD(t_bidi, getLogicalIndex, METH_O),
    DECLARE_METHOD(t_bidi, getVisualIndex, METH_O),
    DECLARE_METHOD(t_bidi, getLogicalMap, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getVisualMap, METH_NOARGS),
    DECLARE_METHOD(t_bidi, reorderLogical, METH_O | METH_CLASS),
    DECLARE_METHOD(t_bidi, reorderVisual, METH_O | METH_CLASS),
    DECLARE_METHOD(t_bidi, invertMap, METH_O | METH_CLASS),
    DECLARE_METHOD(t_bidi, setInverse, METH_O),
    DECLARE_METHOD(t_bidi, isInverse, METH_NOARGS),
    DECLARE_METHOD(t_bidi, orderParagraphsLTR, METH_O),
    DECLARE_METHOD(t_bidi, isOrderParagraphsLTR, METH_NOARGS),
    DECLARE_METHOD(t_bidi, setReorderingMode, METH_O),
    DECLARE_METHOD(t_bidi, getReorderingMode, METH_NOARGS),
    DECLARE_METHOD(t_bidi, setReorderingOptions, METH_O),
    DECLARE_METHOD(t_bidi, getReorderingOptions, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getDirection, METH_NOARGS),
    DECLARE_METHOD(t_bidi, getBaseDirection, METH_O | METH_CLASS),
    DECLARE_METHOD(t_bidi, writeReordered, METH_VARARGS),
    DECLARE_METHOD(t_bidi, writeReverse, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_bidi_dealloc(t_bidi *self)
{
    ubidi_close(self->object); self->object = NULL;

    Py_XDECREF(self->text); self->text = NULL;
    Py_XDECREF(self->parent); self->parent = NULL;
#if U_ICU_VERSION_HEX >= 0x04080000
    Py_XDECREF(self->prologue); self->prologue = NULL;
    Py_XDECREF(self->epilogue); self->epilogue = NULL;
#endif

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(Bidi, t_bidi, UBiDi, t_bidi_init, t_bidi_dealloc)


#if U_ICU_VERSION_HEX >= VERSION_HEX(58, 0, 0)

/* BidiTransform */

class t_biditransform : public _wrapper {
public:
    UBiDiTransform *object;
};

static int t_biditransform_init(t_biditransform *self,
                                PyObject *args, PyObject *kwds);
static PyObject *t_biditransform_transform(t_biditransform *self,
                                           PyObject *args);

static PyMethodDef t_biditransform_methods[] = {
    DECLARE_METHOD(t_biditransform, transform, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_biditransform_dealloc(t_biditransform *self)
{
    ubiditransform_close(self->object); self->object = NULL;
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(BidiTransform, t_biditransform, UBiDiTransform,
               t_biditransform_init, t_biditransform_dealloc)

#endif // >= 58


/* Bidi */

static int t_bidi_init(t_bidi *self, PyObject *args, PyObject *kwds)
{
    int maxLength, maxRunCount;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = ubidi_open();
        self->text = NULL;
        self->parent = NULL;
#if U_ICU_VERSION_HEX >= 0x04080000
        self->prologue = self->epilogue = NULL;
#endif
        self->flags = T_OWNED;
        return 0;

      case 1:
        if (!parseArgs(args, "i", &maxLength))
        {
            INT_STATUS_CALL(self->object = ubidi_openSized(
                maxLength, 0, &status));
            self->text = NULL;
            self->parent = NULL;
#if U_ICU_VERSION_HEX >= 0x04080000
            self->prologue = self->epilogue = NULL;
#endif
            self->flags = T_OWNED;
            return 0;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;

      case 2:
        if (!parseArgs(args, "ii", &maxLength, &maxRunCount))
        {
            INT_STATUS_CALL(self->object = ubidi_openSized(
                maxLength, maxRunCount, &status));
            self->text = NULL;
            self->parent = NULL;
#if U_ICU_VERSION_HEX >= 0x04080000
            self->prologue = self->epilogue = NULL;
#endif
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

static PyObject *t_bidi_setPara(t_bidi *self, PyObject *args)
{
    UnicodeString *u;
    PyObject *obj;
    int level;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "V", &u, &obj))
        {
            STATUS_CALL(ubidi_setPara(self->object, u->getBuffer(), u->length(),
                                      UBIDI_DEFAULT_LTR, NULL, &status));
            Py_INCREF(obj); Py_XDECREF(self->text);
            self->text = obj;

#if U_ICU_VERSION_HEX >= 0x04080000
            // a context is not "remembered" after call to ubidi_setPara()
            Py_XDECREF(self->prologue); self->prologue = NULL;
            Py_XDECREF(self->epilogue); self->epilogue = NULL;
#endif

            Py_RETURN_NONE;
        }
        break;

      case 2:
        if (!parseArgs(args, "Vi", &u, &obj, &level))
        {
            STATUS_CALL(ubidi_setPara(self->object, u->getBuffer(), u->length(),
                                      level, NULL, &status));
            Py_INCREF(obj); Py_XDECREF(self->text);
            self->text = obj;

#if U_ICU_VERSION_HEX >= 0x04080000
            // a context is not "remembered" after call to ubidi_setPara()
            Py_XDECREF(self->prologue); self->prologue = NULL;
            Py_XDECREF(self->epilogue); self->epilogue = NULL;
#endif

            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "setPara", args);
}

static PyObject *t_bidi_getText(t_bidi *self)
{
    if (self->text != NULL)
    {
        Py_INCREF(self->text);
        return self->text;
    }

    Py_RETURN_NONE;
}

static PyObject *t_bidi__getText(t_bidi *self, void *closure)
{
    return t_bidi_getText(self);
}

#if U_ICU_VERSION_HEX >= 0x04080000

static PyObject *t_bidi_setContext(t_bidi *self, PyObject *args)
{
    UnicodeString *u, *v;
    PyObject *u_obj, *v_obj;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(ubidi_setContext(self->object, NULL, 0, NULL, 0, &status));

        Py_XDECREF(self->prologue); self->prologue = NULL;
        Py_XDECREF(self->epilogue); self->epilogue = NULL;

        Py_RETURN_NONE;

      case 1:
        if (!parseArgs(args, "V", &u, &u_obj))
        {
            STATUS_CALL(ubidi_setContext(
                self->object, u->getBuffer(), u->length(), NULL, 0, &status));

            Py_INCREF(u_obj); Py_XDECREF(self->prologue);
            self->prologue = u_obj;
            Py_XDECREF(self->epilogue); self->epilogue = NULL;

            Py_RETURN_NONE;
        }
        break;

      case 2:
        if (!parseArgs(args, "VV", &u, &u_obj, &v, &v_obj))
        {
            STATUS_CALL(ubidi_setContext(
                self->object, u->getBuffer(), u->length(),
                v->getBuffer(), v->length(), &status));

            Py_INCREF(u_obj); Py_XDECREF(self->prologue);
            self->prologue = u_obj;
            Py_INCREF(v_obj); Py_XDECREF(self->epilogue);
            self->epilogue = v_obj;

            Py_RETURN_NONE;
        }
        if (!parseArgs(args, "NV", &u_obj, &v, &v_obj))
        {
            STATUS_CALL(ubidi_setContext(
                self->object, NULL, 0, v->getBuffer(), v->length(), &status));

            Py_XDECREF(self->prologue); self->prologue = NULL;
            Py_INCREF(v_obj); Py_XDECREF(self->epilogue);
            self->epilogue = v_obj;

            Py_RETURN_NONE;
        }
        if (!parseArgs(args, "VN", &u, &u_obj, &v_obj))
        {
            STATUS_CALL(ubidi_setContext(
                self->object, u->getBuffer(), u->length(), NULL, 0, &status));

            Py_INCREF(u_obj); Py_XDECREF(self->prologue);
            self->prologue = u_obj;
            Py_XDECREF(self->epilogue); self->epilogue = NULL;

            Py_RETURN_NONE;
        }
        if (!parseArgs(args, "NN", &u_obj, &v_obj))
        {
            STATUS_CALL(ubidi_setContext(
                self->object, NULL, 0, NULL, 0, &status));

            Py_XDECREF(self->prologue); self->prologue = NULL;
            Py_XDECREF(self->epilogue); self->epilogue = NULL;

            Py_RETURN_NONE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "setContext", args);
}

static PyObject *t_bidi__getPrologue(t_bidi *self, void *closure)
{
    if (self->prologue != NULL)
    {
        Py_INCREF(self->prologue);
        return self->prologue;
    }

    Py_RETURN_NONE;
}

static PyObject *t_bidi__getEpilogue(t_bidi *self, void *closure)
{
    if (self->epilogue != NULL)
    {
        Py_INCREF(self->epilogue);
        return self->epilogue;
    }

    Py_RETURN_NONE;
}

#endif  // ICU >= 4.8

static PyObject *t_bidi_setLine(t_bidi *self, PyObject *args)
{
    int start, limit;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "ii", &start, &limit) &&
            limit - start > 0 &&
            limit - start <= ubidi_getLength(self->object))
        {
            UBiDi *line;

            STATUS_CALL(line = ubidi_openSized(limit - start, 0, &status));
            STATUS_CALL(
                {
                    ubidi_setLine(self->object, start, limit, line, &status);
                    if (U_FAILURE(status))
                        ubidi_close(line);
                });

            PyObject *result = wrap_Bidi(line, T_OWNED);

            if (result != NULL)
            {
                t_bidi *bidi = (t_bidi *) result;
                const UChar *text = ubidi_getText(line);
                int length = ubidi_getLength(line);
                UnicodeString *u = new UnicodeString(0, text, length);

                if (u == NULL)
                {
                    Py_DECREF(result);  // closes line too
                    return PyErr_NoMemory();
                }

                bidi->parent = (PyObject *) self; Py_INCREF(bidi->parent);
                bidi->text = wrap_UnicodeString(u, T_OWNED);

#if U_ICU_VERSION_HEX >= 0x04080000
                bidi->prologue = bidi->epilogue = NULL;
#endif
            }
            else
                ubidi_close(line);

            return result;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "setLine", args);
}

static PyObject *t_bidi__getParent(t_bidi *self, void *closure)
{
    if (self->parent != NULL)
    {
        Py_INCREF(self->parent);
        return self->parent;
    }

    Py_RETURN_NONE;
}

static PyObject *t_bidi_getLength(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getLength(self->object));
}

static PyObject *t_bidi_getProcessedLength(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getProcessedLength(self->object));
}

static PyObject *t_bidi_getResultLength(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getResultLength(self->object));
}

static PyObject *t_bidi_getParaLevel(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getParaLevel(self->object));
}

static PyObject *t_bidi_getLevelAt(t_bidi *self, PyObject *arg)
{
    int charIndex;

    if (!parseArg(arg, "i", &charIndex))
    {
        UBiDiLevel level = ubidi_getLevelAt(self->object, charIndex);
        return PyInt_FromLong(level);
    }

    return PyErr_SetArgsError((PyObject *) self, "getLevelAt", arg);
}

static PyObject *t_bidi_getLevels(t_bidi *self)
{
    const UBiDiLevel *levels;
    STATUS_CALL(levels = ubidi_getLevels(self->object, &status));

    int length = ubidi_getProcessedLength(self->object);
    PyObject *result = PyTuple_New(length);

    if (result != NULL)
    {
        for (int i = 0; i < length; ++i)
            PyTuple_SET_ITEM(result, i, PyInt_FromLong(levels[i]));
    }

    return result;
}

static PyObject *t_bidi_countParagraphs(t_bidi *self)
{
    return PyInt_FromLong(ubidi_countParagraphs(self->object));
}

static PyObject *t_bidi_getParagraph(t_bidi *self, PyObject *arg)
{
    int charIndex;

    if (!parseArg(arg, "i", &charIndex))
    {
        int paraIndex, start, limit;
        UBiDiLevel level;

        STATUS_CALL(paraIndex = ubidi_getParagraph(
            self->object, charIndex, &start, &limit, &level, &status));

        return Py_BuildValue("(iiii)", start, limit, (int) level, paraIndex);
    }

    return PyErr_SetArgsError((PyObject *) self, "getParagraph", arg);
}

static PyObject *t_bidi_getParagraphByIndex(t_bidi *self, PyObject *arg)
{
    int paraIndex;

    if (!parseArg(arg, "i", &paraIndex))
    {
        int start, limit;
        UBiDiLevel level;

        STATUS_CALL(ubidi_getParagraphByIndex(
            self->object, paraIndex, &start, &limit, &level, &status));

        return Py_BuildValue("(iii)", start, limit, (int) level);
    }

    return PyErr_SetArgsError((PyObject *) self, "getParagraphByIndex", arg);
}

static PyObject *t_bidi_countRuns(t_bidi *self)
{
    int runs;
    STATUS_CALL(runs = ubidi_countRuns(self->object, &status));

    return PyInt_FromLong(runs);
}

static PyObject *t_bidi_getLogicalRun(t_bidi *self, PyObject *arg)
{
    int logicalPosition;

    if (!parseArg(arg, "i", &logicalPosition))
    {
        int limit = 0;
        UBiDiLevel level = 0;

        ubidi_getLogicalRun(self->object, logicalPosition, &limit, &level);

        return Py_BuildValue("(ii)", limit, (int) level);
    }

    return PyErr_SetArgsError((PyObject *) self, "getLogicalRun", arg);
}

static PyObject *t_bidi_getVisualRun(t_bidi *self, PyObject *arg)
{
    int runIndex;

    if (!parseArg(arg, "i", &runIndex))
    {
        int logicalStart = 0, length = 0;
        UBiDiDirection direction = ubidi_getVisualRun(
            self->object, runIndex, &logicalStart, &length);

        return Py_BuildValue("(iii)", logicalStart, length, direction);
    }

    return PyErr_SetArgsError((PyObject *) self, "getVisualRun", arg);
}

static PyObject *t_bidi_getLogicalIndex(t_bidi *self, PyObject *arg)
{
    int visualIndex;

    if (!parseArg(arg, "i", &visualIndex))
    {
        int logicalIndex;

        STATUS_CALL(logicalIndex = ubidi_getLogicalIndex(
            self->object, visualIndex, &status));

        return PyInt_FromLong(logicalIndex);
    }

    return PyErr_SetArgsError((PyObject *) self, "getLogicalIndex", arg);
}

static PyObject *t_bidi_getVisualIndex(t_bidi *self, PyObject *arg)
{
    int logicalIndex;

    if (!parseArg(arg, "i", &logicalIndex))
    {
        int visualIndex;

        STATUS_CALL(visualIndex = ubidi_getVisualIndex(
            self->object, logicalIndex, &status));

        return PyInt_FromLong(visualIndex);
    }

    return PyErr_SetArgsError((PyObject *) self, "getVisualIndex", arg);
}

static PyObject *t_bidi_getLogicalMap(t_bidi *self)
{
    int length;

    if (ubidi_getReorderingOptions(self->object) & UBIDI_OPTION_INSERT_MARKS)
        length = ubidi_getResultLength(self->object);
    else
        length = ubidi_getProcessedLength(self->object);

    int *indexMap = (int *) calloc(length, sizeof(int));

    if (indexMap == NULL)
        return PyErr_NoMemory();

    STATUS_CALL(
        {
            ubidi_getLogicalMap(self->object, indexMap, &status);
            if (U_FAILURE(status))
                free(indexMap);
        });

    PyObject *result = PyTuple_New(length);

    if (result != NULL)
    {
        for (int i = 0; i < length; ++i)
            PyTuple_SET_ITEM(result, i, PyInt_FromLong(indexMap[i]));
    }
    free(indexMap);

    return result;
}

static PyObject *t_bidi_getVisualMap(t_bidi *self)
{
    int length;

    if (ubidi_getReorderingOptions(self->object) & UBIDI_OPTION_REMOVE_CONTROLS)
        length = ubidi_getProcessedLength(self->object);
    else
        length = ubidi_getResultLength(self->object);

    int *indexMap = (int *) calloc(length, sizeof(int));

    if (indexMap == NULL)
        return PyErr_NoMemory();

    STATUS_CALL(
        {
            ubidi_getVisualMap(self->object, indexMap, &status);
            if (U_FAILURE(status))
                free(indexMap);
        });

    PyObject *result = PyTuple_New(length);

    if (result != NULL)
    {
        for (int i = 0; i < length; ++i)
            PyTuple_SET_ITEM(result, i, PyInt_FromLong(indexMap[i]));
    }
    free(indexMap);

    return result;
}

static PyObject *t_bidi_reorderLogical(PyTypeObject *type, PyObject *arg)
{
    int *levels, length;

    if (!parseArg(arg, "H", &levels, &length))
    {
        int *indexMap = (int *) calloc(length, sizeof(int));

        if (indexMap == NULL)
            return PyErr_NoMemory();

        ubidi_reorderLogical((const UBiDiLevel *) levels, length, indexMap);

        PyObject *result = PyTuple_New(length);

        if (result != NULL)
        {
            for (int i = 0; i < length; ++i)
                PyTuple_SET_ITEM(result, i, PyInt_FromLong(indexMap[i]));
        }
        free(indexMap);

        return result;
    }

    return PyErr_SetArgsError((PyObject *) type, "reorderLogical", arg);
}

static PyObject *t_bidi_reorderVisual(PyTypeObject *type, PyObject *arg)
{
    int *levels, length;

    if (!parseArg(arg, "H", &levels, &length))
    {
        int *indexMap = (int *) calloc(length, sizeof(int));

        if (indexMap == NULL)
            return PyErr_NoMemory();

        ubidi_reorderVisual((const UBiDiLevel *) levels, length, indexMap);

        PyObject *result = PyTuple_New(length);

        if (result != NULL)
        {
            for (int i = 0; i < length; ++i)
                PyTuple_SET_ITEM(result, i, PyInt_FromLong(indexMap[i]));
        }
        free(indexMap);

        return result;
    }

    return PyErr_SetArgsError((PyObject *) type, "reorderVisual", arg);
}

static PyObject *t_bidi_invertMap(PyTypeObject *type, PyObject *arg)
{
    int *srcMap, srcLength;

    if (!parseArg(arg, "H", &srcMap, &srcLength))
    {
        int maxSrc = 0;

        for (int i = 0; i < srcLength; ++i)
            if (srcMap[i] > maxSrc)
                maxSrc = srcMap[i];

        int destLength = maxSrc + 1;
        int *destMap = (int *) calloc(destLength, sizeof(int));

        if (destMap == NULL)
            return PyErr_NoMemory();

        ubidi_invertMap((const int *) srcMap, destMap, srcLength);

        PyObject *result = PyTuple_New(destLength);

        if (result != NULL)
        {
            for (int i = 0; i < destLength; ++i)
                PyTuple_SET_ITEM(result, i, PyInt_FromLong(destMap[i]));
        }
        free(destMap);

        return result;
    }

    return PyErr_SetArgsError((PyObject *) type, "invertMap", arg);
}

static PyObject *t_bidi_setInverse(t_bidi *self, PyObject *arg)
{
    int inverse;

    if (!parseArg(arg, "b", &inverse))
    {
        ubidi_setInverse(self->object, (UBool) inverse);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setInverse", arg);
}

static PyObject *t_bidi_isInverse(t_bidi *self)
{
    UBool inverse = ubidi_isInverse(self->object);
    Py_RETURN_BOOL(inverse);
}

static PyObject *t_bidi_orderParagraphsLTR(t_bidi *self, PyObject *arg)
{
    int ltr;

    if (!parseArg(arg, "b", &ltr))
    {
        ubidi_orderParagraphsLTR(self->object, (UBool) ltr);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "orderParagraphsLTR", arg);
}

static PyObject *t_bidi_isOrderParagraphsLTR(t_bidi *self)
{
    UBool ltr = ubidi_isOrderParagraphsLTR(self->object);
    Py_RETURN_BOOL(ltr);
}

static PyObject *t_bidi_setReorderingMode(t_bidi *self, PyObject *arg)
{
    int mode;

    if (!parseArg(arg, "i", &mode))
    {
        ubidi_setReorderingMode(self->object, (UBiDiReorderingMode) mode);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setReorderingMode", arg);
}

static PyObject *t_bidi_getReorderingMode(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getReorderingMode(self->object));
}

static PyObject *t_bidi_setReorderingOptions(t_bidi *self, PyObject *arg)
{
    int options;

    if (!parseArg(arg, "i", &options))
    {
        ubidi_setReorderingOptions(self->object, options);
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setReorderingOptions", arg);
}

static PyObject *t_bidi_getReorderingOptions(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getReorderingOptions(self->object));
}

static PyObject *t_bidi_getDirection(t_bidi *self)
{
    return PyInt_FromLong(ubidi_getDirection(self->object));
}

static PyObject *t_bidi_getBaseDirection(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u) && u->length() >= 1)
        return PyInt_FromLong(ubidi_getBaseDirection(
            u->getBuffer(), u->length()));

    return PyErr_SetArgsError((PyObject *) type, "getBaseDirection", arg);
}

static PyObject *t_bidi_writeReordered(t_bidi *self, PyObject *args)
{
    int options;

    switch (PyTuple_Size(args)) {
      case 0:
        options = 0;
        break;

      case 1:
        if (!parseArgs(args, "i", &options))
          break;
        return PyErr_SetArgsError((PyObject *) self, "writeReordered", args);

      default:
        return PyErr_SetArgsError((PyObject *) self, "writeReordered", args);
    }

    int destSize;

    if (options & UBIDI_INSERT_LRM_FOR_NUMERIC)
    {
        int runs;
        STATUS_CALL(runs = ubidi_countRuns(self->object, &status));

        destSize = ubidi_getLength(self->object) + 2 * runs;
    }
    else if (options & UBIDI_REMOVE_BIDI_CONTROLS)
      destSize = ubidi_getLength(self->object);
    else
      destSize = ubidi_getProcessedLength(self->object);

    UnicodeString *u = new UnicodeString(destSize, 0, 0);

    if (u == NULL)
        return PyErr_NoMemory();

    UChar *dest = u->getBuffer(destSize);
    int length;

    STATUS_CALL(
        {
            length = ubidi_writeReordered(
                self->object, dest, destSize, options, &status);
            if (U_FAILURE(status))
            {
                u->releaseBuffer(0);
                delete u;
            }
        });

    u->releaseBuffer(length);
    return wrap_UnicodeString(u, T_OWNED);
}

static PyObject *t_bidi_writeReverse(PyTypeObject *type, PyObject *args)
{
    UnicodeString *src, _src;
    int options;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &src, &_src))
        {
            options = 0;
            break;
        }
        return PyErr_SetArgsError((PyObject *) type, "writeReverse", args);

      case 2:
        if (!parseArgs(args, "Si", &src, &_src, &options))
          break;
        return PyErr_SetArgsError((PyObject *) type, "writeReverse", args);

      default:
        return PyErr_SetArgsError((PyObject *) type, "writeReverse", args);
    }

    int destSize = src->length();
    UnicodeString *u = new UnicodeString(destSize, 0, 0);

    if (u == NULL)
        return PyErr_NoMemory();

    UChar *dest = u->getBuffer(destSize);
    int length;

    STATUS_CALL(
        {
            length = ubidi_writeReverse(
                src->getBuffer(), src->length(), dest, destSize, options,
                &status);

            if (U_FAILURE(status))
            {
                u->releaseBuffer(0);
                delete u;
            }
        });

    u->releaseBuffer(length);
    return wrap_UnicodeString(u, T_OWNED);
}


#if U_ICU_VERSION_HEX >= VERSION_HEX(58, 0, 0)

/* BidiTransform */

static int t_biditransform_init(
    t_biditransform *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        INT_STATUS_CALL(self->object = ubiditransform_open(&status));
        self->flags = T_OWNED;
        return 0;

      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
}

static PyObject *t_biditransform_transform(t_biditransform *self,
                                           PyObject *args)
{
    UnicodeString *src, _src;
    int inParaLevel, outParaLevel;  // UBiDiLevel
    UBiDiOrder inOrder, outOrder;
    UBiDiMirroring doMirroring = UBIDI_MIRRORING_OFF;
    int shapingOptions = 0;

    switch (PyTuple_Size(args)) {
      case 5:
        if (!parseArgs(args, "Siiii", &src, &_src,
                       &inParaLevel, &inOrder, &outParaLevel, &outOrder))
          break;
        return PyErr_SetArgsError((PyObject *) self, "transform", args);

      case 6:
        if (!parseArgs(args, "Siiiii", &src, &_src,
                       &inParaLevel, &inOrder, &outParaLevel, &outOrder,
                       &doMirroring))
          break;
        return PyErr_SetArgsError((PyObject *) self, "transform", args);

      case 7:
        if (!parseArgs(args, "Siiiiii", &src, &_src,
                       &inParaLevel, &inOrder, &outParaLevel, &outOrder,
                       &doMirroring, &shapingOptions))
          break;
        return PyErr_SetArgsError((PyObject *) self, "transform", args);

      default:
        return PyErr_SetArgsError((PyObject *) self, "transform", args);
    }

    int srcSize = src->length();
    int destSize = srcSize;

    if (shapingOptions & U_SHAPE_LETTERS_UNSHAPE)
      destSize *= 2;

    UnicodeString *u = new UnicodeString(destSize, 0, 0);

    if (u == NULL)
        return PyErr_NoMemory();

    UChar *dest = u->getBuffer(destSize);
    int length;

    STATUS_CALL(
        {
            length = ubiditransform_transform(
                self->object, src->getBuffer(), srcSize, dest, destSize,
                (UBiDiLevel) inParaLevel, inOrder,
                (UBiDiLevel) outParaLevel, outOrder,
                doMirroring, shapingOptions, &status);

            if (U_FAILURE(status))
            {
                u->releaseBuffer(0);
                delete u;
            }
        });

    u->releaseBuffer(length);
    return wrap_UnicodeString(u, T_OWNED);
}

#endif  // >= 58

void _init_bidi(PyObject *m)
{
    BidiType_.tp_getset = t_bidi_properties;
    INSTALL_STRUCT(Bidi, m);

    INSTALL_CONSTANTS_TYPE(UBiDiDirection, m);
    INSTALL_CONSTANTS_TYPE(UBiDiReorderingMode, m);
    INSTALL_CONSTANTS_TYPE(UBiDiReorderingOption, m);

#if U_ICU_VERSION_HEX >= VERSION_HEX(58, 0, 0)
    INSTALL_STRUCT(BidiTransform, m);

    INSTALL_CONSTANTS_TYPE(UBiDiMirroring, m);
    INSTALL_CONSTANTS_TYPE(UBiDiOrder, m);
#endif

    INSTALL_ENUM(Bidi, "DEFAULT_LTR", UBIDI_DEFAULT_LTR);
    INSTALL_ENUM(Bidi, "DEFAULT_RTL", UBIDI_DEFAULT_RTL);
    INSTALL_ENUM(Bidi, "MAX_EXPLICIT_LEVEL", UBIDI_MAX_EXPLICIT_LEVEL);
    INSTALL_ENUM(Bidi, "LEVEL_OVERRIDE", UBIDI_LEVEL_OVERRIDE);
    INSTALL_ENUM(Bidi, "MAP_NOWHERE", UBIDI_MAP_NOWHERE);
    INSTALL_ENUM(Bidi, "KEEP_BASE_COMBINING", UBIDI_KEEP_BASE_COMBINING);
    INSTALL_ENUM(Bidi, "DO_MIRRORING", UBIDI_DO_MIRRORING);
    INSTALL_ENUM(Bidi, "INSERT_LRM_FOR_NUMERIC", UBIDI_INSERT_LRM_FOR_NUMERIC);
    INSTALL_ENUM(Bidi, "REMOVE_BIDI_CONTROLS", UBIDI_REMOVE_BIDI_CONTROLS);
    INSTALL_ENUM(Bidi, "OUTPUT_REVERSE", UBIDI_OUTPUT_REVERSE);

    INSTALL_ENUM(UBiDiDirection, "LTR", UBIDI_LTR);
    INSTALL_ENUM(UBiDiDirection, "RTL", UBIDI_RTL);
    INSTALL_ENUM(UBiDiDirection, "MIXED", UBIDI_MIXED);
#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(UBiDiDirection, "NEUTRAL", UBIDI_NEUTRAL);
#endif

    INSTALL_ENUM(UBiDiReorderingMode, "DEFAULT", UBIDI_REORDER_DEFAULT);
    INSTALL_ENUM(UBiDiReorderingMode, "NUMBERS_SPECIAL", UBIDI_REORDER_NUMBERS_SPECIAL);
    INSTALL_ENUM(UBiDiReorderingMode, "GROUP_NUMBERS_WITH_R", UBIDI_REORDER_GROUP_NUMBERS_WITH_R);
    INSTALL_ENUM(UBiDiReorderingMode, "RUNS_ONLY", UBIDI_REORDER_RUNS_ONLY);
    INSTALL_ENUM(UBiDiReorderingMode, "INVERSE_NUMBERS_AS_L", UBIDI_REORDER_INVERSE_NUMBERS_AS_L);
    INSTALL_ENUM(UBiDiReorderingMode, "INVERSE_LIKE_DIRECT", UBIDI_REORDER_INVERSE_LIKE_DIRECT);
    INSTALL_ENUM(UBiDiReorderingMode, "INVERSE_FOR_NUMBERS_SPECIAL", UBIDI_REORDER_INVERSE_FOR_NUMBERS_SPECIAL);

    INSTALL_ENUM(UBiDiReorderingOption, "DEFAULT", UBIDI_OPTION_DEFAULT);
    INSTALL_ENUM(UBiDiReorderingOption, "INSERT_MARKS", UBIDI_OPTION_INSERT_MARKS);
    INSTALL_ENUM(UBiDiReorderingOption, "REMOVE_CONTROLS", UBIDI_OPTION_REMOVE_CONTROLS);
    INSTALL_ENUM(UBiDiReorderingOption, "STREAMING", UBIDI_OPTION_STREAMING);

#if U_ICU_VERSION_HEX >= VERSION_HEX(58, 0, 0)
    INSTALL_ENUM(UBiDiMirroring, "OFF", UBIDI_MIRRORING_OFF);
    INSTALL_ENUM(UBiDiMirroring, "ON", UBIDI_MIRRORING_ON);

    INSTALL_ENUM(UBiDiOrder, "LOGICAL", UBIDI_LOGICAL);
    INSTALL_ENUM(UBiDiOrder, "VISUAL", UBIDI_VISUAL);
#endif
}
