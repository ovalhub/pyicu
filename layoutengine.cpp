/* ====================================================================
 * Copyright (c) 2011-2011 Open Source Applications Foundation.
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

#include <layout/LayoutEngine.h>
#include <layout/LEFontInstance.h>
#include <layout/LELanguages.h>
#include <layout/LEScripts.h>

#include "bases.h"
#include "layoutengine.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(ScriptCode);
DECLARE_CONSTANTS_TYPE(LanguageCode);

static PyObject *getFontTable_NAME;

/* LEFontInstance */

class t_lefontinstance : public _wrapper {
public:
    LEFontInstance *object;
};

U_NAMESPACE_BEGIN

class U_EXPORT PythonLEFontInstance : public LEFontInstance {
  public:
    /**
     * ICU "poor man's RTTI", returns a UClassID for the actual class.
     */
    virtual UClassID getDynamicClassID() const;

    /**
     * ICU "poor man's RTTI", returns a UClassID for this class.
     */
    static UClassID getStaticClassID();

    PythonLEFontInstance(t_lefontinstance *t_self) : self(t_self)
    {
        tables = PyDict_New();
    }
        
    /**
     * Destructor.
     */
    virtual ~PythonLEFontInstance()
    {
        Py_DECREF(tables);
    }

    le_int32 get_le_int32(const char *name) const
    {
        PyObject *s = PyString_FromString(name);
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, s, NULL);

        Py_DECREF(s);
        if (result != NULL)
        {
            int n;

            if (!parseArg(result, "i", &n))
            {
                Py_DECREF(result);
                return (le_int32) n;
            }
        }

        return 0;
    }

    float get_float(const char *name) const
    {
        PyObject *s = PyString_FromString(name);
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, s, NULL);

        Py_DECREF(s);
        if (result != NULL)
        {
            double d;

            if (!parseArg(result, "d", &d))
            {
                Py_DECREF(result);
                return (float) d;
            }
        }

        return 0.0f;
    }

    /**
     * LEFontInstance API.
     */

    virtual const void *getFontTable(LETag tableTag, size_t &length) const
    {
        length = -1;
        return getFontTable(tableTag);
    }

    virtual const void *getFontTable(LETag tag) const
    {
#if PY_MAJOR_VERSION >= 3
        PyObject *key = PyUnicode_FromStringAndSize(NULL, 4);
        Py_UNICODE *s = PyUnicode_AS_UNICODE(key);
#else
        PyObject *key = PyString_FromStringAndSize(NULL, 4);
        char *s = PyString_AS_STRING(key);
#endif
        for (int i = 0; i < 4; ++i) {
            s[3 - i] = tag & 0xff;
            tag >>= 8;
        }

        PyObject *result = PyDict_GetItem(tables, key);

        if (result == NULL)
        {
            result = PyObject_CallMethodObjArgs((PyObject *) self,
                                                getFontTable_NAME, key, NULL);
            if (result == NULL)
            {
                if (PyErr_ExceptionMatches(PyExc_KeyError))
                    PyErr_Clear();
                Py_DECREF(key);

                return NULL;
            }

#if PY_MAJOR_VERSION >= 3
            if (!PyBytes_CheckExact(result))
#else
            if (!PyString_CheckExact(result))
#endif
            {
                PyErr_SetObject(PyExc_TypeError, result);
                Py_DECREF(result);
                Py_DECREF(key);

                return NULL;
            }

            PyDict_SetItem(tables, key, result);

            Py_DECREF(result);
            Py_DECREF(key);
        }
        else
            Py_DECREF(key);

#if PY_MAJOR_VERSION >= 3
        return PyBytes_AS_STRING(result);
#else
        return PyString_AS_STRING(result);
#endif
    }

    virtual le_int32 getAscent() const
    {
        return get_le_int32("getAscent");
    }

    virtual le_int32 getDescent() const
    {
        return get_le_int32("getDescent");
    }

    virtual le_int32 getLeading() const
    {
        return get_le_int32("getLeading");
    }

    virtual le_int32 getUnitsPerEM() const
    {
        return get_le_int32("getUnitsPerEm");
    }

    virtual LEGlyphID mapCharToGlyph(LEUnicode32 u) const
    {
        PyObject *name = PyString_FromString("mapCharToGlyph");
        PyObject *n = PyInt_FromLong(u);
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, name, n, NULL);

        Py_DECREF(n);
        Py_DECREF(name);
        if (result != NULL)
        {
            int id;

            if (!parseArg(result, "i", &id))
            {
                Py_DECREF(result);
                return id;
            }
        }

        return 0;
    }

    virtual LEGlyphID mapCharToGlyph(LEUnicode32 u,
                                     const LECharMapper *mapper) const {
      return LEFontInstance::mapCharToGlyph(u, mapper);
    }

    virtual LEGlyphID mapCharToGlyph(LEUnicode32 u, const LECharMapper *mapper,
                                     le_bool filterZeroWidth) const {
      return LEFontInstance::mapCharToGlyph(u, mapper, filterZeroWidth);
    }

    virtual void getGlyphAdvance(LEGlyphID glyph, LEPoint &advance) const
    {
        PyObject *name = PyString_FromString("getGlyphAdvance");
        PyObject *g = PyInt_FromLong(LE_GET_GLYPH(glyph));
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, name, g, NULL);

        Py_DECREF(g);
        Py_DECREF(name);

        if (result != NULL)
        {
            PyArg_ParseTuple(result, "ff", &advance.fX, &advance.fY);
            Py_DECREF(result);
        }
    }

    virtual le_bool getGlyphPoint(LEGlyphID glyph, le_int32 pointNumber,
                                  LEPoint &point) const
    {
        PyObject *name = PyString_FromString("getGlyphPoint");
        PyObject *g = PyInt_FromLong(LE_GET_GLYPH(glyph));
        PyObject *pn = PyInt_FromLong(pointNumber);
        PyObject *result =
            PyObject_CallMethodObjArgs((PyObject *) self, name, g, pn, NULL);

        Py_DECREF(pn);
        Py_DECREF(g);
        Py_DECREF(name);

        if (result != NULL)
        {
            PyArg_ParseTuple(result, "ff", &point.fX, &point.fY);
            Py_DECREF(result);

            return true;
        }
        
        return false;
    }

    virtual float getXPixelsPerEm() const
    {
        return get_float("getXPixelsPerEm");
    }

    virtual float getYPixelsPerEm() const
    {
        return get_float("getYPixelsPerEm");
    }

    virtual float getScaleFactorX() const
    {
        return get_float("getScaleFactorX");
    }

    virtual float getScaleFactorY() const
    {
        return get_float("getScaleFactorY");
    }

  private:
    t_lefontinstance *self;
    PyObject *tables;
};

U_NAMESPACE_END

UOBJECT_DEFINE_RTTI_IMPLEMENTATION(PythonLEFontInstance);

DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getFontTable);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getAscent);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getDescent);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getLeading);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, canDisplay);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getUnitsPerEm);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, mapCharToGlyph);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getGlyphAdvance);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getGlyphPoint);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getXPixelsPerEm);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getYPixelsPerEm);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getScaleFactorX);
DEFINE_ABSTRACT(t_lefontinstance, LEFontInstance, getScaleFactorY);

static PyMethodDef t_lefontinstance_methods[] = {
    DECLARE_METHOD(t_lefontinstance, getFontTable, METH_O),
    DECLARE_METHOD(t_lefontinstance, getAscent, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, getDescent, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, getLeading, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, canDisplay, METH_O),
    DECLARE_METHOD(t_lefontinstance, getUnitsPerEm, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, mapCharToGlyph, METH_O),
    DECLARE_METHOD(t_lefontinstance, getGlyphAdvance, METH_O),
    DECLARE_METHOD(t_lefontinstance, getGlyphPoint, METH_VARARGS),
    DECLARE_METHOD(t_lefontinstance, getXPixelsPerEm, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, getYPixelsPerEm, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, getScaleFactorX, METH_NOARGS),
    DECLARE_METHOD(t_lefontinstance, getScaleFactorY, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

static int t_lefontinstance_init(t_lefontinstance *self,
                                 PyObject *args, PyObject *kwds);

DECLARE_TYPE(LEFontInstance, t_lefontinstance, UObject, LEFontInstance,
             t_lefontinstance_init, NULL);

static int t_lefontinstance_init(t_lefontinstance *self,
                                 PyObject *args, PyObject *kwds)
{
    if (PyTuple_Size(args) == 0)
    {
        self->object = new PythonLEFontInstance(self);
        self->flags = T_OWNED;
        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}


/* LayoutEngine */

class t_layoutengine : public _wrapper {
public:
    LayoutEngine *object;
};

static PyObject *t_layoutengine_layoutEngineFactory(PyTypeObject *type,
                                                    PyObject *args);
static PyObject *t_layoutengine_layoutChars(t_layoutengine *self,
                                            PyObject *args);
static PyObject *t_layoutengine_getGlyphCount(t_layoutengine *self);
static PyObject *t_layoutengine_getGlyphs(t_layoutengine *self);
static PyObject *t_layoutengine_getCharIndices(t_layoutengine *self);
static PyObject *t_layoutengine_getGlyphPositions(t_layoutengine *self);
static PyObject *t_layoutengine_getGlyphPosition(t_layoutengine *self,
                                                 PyObject *arg);

static PyMethodDef t_layoutengine_methods[] = {
    DECLARE_METHOD(t_layoutengine, layoutEngineFactory, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_layoutengine, layoutChars, METH_VARARGS),
    DECLARE_METHOD(t_layoutengine, getGlyphCount, METH_NOARGS),
    DECLARE_METHOD(t_layoutengine, getGlyphs, METH_NOARGS),
    DECLARE_METHOD(t_layoutengine, getCharIndices, METH_NOARGS),
    DECLARE_METHOD(t_layoutengine, getGlyphPositions, METH_NOARGS),
    DECLARE_METHOD(t_layoutengine, getGlyphPosition, METH_O),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(LayoutEngine, t_layoutengine, UObject, LayoutEngine,
             abstract_init, NULL);


static PyObject *t_layoutengine_layoutEngineFactory(PyTypeObject *type,
                                                    PyObject *args)
{
    LayoutEngine *le = NULL;
    LEFontInstance *fe;
    le_int32 script, language, typo_flag;

    switch (PyTuple_Size(args)) {
      case 3:
        if (!parseArgs(args, "Pii", TYPE_CLASSID(LEFontInstance), &fe,
                       &script, &language))
        {
            STATUS_CALL(
                le = LayoutEngine::layoutEngineFactory(
                    fe, script, language, (LEErrorCode &) status));
            break;
        }
        return PyErr_SetArgsError((PyObject *) type, "__init__", args);

      case 4:
        if (!parseArgs(args, "Piii", TYPE_CLASSID(LEFontInstance), &fe,
                       &script, &language, &typo_flag))
        {
            STATUS_CALL(
                le = LayoutEngine::layoutEngineFactory(
                    fe, script, language, typo_flag, (LEErrorCode &) status));
            break;
        }
        return PyErr_SetArgsError((PyObject *) type, "__init__", args);

      default:
        return PyErr_SetArgsError((PyObject *) type, "__init__", args);
    }
                
    return wrap_LayoutEngine(le, T_OWNED);
}

static PyObject *t_layoutengine_layoutChars(t_layoutengine *self,
                                            PyObject *args)
{
    UnicodeString *u0, _u0;
    le_int32 n, offset, count;
    double x, y;
    int rtl;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u0, &_u0))
        {
            STATUS_CALL(
                n = self->object->layoutChars(
                    (const LEUnicode *) (u0->getBuffer()),
                    0, u0->length(), u0->length(), false,
                    0.0f, 0.0f, (LEErrorCode &) status));
            return PyInt_FromLong(n);
        }
        break;
      case 3:
        if (!parseArgs(args, "Sii", &u0, &_u0, &offset, &count))
        {
            STATUS_CALL(
                n = self->object->layoutChars(
                    (const LEUnicode *) (u0->getBuffer()),
                    offset, count, u0->length(), false,
                    0.0f, 0.0f, (LEErrorCode &) status));
            return PyInt_FromLong(n);
        }
        break;
      case 4:
        if (!parseArgs(args, "Siii", &u0, &_u0, &offset, &count, &rtl))
        {
            STATUS_CALL(
                n = self->object->layoutChars(
                    (const LEUnicode *) (u0->getBuffer()),
                    offset, count, u0->length(), rtl,
                    0.0f, 0.0f, (LEErrorCode &) status));
            return PyInt_FromLong(n);
        }
        break;
      case 6:
        if (!parseArgs(args, "Siiidd", &u0, &_u0, &offset, &count, &rtl,
                       &x, &y))
        {
            STATUS_CALL(
                n = self->object->layoutChars(
                    (const LEUnicode *) (u0->getBuffer()),
                    offset, count, u0->length(), rtl,
                    (float) x, (float) y, (LEErrorCode &) status));
            return PyInt_FromLong(n);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "layoutChars", args);
}

static PyObject *t_layoutengine_getGlyphCount(t_layoutengine *self)
{
    return PyInt_FromLong(self->object->getGlyphCount());
}

static PyObject *t_layoutengine_getGlyphs(t_layoutengine *self)
{
    le_int32 num = self->object->getGlyphCount();
    LEGlyphID *glyphs = new LEGlyphID[num];
    PyObject *tuple;

    STATUS_CALL(self->object->getGlyphs(glyphs, (LEErrorCode &) status));

    tuple = PyTuple_New(num);
    for (int i = 0; i < num; i++)
        PyTuple_SET_ITEM(tuple, i, PyInt_FromLong(glyphs[i]));
    delete[] glyphs;

    return tuple;
}

static PyObject *t_layoutengine_getCharIndices(t_layoutengine *self)
{
    le_int32 num = self->object->getGlyphCount();
    le_int32 *charIndices = new le_int32[num];
    PyObject *tuple;

    STATUS_CALL(self->object->getCharIndices(charIndices,
                                             (LEErrorCode &) status));
    tuple = PyTuple_New(num);
    for (int i = 0; i < num; i++)
        PyTuple_SET_ITEM(tuple, i, PyInt_FromLong(charIndices[i]));
    delete[] charIndices;

    return tuple;
}

static PyObject *t_layoutengine_getGlyphPositions(t_layoutengine *self)
{
    le_int32 num = self->object->getGlyphCount() + 1;
    float *positions = new float[num * 2];
    PyObject *tuple;

    STATUS_CALL(self->object->getGlyphPositions(positions,
                                                (LEErrorCode &) status));
    tuple = PyTuple_New(num);
    for (int i = 0; i < num; i++)
        PyTuple_SET_ITEM(tuple, i, Py_BuildValue("(ff)", positions[2 * i],
                                                 positions[2 * i + 1]));
    delete[] positions;

    return tuple;
}

static PyObject *t_layoutengine_getGlyphPosition(t_layoutengine *self,
                                                 PyObject *arg)
{
    le_int32 n;
    float x, y;

    if (!parseArg(arg, "i", &n))
    {
        STATUS_CALL(self->object->getGlyphPosition(n, x, y,
                                                   (LEErrorCode &) status));
        return Py_BuildValue("(ff)", x, y);
    }

    return PyErr_SetArgsError((PyObject *) self, "getGlyphPosition", arg);
}


void _init_layoutengine(PyObject *m)
{
    INSTALL_CONSTANTS_TYPE(ScriptCode, m);
    INSTALL_CONSTANTS_TYPE(LanguageCode, m);

    REGISTER_TYPE(LEFontInstance, m);
    REGISTER_TYPE(LayoutEngine, m);

    INSTALL_ENUM(ScriptCode, "zyyy", zyyyScriptCode);
#if U_ICU_VERSION_HEX >= 0x04040200
    INSTALL_ENUM(ScriptCode, "zinh", zinhScriptCode);
#endif
    INSTALL_ENUM(ScriptCode, "qaai", qaaiScriptCode);
    INSTALL_ENUM(ScriptCode, "arab", arabScriptCode);
    INSTALL_ENUM(ScriptCode, "armn", armnScriptCode);
    INSTALL_ENUM(ScriptCode, "beng", bengScriptCode);
    INSTALL_ENUM(ScriptCode, "bopo", bopoScriptCode);
    INSTALL_ENUM(ScriptCode, "cher", cherScriptCode);
    INSTALL_ENUM(ScriptCode, "copt", coptScriptCode);
    INSTALL_ENUM(ScriptCode, "cyrl", cyrlScriptCode);
    INSTALL_ENUM(ScriptCode, "dsrt", dsrtScriptCode);
    INSTALL_ENUM(ScriptCode, "deva", devaScriptCode);
    INSTALL_ENUM(ScriptCode, "ethi", ethiScriptCode);
    INSTALL_ENUM(ScriptCode, "geor", georScriptCode);
    INSTALL_ENUM(ScriptCode, "goth", gothScriptCode);
    INSTALL_ENUM(ScriptCode, "grek", grekScriptCode);
    INSTALL_ENUM(ScriptCode, "gujr", gujrScriptCode);
    INSTALL_ENUM(ScriptCode, "guru", guruScriptCode);
    INSTALL_ENUM(ScriptCode, "hani", haniScriptCode);
    INSTALL_ENUM(ScriptCode, "hang", hangScriptCode);
    INSTALL_ENUM(ScriptCode, "hebr", hebrScriptCode);
    INSTALL_ENUM(ScriptCode, "hira", hiraScriptCode);
    INSTALL_ENUM(ScriptCode, "knda", kndaScriptCode);
    INSTALL_ENUM(ScriptCode, "kana", kanaScriptCode);
    INSTALL_ENUM(ScriptCode, "khmr", khmrScriptCode);
    INSTALL_ENUM(ScriptCode, "laoo", laooScriptCode);
    INSTALL_ENUM(ScriptCode, "latn", latnScriptCode);
    INSTALL_ENUM(ScriptCode, "mlym", mlymScriptCode);
    INSTALL_ENUM(ScriptCode, "mong", mongScriptCode);
    INSTALL_ENUM(ScriptCode, "mymr", mymrScriptCode);
    INSTALL_ENUM(ScriptCode, "ogam", ogamScriptCode);
    INSTALL_ENUM(ScriptCode, "ital", italScriptCode);
    INSTALL_ENUM(ScriptCode, "orya", oryaScriptCode);
    INSTALL_ENUM(ScriptCode, "runr", runrScriptCode);
    INSTALL_ENUM(ScriptCode, "sinh", sinhScriptCode);
    INSTALL_ENUM(ScriptCode, "syrc", syrcScriptCode);
    INSTALL_ENUM(ScriptCode, "taml", tamlScriptCode);
    INSTALL_ENUM(ScriptCode, "telu", teluScriptCode);
    INSTALL_ENUM(ScriptCode, "thaa", thaaScriptCode);
    INSTALL_ENUM(ScriptCode, "thai", thaiScriptCode);
    INSTALL_ENUM(ScriptCode, "tibt", tibtScriptCode);
    INSTALL_ENUM(ScriptCode, "cans", cansScriptCode);
    INSTALL_ENUM(ScriptCode, "yiii", yiiiScriptCode);
    INSTALL_ENUM(ScriptCode, "tglg", tglgScriptCode);
    INSTALL_ENUM(ScriptCode, "hano", hanoScriptCode);
    INSTALL_ENUM(ScriptCode, "buhd", buhdScriptCode);
    INSTALL_ENUM(ScriptCode, "tagb", tagbScriptCode);
    INSTALL_ENUM(ScriptCode, "brai", braiScriptCode);
    INSTALL_ENUM(ScriptCode, "cprt", cprtScriptCode);
    INSTALL_ENUM(ScriptCode, "limb", limbScriptCode);
    INSTALL_ENUM(ScriptCode, "linb", linbScriptCode);
    INSTALL_ENUM(ScriptCode, "osma", osmaScriptCode);
    INSTALL_ENUM(ScriptCode, "shaw", shawScriptCode);
    INSTALL_ENUM(ScriptCode, "tale", taleScriptCode);
    INSTALL_ENUM(ScriptCode, "ugar", ugarScriptCode);
    INSTALL_ENUM(ScriptCode, "hrkt", hrktScriptCode);
    INSTALL_ENUM(ScriptCode, "bugi", bugiScriptCode);
    INSTALL_ENUM(ScriptCode, "glag", glagScriptCode);
    INSTALL_ENUM(ScriptCode, "khar", kharScriptCode);
    INSTALL_ENUM(ScriptCode, "sylo", syloScriptCode);
    INSTALL_ENUM(ScriptCode, "talu", taluScriptCode);
    INSTALL_ENUM(ScriptCode, "tfng", tfngScriptCode);
    INSTALL_ENUM(ScriptCode, "xpeo", xpeoScriptCode);
    INSTALL_ENUM(ScriptCode, "bali", baliScriptCode);
    INSTALL_ENUM(ScriptCode, "batk", batkScriptCode);
    INSTALL_ENUM(ScriptCode, "blis", blisScriptCode);
    INSTALL_ENUM(ScriptCode, "brah", brahScriptCode);
    INSTALL_ENUM(ScriptCode, "cham", chamScriptCode);
    INSTALL_ENUM(ScriptCode, "cirt", cirtScriptCode);
    INSTALL_ENUM(ScriptCode, "cyrs", cyrsScriptCode);
    INSTALL_ENUM(ScriptCode, "egyd", egydScriptCode);
    INSTALL_ENUM(ScriptCode, "egyh", egyhScriptCode);
    INSTALL_ENUM(ScriptCode, "egyp", egypScriptCode);
    INSTALL_ENUM(ScriptCode, "geok", geokScriptCode);
    INSTALL_ENUM(ScriptCode, "hans", hansScriptCode);
    INSTALL_ENUM(ScriptCode, "hant", hantScriptCode);
    INSTALL_ENUM(ScriptCode, "hmng", hmngScriptCode);
    INSTALL_ENUM(ScriptCode, "hung", hungScriptCode);
    INSTALL_ENUM(ScriptCode, "inds", indsScriptCode);
    INSTALL_ENUM(ScriptCode, "java", javaScriptCode);
    INSTALL_ENUM(ScriptCode, "kali", kaliScriptCode);
    INSTALL_ENUM(ScriptCode, "latf", latfScriptCode);
    INSTALL_ENUM(ScriptCode, "latg", latgScriptCode);
    INSTALL_ENUM(ScriptCode, "lepc", lepcScriptCode);
    INSTALL_ENUM(ScriptCode, "lina", linaScriptCode);
    INSTALL_ENUM(ScriptCode, "mand", mandScriptCode);
    INSTALL_ENUM(ScriptCode, "maya", mayaScriptCode);
    INSTALL_ENUM(ScriptCode, "mero", meroScriptCode);
    INSTALL_ENUM(ScriptCode, "nkoo", nkooScriptCode);
    INSTALL_ENUM(ScriptCode, "orkh", orkhScriptCode);
    INSTALL_ENUM(ScriptCode, "perm", permScriptCode);
    INSTALL_ENUM(ScriptCode, "phag", phagScriptCode);
    INSTALL_ENUM(ScriptCode, "phnx", phnxScriptCode);
    INSTALL_ENUM(ScriptCode, "plrd", plrdScriptCode);
    INSTALL_ENUM(ScriptCode, "roro", roroScriptCode);
    INSTALL_ENUM(ScriptCode, "sara", saraScriptCode);
    INSTALL_ENUM(ScriptCode, "syre", syreScriptCode);
    INSTALL_ENUM(ScriptCode, "syrj", syrjScriptCode);
    INSTALL_ENUM(ScriptCode, "syrn", syrnScriptCode);
    INSTALL_ENUM(ScriptCode, "teng", tengScriptCode);
    INSTALL_ENUM(ScriptCode, "vaii", vaiiScriptCode);
    INSTALL_ENUM(ScriptCode, "visp", vispScriptCode);
    INSTALL_ENUM(ScriptCode, "xsux", xsuxScriptCode);
    INSTALL_ENUM(ScriptCode, "zxxx", zxxxScriptCode);
    INSTALL_ENUM(ScriptCode, "zzzz", zzzzScriptCode);
    INSTALL_ENUM(ScriptCode, "cari", cariScriptCode);
    INSTALL_ENUM(ScriptCode, "jpan", jpanScriptCode);
    INSTALL_ENUM(ScriptCode, "lana", lanaScriptCode);
    INSTALL_ENUM(ScriptCode, "lyci", lyciScriptCode);
    INSTALL_ENUM(ScriptCode, "lydi", lydiScriptCode);
    INSTALL_ENUM(ScriptCode, "olck", olckScriptCode);
    INSTALL_ENUM(ScriptCode, "rjng", rjngScriptCode);
    INSTALL_ENUM(ScriptCode, "saur", saurScriptCode);
    INSTALL_ENUM(ScriptCode, "sgnw", sgnwScriptCode);
    INSTALL_ENUM(ScriptCode, "sund", sundScriptCode);
    INSTALL_ENUM(ScriptCode, "moon", moonScriptCode);
    INSTALL_ENUM(ScriptCode, "mtei", mteiScriptCode);

#if U_ICU_VERSION_HEX >= 0x04000000
    INSTALL_ENUM(ScriptCode, "armi", armiScriptCode);
    INSTALL_ENUM(ScriptCode, "avst", avstScriptCode);
    INSTALL_ENUM(ScriptCode, "cakm", cakmScriptCode);
    INSTALL_ENUM(ScriptCode, "kore", koreScriptCode);
    INSTALL_ENUM(ScriptCode, "kthi", kthiScriptCode);
    INSTALL_ENUM(ScriptCode, "mani", maniScriptCode);
    INSTALL_ENUM(ScriptCode, "phli", phliScriptCode);
    INSTALL_ENUM(ScriptCode, "phlp", phlpScriptCode);
    INSTALL_ENUM(ScriptCode, "phlv", phlvScriptCode);
    INSTALL_ENUM(ScriptCode, "prti", prtiScriptCode);
    INSTALL_ENUM(ScriptCode, "samr", samrScriptCode);
    INSTALL_ENUM(ScriptCode, "tavt", tavtScriptCode);
    INSTALL_ENUM(ScriptCode, "zmth", zmthScriptCode);
    INSTALL_ENUM(ScriptCode, "zsym", zsymScriptCode);

#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(ScriptCode, "bamu", bamuScriptCode);
    INSTALL_ENUM(ScriptCode, "lisu", lisuScriptCode);
    INSTALL_ENUM(ScriptCode, "nkgb", nkgbScriptCode);
    INSTALL_ENUM(ScriptCode, "sarb", sarbScriptCode);

#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(ScriptCode, "bass", bassScriptCode);
    INSTALL_ENUM(ScriptCode, "dupl", duplScriptCode);
    INSTALL_ENUM(ScriptCode, "elba", elbaScriptCode);
    INSTALL_ENUM(ScriptCode, "gran", granScriptCode);
    INSTALL_ENUM(ScriptCode, "kpel", kpelScriptCode);
    INSTALL_ENUM(ScriptCode, "loma", lomaScriptCode);
    INSTALL_ENUM(ScriptCode, "mend", mendScriptCode);
    INSTALL_ENUM(ScriptCode, "merc", mercScriptCode);
    INSTALL_ENUM(ScriptCode, "narb", narbScriptCode);
    INSTALL_ENUM(ScriptCode, "nbat", nbatScriptCode);
    INSTALL_ENUM(ScriptCode, "palm", palmScriptCode);
    INSTALL_ENUM(ScriptCode, "sind", sindScriptCode);
    INSTALL_ENUM(ScriptCode, "wara", waraScriptCode);

#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
    INSTALL_ENUM(ScriptCode, "afak", afakScriptCode);
    INSTALL_ENUM(ScriptCode, "jurc", jurcScriptCode);
    INSTALL_ENUM(ScriptCode, "khoj", khojScriptCode);
    INSTALL_ENUM(ScriptCode, "mroo", mrooScriptCode);
    INSTALL_ENUM(ScriptCode, "nshu", nshuScriptCode);
    INSTALL_ENUM(ScriptCode, "shrd", shrdScriptCode);
    INSTALL_ENUM(ScriptCode, "sora", soraScriptCode);
    INSTALL_ENUM(ScriptCode, "takr", takrScriptCode);
    INSTALL_ENUM(ScriptCode, "tang", tangScriptCode);
    INSTALL_ENUM(ScriptCode, "tirh", tirhScriptCode);
    INSTALL_ENUM(ScriptCode, "wole", woleScriptCode);
#endif  /* 49.0 */
#endif  /* 4.6 */
#endif  /* 4.4 */
#endif  /* 4.0 */

    INSTALL_ENUM(LanguageCode, "nul", nullLanguageCode);
    INSTALL_ENUM(LanguageCode, "ara", araLanguageCode);
    INSTALL_ENUM(LanguageCode, "asm", asmLanguageCode);
    INSTALL_ENUM(LanguageCode, "ben", benLanguageCode);
    INSTALL_ENUM(LanguageCode, "far", farLanguageCode);
    INSTALL_ENUM(LanguageCode, "guj", gujLanguageCode);
    INSTALL_ENUM(LanguageCode, "hin", hinLanguageCode);
    INSTALL_ENUM(LanguageCode, "iwr", iwrLanguageCode);
    INSTALL_ENUM(LanguageCode, "jii", jiiLanguageCode);
    INSTALL_ENUM(LanguageCode, "jan", janLanguageCode);
    INSTALL_ENUM(LanguageCode, "kan", kanLanguageCode);
    INSTALL_ENUM(LanguageCode, "kok", kokLanguageCode);
    INSTALL_ENUM(LanguageCode, "kor", korLanguageCode);
    INSTALL_ENUM(LanguageCode, "ksh", kshLanguageCode);
    INSTALL_ENUM(LanguageCode, "mal", malLanguageCode);
    INSTALL_ENUM(LanguageCode, "mar", marLanguageCode);
    INSTALL_ENUM(LanguageCode, "mlr", mlrLanguageCode);
    INSTALL_ENUM(LanguageCode, "mni", mniLanguageCode);
    INSTALL_ENUM(LanguageCode, "ori", oriLanguageCode);
    INSTALL_ENUM(LanguageCode, "san", sanLanguageCode);
    INSTALL_ENUM(LanguageCode, "snd", sndLanguageCode);
    INSTALL_ENUM(LanguageCode, "snh", snhLanguageCode);
    INSTALL_ENUM(LanguageCode, "syr", syrLanguageCode);
    INSTALL_ENUM(LanguageCode, "tam", tamLanguageCode);
    INSTALL_ENUM(LanguageCode, "tel", telLanguageCode);
    INSTALL_ENUM(LanguageCode, "tha", thaLanguageCode);
    INSTALL_ENUM(LanguageCode, "urd", urdLanguageCode);
    INSTALL_ENUM(LanguageCode, "zhp", zhpLanguageCode);
    INSTALL_ENUM(LanguageCode, "zhs", zhsLanguageCode);
    INSTALL_ENUM(LanguageCode, "zht", zhtLanguageCode);

#if U_ICU_VERSION_HEX >= 0x04000000
    INSTALL_ENUM(LanguageCode, "afk", afkLanguageCode);
    INSTALL_ENUM(LanguageCode, "bel", belLanguageCode);
    INSTALL_ENUM(LanguageCode, "bgr", bgrLanguageCode);
    INSTALL_ENUM(LanguageCode, "cat", catLanguageCode);
    INSTALL_ENUM(LanguageCode, "che", cheLanguageCode);
    INSTALL_ENUM(LanguageCode, "cop", copLanguageCode);
    INSTALL_ENUM(LanguageCode, "csy", csyLanguageCode);
    INSTALL_ENUM(LanguageCode, "dan", danLanguageCode);
    INSTALL_ENUM(LanguageCode, "deu", deuLanguageCode);
    INSTALL_ENUM(LanguageCode, "dzn", dznLanguageCode);
    INSTALL_ENUM(LanguageCode, "ell", ellLanguageCode);
    INSTALL_ENUM(LanguageCode, "eng", engLanguageCode);
    INSTALL_ENUM(LanguageCode, "esp", espLanguageCode);
    INSTALL_ENUM(LanguageCode, "eti", etiLanguageCode);
    INSTALL_ENUM(LanguageCode, "euq", euqLanguageCode);
    INSTALL_ENUM(LanguageCode, "fin", finLanguageCode);
    INSTALL_ENUM(LanguageCode, "fra", fraLanguageCode);
    INSTALL_ENUM(LanguageCode, "gae", gaeLanguageCode);
    INSTALL_ENUM(LanguageCode, "hau", hauLanguageCode);
    INSTALL_ENUM(LanguageCode, "hrv", hrvLanguageCode);
    INSTALL_ENUM(LanguageCode, "hun", hunLanguageCode);
    INSTALL_ENUM(LanguageCode, "hye", hyeLanguageCode);
    INSTALL_ENUM(LanguageCode, "ind", indLanguageCode);
    INSTALL_ENUM(LanguageCode, "ita", itaLanguageCode);
    INSTALL_ENUM(LanguageCode, "khm", khmLanguageCode);
    INSTALL_ENUM(LanguageCode, "mng", mngLanguageCode);
    INSTALL_ENUM(LanguageCode, "mts", mtsLanguageCode);
    INSTALL_ENUM(LanguageCode, "nep", nepLanguageCode);
    INSTALL_ENUM(LanguageCode, "nld", nldLanguageCode);
    INSTALL_ENUM(LanguageCode, "pas", pasLanguageCode);
    INSTALL_ENUM(LanguageCode, "plk", plkLanguageCode);
    INSTALL_ENUM(LanguageCode, "ptg", ptgLanguageCode);
    INSTALL_ENUM(LanguageCode, "rom", romLanguageCode);
    INSTALL_ENUM(LanguageCode, "rus", rusLanguageCode);
    INSTALL_ENUM(LanguageCode, "sky", skyLanguageCode);
    INSTALL_ENUM(LanguageCode, "slv", slvLanguageCode);
    INSTALL_ENUM(LanguageCode, "sqi", sqiLanguageCode);
    INSTALL_ENUM(LanguageCode, "srb", srbLanguageCode);
    INSTALL_ENUM(LanguageCode, "sve", sveLanguageCode);
    INSTALL_ENUM(LanguageCode, "tib", tibLanguageCode);
    INSTALL_ENUM(LanguageCode, "trk", trkLanguageCode);
    INSTALL_ENUM(LanguageCode, "wel", welLanguageCode);
#endif  /* 4.0 */

    getFontTable_NAME = PyString_FromString("getFontTable");
}
