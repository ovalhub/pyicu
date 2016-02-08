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
#include "shape.h"
#include "macros.h"

/* Shape */

struct UNone;
typedef struct UNone UNone;

class t_shape : public _wrapper {
public:
    UNone *object;
};

static int t_shape_init(t_shape *self, PyObject *args, PyObject *kwds);
static PyObject *t_shape_shapeArabic(PyTypeObject *type, PyObject *args);

static PyMethodDef t_shape_methods[] = {
    DECLARE_METHOD(t_shape, shapeArabic, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_shape_dealloc(t_shape *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(Shape, t_shape, UNone, t_shape_init, t_shape_dealloc);

/* Shape */

static int t_shape_init(t_shape *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = NULL;  /* there is no ICU struct for this */
        self->flags = T_OWNED;
        return 0;
      default:
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
    }
}

static PyObject *t_shape_shapeArabic(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    uint32_t options = 0;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &options))
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

            size = u_shapeArabic(u->getBuffer(), len, dest, capacity,
                                 options, &status);
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

    return PyErr_SetArgsError((PyObject *) type, "shapeArabic", args);
}

void _init_shape(PyObject *m)
{
    INSTALL_STRUCT(Shape, m);

    INSTALL_ENUM(Shape, "LENGTH_GROW_SHRINK", U_SHAPE_LENGTH_GROW_SHRINK);
    INSTALL_ENUM(Shape, "LAMALEF_RESIZE", U_SHAPE_LAMALEF_RESIZE);
    INSTALL_ENUM(Shape, "LENGTH_FIXED_SPACES_NEAR", U_SHAPE_LENGTH_FIXED_SPACES_NEAR);
    INSTALL_ENUM(Shape, "LAMALEF_NEAR", U_SHAPE_LAMALEF_NEAR);
    INSTALL_ENUM(Shape, "LENGTH_FIXED_SPACES_AT_END", U_SHAPE_LENGTH_FIXED_SPACES_AT_END);
    INSTALL_ENUM(Shape, "LAMALEF_END", U_SHAPE_LAMALEF_END);
    INSTALL_ENUM(Shape, "LENGTH_FIXED_SPACES_AT_BEGINNING", U_SHAPE_LENGTH_FIXED_SPACES_AT_BEGINNING);
    INSTALL_ENUM(Shape, "TEXT_DIRECTION_LOGICAL", U_SHAPE_TEXT_DIRECTION_LOGICAL);
    INSTALL_ENUM(Shape, "TEXT_DIRECTION_MASK", U_SHAPE_TEXT_DIRECTION_MASK);
    INSTALL_ENUM(Shape, "TEXT_DIRECTION_VISUAL_LTR", U_SHAPE_TEXT_DIRECTION_VISUAL_LTR);

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_ENUM(Shape, "LAMALEF_BEGIN", U_SHAPE_LAMALEF_BEGIN);
    INSTALL_ENUM(Shape, "LAMALEF_AUTO", U_SHAPE_LAMALEF_AUTO);
    INSTALL_ENUM(Shape, "LENGTH_MASK", U_SHAPE_LENGTH_MASK);
    INSTALL_ENUM(Shape, "LAMALEF_MASK", U_SHAPE_LAMALEF_MASK);
    INSTALL_ENUM(Shape, "LAMALEF_NEAR", U_SHAPE_LAMALEF_NEAR);
    INSTALL_ENUM(Shape, "LAMALEF_RESIZE", U_SHAPE_LAMALEF_RESIZE);
    INSTALL_ENUM(Shape, "TEXT_DIRECTION_VISUAL_RTL", U_SHAPE_TEXT_DIRECTION_VISUAL_RTL);
#endif

    INSTALL_ENUM(Shape, "LETTERS_NOOP", U_SHAPE_LETTERS_NOOP);
    INSTALL_ENUM(Shape, "LETTERS_SHAPE", U_SHAPE_LETTERS_SHAPE);
    INSTALL_ENUM(Shape, "LETTERS_UNSHAPE", U_SHAPE_LETTERS_UNSHAPE);
    INSTALL_ENUM(Shape, "LETTERS_SHAPE_TASHKEEL_ISOLATED", U_SHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED);
    INSTALL_ENUM(Shape, "LETTERS_MASK", U_SHAPE_LETTERS_MASK);
    INSTALL_ENUM(Shape, "DIGITS_NOOP", U_SHAPE_DIGITS_NOOP);
    INSTALL_ENUM(Shape, "DIGITS_EN2AN", U_SHAPE_DIGITS_EN2AN);
    INSTALL_ENUM(Shape, "DIGITS_AN2EN", U_SHAPE_DIGITS_AN2EN);
    INSTALL_ENUM(Shape, "DIGITS_ALEN2AN_INIT_LR", U_SHAPE_DIGITS_ALEN2AN_INIT_LR);
    INSTALL_ENUM(Shape, "DIGITS_ALEN2AN_INIT_AL", U_SHAPE_DIGITS_ALEN2AN_INIT_AL);
    INSTALL_ENUM(Shape, "DIGITS_RESERVED", U_SHAPE_DIGITS_RESERVED);
    INSTALL_ENUM(Shape, "DIGITS_MASK", U_SHAPE_DIGITS_MASK);
    INSTALL_ENUM(Shape, "DIGIT_TYPE_AN", U_SHAPE_DIGIT_TYPE_AN);
    INSTALL_ENUM(Shape, "DIGIT_TYPE_AN_EXTENDED", U_SHAPE_DIGIT_TYPE_AN_EXTENDED);
    INSTALL_ENUM(Shape, "DIGIT_TYPE_RESERVED", U_SHAPE_DIGIT_TYPE_RESERVED);
    INSTALL_ENUM(Shape, "DIGIT_TYPE_MASK", U_SHAPE_DIGIT_TYPE_MASK);
    INSTALL_ENUM(Shape, "AGGREGATE_TASHKEEL", U_SHAPE_AGGREGATE_TASHKEEL);
    INSTALL_ENUM(Shape, "AGGREGATE_TASHKEEL_NOOP", U_SHAPE_AGGREGATE_TASHKEEL_NOOP);
    INSTALL_ENUM(Shape, "AGGREGATE_TASHKEEL_MASK", U_SHAPE_AGGREGATE_TASHKEEL_MASK);
    INSTALL_ENUM(Shape, "PRESERVE_PRESENTATION", U_SHAPE_PRESERVE_PRESENTATION);
    INSTALL_ENUM(Shape, "PRESERVE_PRESENTATION_NOOP", U_SHAPE_PRESERVE_PRESENTATION_NOOP);
    INSTALL_ENUM(Shape, "PRESERVE_PRESENTATION_MASK", U_SHAPE_PRESERVE_PRESENTATION_MASK);
    INSTALL_ENUM(Shape, "SEEN_TWOCELL_NEAR", U_SHAPE_SEEN_TWOCELL_NEAR);

#if U_ICU_VERSION_HEX >= 0x04020000
    INSTALL_ENUM(Shape, "SEEN_MASK", U_SHAPE_SEEN_MASK);
    INSTALL_ENUM(Shape, "YEHHAMZA_TWOCELL_NEAR", U_SHAPE_YEHHAMZA_TWOCELL_NEAR);
    INSTALL_ENUM(Shape, "YEHHAMZA_MASK", U_SHAPE_YEHHAMZA_MASK);
    INSTALL_ENUM(Shape, "TASHKEEL_BEGIN", U_SHAPE_TASHKEEL_BEGIN);
    INSTALL_ENUM(Shape, "TASHKEEL_END", U_SHAPE_TASHKEEL_END);
    INSTALL_ENUM(Shape, "TASHKEEL_RESIZE", U_SHAPE_TASHKEEL_RESIZE);
    INSTALL_ENUM(Shape, "TASHKEEL_REPLACE_BY_TATWEEL", U_SHAPE_TASHKEEL_REPLACE_BY_TATWEEL);
    INSTALL_ENUM(Shape, "TASHKEEL_MASK", U_SHAPE_TASHKEEL_MASK);
    INSTALL_ENUM(Shape, "SPACES_RELATIVE_TO_TEXT_BEGIN_END", U_SHAPE_SPACES_RELATIVE_TO_TEXT_BEGIN_END);
    INSTALL_ENUM(Shape, "SPACES_RELATIVE_TO_TEXT_MASK", U_SHAPE_SPACES_RELATIVE_TO_TEXT_MASK);
#endif

#if U_ICU_VERSION_HEX >= 0x04080000
    INSTALL_ENUM(Shape, "TAIL_NEW_UNICODE", U_SHAPE_TAIL_NEW_UNICODE);
    INSTALL_ENUM(Shape, "TAIL_TYPE_MASK", U_SHAPE_TAIL_TYPE_MASK);
#endif
}
