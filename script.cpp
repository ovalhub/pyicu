/* ====================================================================
 * Copyright (c) 2004-2013 Open Source Applications Foundation.
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
#include "script.h"
#include "macros.h"

DECLARE_CONSTANTS_TYPE(UScriptCode);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
DECLARE_CONSTANTS_TYPE(UScriptUsage);
#endif

/* Script */

struct UNone;
typedef struct UNone UNone;

class t_script : public _wrapper {
public:
    UNone *object;
    UScriptCode code;
};

static int t_script_init(t_script *self, PyObject *args, PyObject *kwds);
static PyObject *t_script_getName(t_script *self);
static PyObject *t_script_getShortName(t_script *self);
static PyObject *t_script_getScriptCode(t_script *self);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
static PyObject *t_script_isRightToLeft(t_script *self);
static PyObject *t_script_isCased(t_script *self);
static PyObject *t_script_breaksBetweenLetters(t_script *self);
static PyObject *t_script_getSampleString(t_script *self);
static PyObject *t_script_getUsage(t_script *self);
#endif
static PyObject *t_script_getCode(PyTypeObject *type, PyObject *arg);
static PyObject *t_script_getScript(PyTypeObject *type, PyObject *arg);
static PyObject *t_script_hasScript(PyTypeObject *type, PyObject *args);
static PyObject *t_script_getScriptExtensions(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_script_methods[] = {
    DECLARE_METHOD(t_script, getName, METH_NOARGS),
    DECLARE_METHOD(t_script, getShortName, METH_NOARGS),
    DECLARE_METHOD(t_script, getScriptCode, METH_NOARGS),
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    DECLARE_METHOD(t_script, isRightToLeft, METH_NOARGS),
    DECLARE_METHOD(t_script, isCased, METH_NOARGS),
    DECLARE_METHOD(t_script, breaksBetweenLetters, METH_NOARGS),
    DECLARE_METHOD(t_script, getSampleString, METH_NOARGS),
    DECLARE_METHOD(t_script, getUsage, METH_NOARGS),
#endif
    DECLARE_METHOD(t_script, getCode, METH_O | METH_CLASS),
    DECLARE_METHOD(t_script, getScript, METH_O | METH_CLASS),
    DECLARE_METHOD(t_script, hasScript, METH_VARARGS | METH_CLASS),
    DECLARE_METHOD(t_script, getScriptExtensions, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_script_dealloc(t_script *self)
{
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_STRUCT(Script, t_script, UNone, t_script_init, t_script_dealloc);


/* Script */

static int t_script_init(t_script *self, PyObject *args, PyObject *kwds)
{
    UScriptCode code;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "i", &code))
        {
            if (uscript_getName(code) == NULL)
            {
                PyErr_Format(PyExc_ValueError, "Invalid script code: %d",
                             code);
                return -1;
            }
            self->object = NULL;  /* there is no ICU struct for this */
            self->code = code;
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

static PyObject *t_script_getName(t_script *self)
{
    return PyString_FromString(uscript_getName(self->code));
}

static PyObject *t_script_getShortName(t_script *self)
{
    return PyString_FromString(uscript_getShortName(self->code));
}

static PyObject *t_script_getScriptCode(t_script *self)
{
    return PyInt_FromLong(self->code);
}

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
static PyObject *t_script_isRightToLeft(t_script *self)
{
    if (uscript_isRightToLeft(self->code))
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_script_isCased(t_script *self)
{
    if (uscript_isCased(self->code))
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_script_breaksBetweenLetters(t_script *self)
{
    if (uscript_breaksBetweenLetters(self->code))
        Py_RETURN_TRUE;

    Py_RETURN_FALSE;
}

static PyObject *t_script_getSampleString(t_script *self)
{
    UChar dest[32];
    int32_t count;

    STATUS_CALL(count = uscript_getSampleString(self->code, dest, sizeof(dest),
                                                &status));

    return PyUnicode_FromUnicodeString(dest, count);
}

static PyObject *t_script_getUsage(t_script *self)
{
    return PyInt_FromLong(uscript_getUsage(self->code));
}
#endif

static PyObject *t_script_getCode(PyTypeObject *type, PyObject *arg)
{
    charsArg name;

    if (!parseArg(arg, "n", &name))
    {
        UScriptCode codes[256];
        int count;

        STATUS_CALL(count = uscript_getCode(
            name, codes, sizeof(codes) / sizeof(UScriptCode), &status));

        PyObject *tuple = PyTuple_New(count);

        for (int i = 0; i < count; ++i)
            PyTuple_SET_ITEM(tuple, i, PyInt_FromLong(codes[i]));

        return tuple;
    }

    return PyErr_SetArgsError((PyObject *) type, "getCode", arg);
}

static PyObject *t_script_getScript(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        UScriptCode code;

        if (u->length() != 1)
        {
            PyObject *tuple = Py_BuildValue("(sO)", "length must be 1", arg);

            PyErr_SetObject(PyExc_ValueError, tuple);
            Py_DECREF(tuple);

            return NULL;
        }
  
        STATUS_CALL(code = uscript_getScript(u->char32At(0), &status));

        return PyObject_CallFunction((PyObject *) type, (char *) "i", code);
    }

    return PyErr_SetArgsError((PyObject *) type, "getScript", arg);
}

static PyObject *t_script_hasScript(PyTypeObject *type, PyObject *args)
{
    UnicodeString *u, _u;
    UScriptCode code;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &code))
        {
            if (u->length() != 1)
            {
                PyObject *tuple = Py_BuildValue("(sO)", "length must be 1",
                                                PyTuple_GET_ITEM(args, 0));

                PyErr_SetObject(PyExc_ValueError, tuple);
                Py_DECREF(tuple);

                return NULL;
            }
  
            if (uscript_hasScript(u->char32At(0), code))
                Py_RETURN_TRUE;

            Py_RETURN_FALSE;
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) type, "hasScript", args);
}

static PyObject *t_script_getScriptExtensions(PyTypeObject *type, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        if (u->length() != 1)
        {
            PyObject *tuple = Py_BuildValue("(sO)", "length must be 1", arg);

            PyErr_SetObject(PyExc_ValueError, tuple);
            Py_DECREF(tuple);

            return NULL;
        }
  
        UScriptCode codes[256];
        int count;

        STATUS_CALL(count = uscript_getScriptExtensions(
            u->char32At(0), codes, sizeof(codes) / sizeof(UScriptCode),
            &status));

        PyObject *tuple = PyTuple_New(count);

        for (int i = 0; i < count; ++i)
            PyTuple_SET_ITEM(tuple, i, PyInt_FromLong(codes[i]));

        return tuple;
    }

    return PyErr_SetArgsError((PyObject *) type, "getScriptExtensions", arg);
}


void _init_script(PyObject *m)
{
    INSTALL_CONSTANTS_TYPE(UScriptCode, m);
#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_CONSTANTS_TYPE(UScriptUsage, m);
#endif
    INSTALL_STRUCT(Script, m);

    INSTALL_ENUM(UScriptCode, "COMMON", USCRIPT_COMMON);
    INSTALL_ENUM(UScriptCode, "INHERITED", USCRIPT_INHERITED);
    INSTALL_ENUM(UScriptCode, "ARABIC", USCRIPT_ARABIC);
    INSTALL_ENUM(UScriptCode, "ARMENIAN", USCRIPT_ARMENIAN);
    INSTALL_ENUM(UScriptCode, "BENGALI", USCRIPT_BENGALI);
    INSTALL_ENUM(UScriptCode, "BOPOMOFO", USCRIPT_BOPOMOFO);
    INSTALL_ENUM(UScriptCode, "CHEROKEE", USCRIPT_CHEROKEE);
    INSTALL_ENUM(UScriptCode, "COPTIC", USCRIPT_COPTIC);
    INSTALL_ENUM(UScriptCode, "CYRILLIC", USCRIPT_CYRILLIC);
    INSTALL_ENUM(UScriptCode, "DESERET", USCRIPT_DESERET);
    INSTALL_ENUM(UScriptCode, "DEVANAGARI", USCRIPT_DEVANAGARI);
    INSTALL_ENUM(UScriptCode, "ETHIOPIC", USCRIPT_ETHIOPIC);
    INSTALL_ENUM(UScriptCode, "GEORGIAN", USCRIPT_GEORGIAN);
    INSTALL_ENUM(UScriptCode, "GOTHIC", USCRIPT_GOTHIC);
    INSTALL_ENUM(UScriptCode, "GREEK", USCRIPT_GREEK);
    INSTALL_ENUM(UScriptCode, "GUJARATI", USCRIPT_GUJARATI);
    INSTALL_ENUM(UScriptCode, "GURMUKHI", USCRIPT_GURMUKHI);
    INSTALL_ENUM(UScriptCode, "HAN", USCRIPT_HAN);
    INSTALL_ENUM(UScriptCode, "HANGUL", USCRIPT_HANGUL);
    INSTALL_ENUM(UScriptCode, "HEBREW", USCRIPT_HEBREW);
    INSTALL_ENUM(UScriptCode, "HIRAGANA", USCRIPT_HIRAGANA);
    INSTALL_ENUM(UScriptCode, "KANNADA", USCRIPT_KANNADA);
    INSTALL_ENUM(UScriptCode, "KATAKANA", USCRIPT_KATAKANA);
    INSTALL_ENUM(UScriptCode, "KHMER", USCRIPT_KHMER);
    INSTALL_ENUM(UScriptCode, "LAO", USCRIPT_LAO);
    INSTALL_ENUM(UScriptCode, "LATIN", USCRIPT_LATIN);
    INSTALL_ENUM(UScriptCode, "MALAYALAM", USCRIPT_MALAYALAM);
    INSTALL_ENUM(UScriptCode, "MONGOLIAN", USCRIPT_MONGOLIAN);
    INSTALL_ENUM(UScriptCode, "MYANMAR", USCRIPT_MYANMAR);
    INSTALL_ENUM(UScriptCode, "OGHAM", USCRIPT_OGHAM);
    INSTALL_ENUM(UScriptCode, "OLD_ITALIC", USCRIPT_OLD_ITALIC);
    INSTALL_ENUM(UScriptCode, "ORIYA", USCRIPT_ORIYA);
    INSTALL_ENUM(UScriptCode, "RUNIC", USCRIPT_RUNIC);
    INSTALL_ENUM(UScriptCode, "SINHALA", USCRIPT_SINHALA);
    INSTALL_ENUM(UScriptCode, "SYRIAC", USCRIPT_SYRIAC);
    INSTALL_ENUM(UScriptCode, "TAMIL", USCRIPT_TAMIL);
    INSTALL_ENUM(UScriptCode, "TELUGU", USCRIPT_TELUGU);
    INSTALL_ENUM(UScriptCode, "THAANA", USCRIPT_THAANA);
    INSTALL_ENUM(UScriptCode, "THAI", USCRIPT_THAI);
    INSTALL_ENUM(UScriptCode, "TIBETAN", USCRIPT_TIBETAN);
    INSTALL_ENUM(UScriptCode, "CANADIAN_ABORIGINAL", USCRIPT_CANADIAN_ABORIGINAL);
    INSTALL_ENUM(UScriptCode, "UCAS", USCRIPT_UCAS);
    INSTALL_ENUM(UScriptCode, "YI", USCRIPT_YI);
    INSTALL_ENUM(UScriptCode, "TAGALOG", USCRIPT_TAGALOG);
    INSTALL_ENUM(UScriptCode, "HANUNOO", USCRIPT_HANUNOO);
    INSTALL_ENUM(UScriptCode, "BUHID", USCRIPT_BUHID);
    INSTALL_ENUM(UScriptCode, "TAGBANWA", USCRIPT_TAGBANWA);
    INSTALL_ENUM(UScriptCode, "BRAILLE", USCRIPT_BRAILLE);
    INSTALL_ENUM(UScriptCode, "CYPRIOT", USCRIPT_CYPRIOT);
    INSTALL_ENUM(UScriptCode, "LIMBU", USCRIPT_LIMBU);
    INSTALL_ENUM(UScriptCode, "LINEAR_B", USCRIPT_LINEAR_B);
    INSTALL_ENUM(UScriptCode, "OSMANYA", USCRIPT_OSMANYA);
    INSTALL_ENUM(UScriptCode, "SHAVIAN", USCRIPT_SHAVIAN);
    INSTALL_ENUM(UScriptCode, "TAI_LE", USCRIPT_TAI_LE);
    INSTALL_ENUM(UScriptCode, "UGARITIC", USCRIPT_UGARITIC);
    INSTALL_ENUM(UScriptCode, "KATAKANA_OR_HIRAGANA", USCRIPT_KATAKANA_OR_HIRAGANA);
    INSTALL_ENUM(UScriptCode, "BUGINESE", USCRIPT_BUGINESE);
    INSTALL_ENUM(UScriptCode, "GLAGOLITIC", USCRIPT_GLAGOLITIC);
    INSTALL_ENUM(UScriptCode, "KHAROSHTHI", USCRIPT_KHAROSHTHI);
    INSTALL_ENUM(UScriptCode, "SYLOTI_NAGRI", USCRIPT_SYLOTI_NAGRI);
    INSTALL_ENUM(UScriptCode, "NEW_TAI_LUE", USCRIPT_NEW_TAI_LUE);
    INSTALL_ENUM(UScriptCode, "TIFINAGH", USCRIPT_TIFINAGH);
    INSTALL_ENUM(UScriptCode, "OLD_PERSIAN", USCRIPT_OLD_PERSIAN);
    INSTALL_ENUM(UScriptCode, "BALINESE", USCRIPT_BALINESE);
    INSTALL_ENUM(UScriptCode, "BATAK", USCRIPT_BATAK);
    INSTALL_ENUM(UScriptCode, "BLISSYMBOLS", USCRIPT_BLISSYMBOLS);
    INSTALL_ENUM(UScriptCode, "BRAHMI", USCRIPT_BRAHMI);
    INSTALL_ENUM(UScriptCode, "CHAM", USCRIPT_CHAM);
    INSTALL_ENUM(UScriptCode, "CIRTH", USCRIPT_CIRTH);
    INSTALL_ENUM(UScriptCode, "OLD_CHURCH_SLAVONIC_CYRILLIC", USCRIPT_OLD_CHURCH_SLAVONIC_CYRILLIC);
    INSTALL_ENUM(UScriptCode, "DEMOTIC_EGYPTIAN", USCRIPT_DEMOTIC_EGYPTIAN);
    INSTALL_ENUM(UScriptCode, "HIERATIC_EGYPTIAN", USCRIPT_HIERATIC_EGYPTIAN);
    INSTALL_ENUM(UScriptCode, "EGYPTIAN_HIEROGLYPHS", USCRIPT_EGYPTIAN_HIEROGLYPHS);
    INSTALL_ENUM(UScriptCode, "KHUTSURI", USCRIPT_KHUTSURI);
    INSTALL_ENUM(UScriptCode, "SIMPLIFIED_HAN", USCRIPT_SIMPLIFIED_HAN);
    INSTALL_ENUM(UScriptCode, "TRADITIONAL_HAN", USCRIPT_TRADITIONAL_HAN);
    INSTALL_ENUM(UScriptCode, "PAHAWH_HMONG", USCRIPT_PAHAWH_HMONG);
    INSTALL_ENUM(UScriptCode, "OLD_HUNGARIAN", USCRIPT_OLD_HUNGARIAN);
    INSTALL_ENUM(UScriptCode, "HARAPPAN_INDUS", USCRIPT_HARAPPAN_INDUS);
    INSTALL_ENUM(UScriptCode, "JAVANESE", USCRIPT_JAVANESE);
    INSTALL_ENUM(UScriptCode, "KAYAH_LI", USCRIPT_KAYAH_LI);
    INSTALL_ENUM(UScriptCode, "LATIN_FRAKTUR", USCRIPT_LATIN_FRAKTUR);
    INSTALL_ENUM(UScriptCode, "LATIN_GAELIC", USCRIPT_LATIN_GAELIC);
    INSTALL_ENUM(UScriptCode, "LEPCHA", USCRIPT_LEPCHA);
    INSTALL_ENUM(UScriptCode, "LINEAR_A", USCRIPT_LINEAR_A);
    INSTALL_ENUM(UScriptCode, "MANDAIC", USCRIPT_MANDAIC);
    INSTALL_ENUM(UScriptCode, "MANDAEAN", USCRIPT_MANDAEAN);
    INSTALL_ENUM(UScriptCode, "MEROITIC_HIEROGLYPHS", USCRIPT_MEROITIC_HIEROGLYPHS);
    INSTALL_ENUM(UScriptCode, "MEROITIC", USCRIPT_MEROITIC);
    INSTALL_ENUM(UScriptCode, "ORKHON", USCRIPT_ORKHON);
    INSTALL_ENUM(UScriptCode, "OLD_PERMIC", USCRIPT_OLD_PERMIC);
    INSTALL_ENUM(UScriptCode, "PHAGS_PA", USCRIPT_PHAGS_PA);
    INSTALL_ENUM(UScriptCode, "PHOENICIAN", USCRIPT_PHOENICIAN);
    INSTALL_ENUM(UScriptCode, "PHONETIC_POLLARD", USCRIPT_PHONETIC_POLLARD);
    INSTALL_ENUM(UScriptCode, "RONGORONGO", USCRIPT_RONGORONGO);
    INSTALL_ENUM(UScriptCode, "SARATI", USCRIPT_SARATI);
    INSTALL_ENUM(UScriptCode, "ESTRANGELO_SYRIAC", USCRIPT_ESTRANGELO_SYRIAC);
    INSTALL_ENUM(UScriptCode, "WESTERN_SYRIAC", USCRIPT_WESTERN_SYRIAC);
    INSTALL_ENUM(UScriptCode, "EASTERN_SYRIAC", USCRIPT_EASTERN_SYRIAC);
    INSTALL_ENUM(UScriptCode, "TENGWAR", USCRIPT_TENGWAR);
    INSTALL_ENUM(UScriptCode, "VAI", USCRIPT_VAI);
    INSTALL_ENUM(UScriptCode, "VISIBLE_SPEECH", USCRIPT_VISIBLE_SPEECH);
    INSTALL_ENUM(UScriptCode, "CUNEIFORM", USCRIPT_CUNEIFORM);
    INSTALL_ENUM(UScriptCode, "UNWRITTEN_LANGUAGES", USCRIPT_UNWRITTEN_LANGUAGES);
    INSTALL_ENUM(UScriptCode, "UNKNOWN", USCRIPT_UNKNOWN);
    INSTALL_ENUM(UScriptCode, "CARIAN", USCRIPT_CARIAN);
    INSTALL_ENUM(UScriptCode, "JAPANESE", USCRIPT_JAPANESE);
    INSTALL_ENUM(UScriptCode, "LANNA", USCRIPT_LANNA);
    INSTALL_ENUM(UScriptCode, "LYCIAN", USCRIPT_LYCIAN);
    INSTALL_ENUM(UScriptCode, "LYDIAN", USCRIPT_LYDIAN);
    INSTALL_ENUM(UScriptCode, "OL_CHIKI", USCRIPT_OL_CHIKI);
    INSTALL_ENUM(UScriptCode, "REJANG", USCRIPT_REJANG);
    INSTALL_ENUM(UScriptCode, "SAURASHTRA", USCRIPT_SAURASHTRA);
    INSTALL_ENUM(UScriptCode, "SIGN_WRITING", USCRIPT_SIGN_WRITING);
    INSTALL_ENUM(UScriptCode, "SUNDANESE", USCRIPT_SUNDANESE);
    INSTALL_ENUM(UScriptCode, "MOON", USCRIPT_MOON);
    INSTALL_ENUM(UScriptCode, "MEITEI_MAYEK", USCRIPT_MEITEI_MAYEK);

#if U_ICU_VERSION_HEX >= 0x04000000
    INSTALL_ENUM(UScriptCode, "IMPERIAL_ARAMAIC", USCRIPT_IMPERIAL_ARAMAIC);
    INSTALL_ENUM(UScriptCode, "AVESTAN", USCRIPT_AVESTAN);
    INSTALL_ENUM(UScriptCode, "CHAKMA", USCRIPT_CHAKMA);
    INSTALL_ENUM(UScriptCode, "KOREAN", USCRIPT_KOREAN);
    INSTALL_ENUM(UScriptCode, "KAITHI", USCRIPT_KAITHI);
    INSTALL_ENUM(UScriptCode, "MANICHAEAN", USCRIPT_MANICHAEAN);
    INSTALL_ENUM(UScriptCode, "INSCRIPTIONAL_PAHLAVI", USCRIPT_INSCRIPTIONAL_PAHLAVI);
    INSTALL_ENUM(UScriptCode, "PSALTER_PAHLAVI", USCRIPT_PSALTER_PAHLAVI);
    INSTALL_ENUM(UScriptCode, "BOOK_PAHLAVI", USCRIPT_BOOK_PAHLAVI);
    INSTALL_ENUM(UScriptCode, "INSCRIPTIONAL_PARTHIAN", USCRIPT_INSCRIPTIONAL_PARTHIAN);
    INSTALL_ENUM(UScriptCode, "SAMARITAN", USCRIPT_SAMARITAN);
    INSTALL_ENUM(UScriptCode, "TAI_VIET", USCRIPT_TAI_VIET);
    INSTALL_ENUM(UScriptCode, "MATHEMATICAL_NOTATION", USCRIPT_MATHEMATICAL_NOTATION);
    INSTALL_ENUM(UScriptCode, "SYMBOLS", USCRIPT_SYMBOLS);
#endif

#if U_ICU_VERSION_HEX >= 0x04040000
    INSTALL_ENUM(UScriptCode, "BAMUM", USCRIPT_BAMUM);
    INSTALL_ENUM(UScriptCode, "LISU", USCRIPT_LISU);
    INSTALL_ENUM(UScriptCode, "NAKHI_GEBA", USCRIPT_NAKHI_GEBA);
    INSTALL_ENUM(UScriptCode, "OLD_SOUTH_ARABIAN", USCRIPT_OLD_SOUTH_ARABIAN);
#endif

#if U_ICU_VERSION_HEX >= 0x04060000
    INSTALL_ENUM(UScriptCode, "BASSA_VAH", USCRIPT_BASSA_VAH);
    INSTALL_ENUM(UScriptCode, "DUPLOYAN_SHORTAND", USCRIPT_DUPLOYAN_SHORTAND);
    INSTALL_ENUM(UScriptCode, "ELBASAN", USCRIPT_ELBASAN);
    INSTALL_ENUM(UScriptCode, "GRANTHA", USCRIPT_GRANTHA);
    INSTALL_ENUM(UScriptCode, "KPELLE", USCRIPT_KPELLE);
    INSTALL_ENUM(UScriptCode, "LOMA", USCRIPT_LOMA);
    INSTALL_ENUM(UScriptCode, "MENDE", USCRIPT_MENDE);
    INSTALL_ENUM(UScriptCode, "MEROITIC_CURSIVE", USCRIPT_MEROITIC_CURSIVE);
    INSTALL_ENUM(UScriptCode, "OLD_NORTH_ARABIAN", USCRIPT_OLD_NORTH_ARABIAN);
    INSTALL_ENUM(UScriptCode, "NABATAEAN", USCRIPT_NABATAEAN);
    INSTALL_ENUM(UScriptCode, "PALMYRENE", USCRIPT_PALMYRENE);
    INSTALL_ENUM(UScriptCode, "SINDHI", USCRIPT_SINDHI);
    INSTALL_ENUM(UScriptCode, "WARANG_CITI", USCRIPT_WARANG_CITI);
#endif

#if U_ICU_VERSION_HEX >= 0x04080000
    INSTALL_ENUM(UScriptCode, "AFAKA", USCRIPT_AFAKA);
    INSTALL_ENUM(UScriptCode, "JURCHEN", USCRIPT_JURCHEN);
    INSTALL_ENUM(UScriptCode, "MRO", USCRIPT_MRO);
    INSTALL_ENUM(UScriptCode, "NUSHU", USCRIPT_NUSHU);
    INSTALL_ENUM(UScriptCode, "SHARADA", USCRIPT_SHARADA);
    INSTALL_ENUM(UScriptCode, "SORA_SOMPENG", USCRIPT_SORA_SOMPENG);
    INSTALL_ENUM(UScriptCode, "TAKRI", USCRIPT_TAKRI);
    INSTALL_ENUM(UScriptCode, "TANGUT", USCRIPT_TANGUT);
    INSTALL_ENUM(UScriptCode, "WOLEAI", USCRIPT_WOLEAI);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(49, 0, 0)
    INSTALL_ENUM(UScriptCode, "ANATOLIAN_HIEROGLYPHS", USCRIPT_ANATOLIAN_HIEROGLYPHS);
    INSTALL_ENUM(UScriptCode, "KHOJKI", USCRIPT_KHOJKI);
    INSTALL_ENUM(UScriptCode, "TIRHUTA", USCRIPT_TIRHUTA);
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
    INSTALL_ENUM(UScriptUsage, "NOT_ENCODED", USCRIPT_USAGE_NOT_ENCODED);
    INSTALL_ENUM(UScriptUsage, "UNKNOWN", USCRIPT_USAGE_UNKNOWN);
    INSTALL_ENUM(UScriptUsage, "EXCLUDED", USCRIPT_USAGE_EXCLUDED);
    INSTALL_ENUM(UScriptUsage, "LIMITED_USE", USCRIPT_USAGE_LIMITED_USE);
    INSTALL_ENUM(UScriptUsage, "ASPIRATIONAL", USCRIPT_USAGE_ASPIRATIONAL);
    INSTALL_ENUM(UScriptUsage, "RECOMMENDED", USCRIPT_USAGE_RECOMMENDED);
#endif
}
