/* ====================================================================
 * Copyright (c) 2019 Open Source Applications Foundation.
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
#include "gender.h"
#include "locale.h"
#include "macros.h"

#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)

DECLARE_CONSTANTS_TYPE(UGender)

/* GenderInfo */

class t_genderinfo : public _wrapper {
public:
    GenderInfo *object;
};

static PyObject *t_genderinfo_getInstance(PyTypeObject *type, PyObject *arg);
static PyObject *t_genderinfo_getListGender(t_genderinfo *self, PyObject *arg);

static PyMethodDef t_genderinfo_methods[] = {
    DECLARE_METHOD(t_genderinfo, getInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_genderinfo, getListGender, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(GenderInfo, t_genderinfo, UObject,
             GenderInfo, abstract_init, NULL)


/* GenderInfo */

static PyObject *t_genderinfo_getInstance(PyTypeObject *type, PyObject *arg)
{
    Locale *locale;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        const GenderInfo *result;
        STATUS_CALL(result = GenderInfo::getInstance(*locale, status));

        return wrap_GenderInfo(const_cast<GenderInfo *>(result), 0);
    }

    return PyErr_SetArgsError(type, "getInstance", arg);
}

static PyObject *t_genderinfo_getListGender(t_genderinfo *self, PyObject *arg)
{
    UGender *genders;
    int len;

    if (!parseArg(arg, "H", &genders, &len))
    {
        UGender result;
        STATUS_CALL(
            {
                result = self->object->getListGender(genders, len, status);
                delete[] genders;
            });

        return PyInt_FromLong(result);
    }

    return PyErr_SetArgsError((PyObject *) self, "getListGender", arg);
}

#endif

void _init_gender(PyObject *m)
{
#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)
    INSTALL_CONSTANTS_TYPE(UGender, m);
    REGISTER_TYPE(GenderInfo, m);

    INSTALL_ENUM(UGender, "MALE", UGENDER_MALE);
    INSTALL_ENUM(UGender, "FEMALE", UGENDER_FEMALE);
    INSTALL_ENUM(UGender, "OTHER", UGENDER_OTHER);
#endif
}
