/* ====================================================================
 * Copyright (c) 2005-2010 Open Source Applications Foundation.
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

#ifndef _common_h
#define _common_h

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <Python.h>

#if PY_VERSION_HEX < 0x02040000
#define Py_RETURN_NONE return Py_INCREF(Py_None), Py_None
#define Py_RETURN_TRUE return Py_INCREF(Py_True), Py_True
#define Py_RETURN_FALSE return Py_INCREF(Py_False), Py_False
#endif

#if PY_VERSION_HEX < 0x02050000
typedef int Py_ssize_t;
typedef inquiry lenfunc;
typedef intargfunc ssizeargfunc;
typedef intobjargproc ssizeobjargproc;
typedef intintargfunc ssizessizeargfunc;
typedef intintobjargproc ssizessizeobjargproc;
#endif

#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#include <unicode/locid.h>
#include <unicode/resbund.h>
#include <unicode/calendar.h>
#include <unicode/gregocal.h>
#include <unicode/format.h>
#include <unicode/datefmt.h>
#include <unicode/smpdtfmt.h>
#include <unicode/measfmt.h>
#include <unicode/msgfmt.h>
#include <unicode/numfmt.h>
#include <unicode/choicfmt.h>
#include <unicode/decimfmt.h>
#include <unicode/rbnf.h>
#include <unicode/measure.h>
#include <unicode/measunit.h>
#include <unicode/currunit.h>
#include <unicode/curramt.h>
#include <unicode/timezone.h>
#include <unicode/simpletz.h>
#include <unicode/dtfmtsym.h>
#include <unicode/dcfmtsym.h>
#include <unicode/strenum.h>
#include <unicode/chariter.h>
#include <unicode/uchriter.h>
#include <unicode/schriter.h>
#include <unicode/brkiter.h>
#include <unicode/rbbi.h>
#include <unicode/dbbi.h>
#include <unicode/caniter.h>
#include <unicode/coleitr.h>
#include <unicode/coll.h>
#include <unicode/tblcoll.h>
#include <unicode/ucsdet.h>
#include <unicode/uidna.h>
#include <unicode/translit.h>
#include <unicode/unifunct.h>
#include <unicode/unimatch.h>
#include <unicode/unifilt.h>
#include <unicode/uniset.h>
#include <unicode/usetiter.h>
#include <unicode/regex.h>
#include <unicode/normlzr.h>
#include <unicode/search.h>
#include <unicode/stsearch.h>

#define U_ICU_VERSION_HEX ((U_ICU_VERSION_MAJOR_NUM << 24) +    \
                           (U_ICU_VERSION_MINOR_NUM << 16) +    \
                           (U_ICU_VERSION_PATCHLEVEL_NUM << 8))

#if U_ICU_VERSION_HEX >= 0x04000000
#include <unicode/plurfmt.h>
#include <unicode/plurrule.h>
#include <unicode/dtintrv.h>
#include <unicode/dtitvinf.h>
#include <unicode/dtitvfmt.h>
#endif

#if U_ICU_VERSION_HEX >= 0x04020000
#include <unicode/tmutfmt.h>
#include <unicode/currpinf.h>
#endif

#if U_ICU_VERSION_HEX >= 0x04040000
#include <unicode/normalizer2.h>
#include <unicode/selfmt.h>
#endif

#if U_ICU_VERSION_HEX >= 0x04060000
#include <typeinfo>
#endif


#if U_ICU_VERSION_HEX < 0x04060000

typedef UClassID classid;

enum {
    UObject_ID,
    Replaceable_ID,
    MeasureUnit_ID,
    Measure_ID,
    StringEnumeration_ID,
    ForwardCharacterIterator_ID,
    CharacterIterator_ID,
    BreakIterator_ID,
    Format_ID,
    MeasureFormat_ID,
    DateFormat_ID,
    Calendar_ID,
    Collator_ID,
    UnicodeMatcher_ID,
    SearchIterator_ID
};

#else

typedef const char *classid;

#endif


U_NAMESPACE_USE

/* lifted from ustrenum.h */

U_NAMESPACE_BEGIN
class U_COMMON_API UStringEnumeration : public StringEnumeration {
public:
    UStringEnumeration(UEnumeration* uenum);
    virtual ~UStringEnumeration();
    virtual int32_t count(UErrorCode& status) const;
    virtual const UnicodeString* snext(UErrorCode& status);
    virtual void reset(UErrorCode& status);
    virtual UClassID getDynamicClassID() const;
private:
    UEnumeration *uenum; // owned
};
U_NAMESPACE_END

extern PyObject *PyExc_ICUError;
extern PyObject *PyExc_InvalidArgsError;

void _init_common(PyObject *m);

class ICUException {
private:
    PyObject *code;
    PyObject *msg;
public:
    EXPORT ICUException();
    EXPORT ICUException(UErrorCode status);
    EXPORT ICUException(UErrorCode status, char *format, ...);
    EXPORT ICUException(UParseError &pe, UErrorCode status);
    EXPORT ~ICUException();
    EXPORT PyObject *reportError();
};

EXPORT PyObject *PyUnicode_FromUnicodeString(UnicodeString *string);
EXPORT PyObject *PyUnicode_FromUnicodeString(const UChar *chars, int size);

EXPORT UnicodeString &PyString_AsUnicodeString(PyObject *object,
                                               const char *encoding,
                                               const char *mode,
                                               UnicodeString &string);
EXPORT UnicodeString &PyObject_AsUnicodeString(PyObject *object,
                                               const char *encoding,
                                               const char *mode,
                                               UnicodeString &string);
EXPORT UnicodeString &PyObject_AsUnicodeString(PyObject *object,
                                               UnicodeString &string);
EXPORT UnicodeString *PyObject_AsUnicodeString(PyObject *object);
EXPORT UDate PyObject_AsUDate(PyObject *object);

int abstract_init(PyObject *self, PyObject *args, PyObject *kwds);

#ifdef _MSC_VER

#define parseArgs __parseArgs
#define parseArg __parseArg

int __parseArgs(PyObject *args, const char *types, ...);
int __parseArg(PyObject *arg, const char *types, ...);

int _parseArgs(PyObject **args, int count, const char *types, va_list list);

#else

#define parseArgs(args, types, rest...) \
    _parseArgs(((PyTupleObject *)(args))->ob_item, \
               ((PyTupleObject *)(args))->ob_size, types, ##rest)

#define parseArg(arg, types, rest...) \
    _parseArgs(&(arg), 1, types, ##rest)

int _parseArgs(PyObject **args, int count, const char *types, ...);

#endif

int isUnicodeString(PyObject *arg);
int32_t toUChar32(UnicodeString& u, UChar32 *c, UErrorCode& status);
UnicodeString fromUChar32(UChar32 c);

int isInstance(PyObject *arg, classid id, PyTypeObject *type);
void registerType(PyTypeObject *type, classid id);

Formattable *toFormattable(PyObject *arg);
Formattable *toFormattableArray(PyObject *arg, int *len,
                                classid id, PyTypeObject *type);

UObject **pl2cpa(PyObject *arg, int *len, classid id, PyTypeObject *type);
PyObject *cpa2pl(UObject **array, int len, PyObject *(*wrap)(UObject *, int));

PyObject *PyErr_SetArgsError(PyObject *self, const char *name, PyObject *args);
PyObject *PyErr_SetArgsError(PyTypeObject *type, const char *name, PyObject *args);

#endif /* _common_h */
