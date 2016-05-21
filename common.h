/* ====================================================================
 * Copyright (c) 2005-2015 Open Source Applications Foundation.
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

#if !defined(PYPY_VERSION) && defined(PYPY_VERSION_NUM)
#define PYPY_VERSION
#endif

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

/* Python 2 uses String and Unicode, Python 3 Bytes and Unicode.
 * In PyICU, we use Bytes for everything that should be 8 bit in both
 * environments, i.e. String in Python 2 and Bytes in Python 3. We use
 * String for everything that should be a String in Python 2 and a
 * Unicode in Python 3. The assumption is that the argument will
 * always be ASCII only, and that we want the result to be represented
 * as a simple string literal without b or u modifier no matter the
 * environment. The definitions below establish these three flavours.
 */
#if PY_MAJOR_VERSION >= 3
# define Py_TPFLAGS_CHECKTYPES 0
# define PyInt_FromLong PyLong_FromLong
# define PyInt_CheckExact PyLong_CheckExact
# define PyInt_Check PyLong_Check
# define PyInt_AsLong PyLong_AsLong
# define PyString_FromString PyUnicode_FromString
# define PyString_FromStringAndSize PyUnicode_FromStringAndSize
# define PyString_FromFormatV PyUnicode_FromFormatV
# define PyString_FromFormat PyUnicode_FromFormat
# define PyString_Format PyUnicode_Format
#else
# define PyBytes_FromStringAndSize PyString_FromStringAndSize
# define PyBytes_Check PyString_Check
# define PyBytes_Size PyString_Size
# define PyBytes_AsStringAndSize PyString_AsStringAndSize
# define PyBytes_AS_STRING PyString_AS_STRING
# define PyBytes_GET_SIZE PyString_GET_SIZE
# define _PyBytes_Resize _PyString_Resize
# ifndef PyVarObject_HEAD_INIT
#  define PyVarObject_HEAD_INIT(type, size) PyObject_HEAD_INIT(type) size,
# endif
# ifndef Py_TYPE
#  define Py_TYPE(ob) (((PyObject*)(ob))->ob_type)
# endif
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
#include <unicode/udat.h>
#include <unicode/udatpg.h>
#include <unicode/dtptngen.h>
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
#include <unicode/sortkey.h>
#include <unicode/tblcoll.h>
#include <unicode/ucsdet.h>
#include <unicode/uidna.h>
#include <unicode/translit.h>
#include <unicode/ulocdata.h>
#include <unicode/unifunct.h>
#include <unicode/unimatch.h>
#include <unicode/unifilt.h>
#include <unicode/uniset.h>
#include <unicode/usetiter.h>
#include <unicode/regex.h>
#include <unicode/normlzr.h>
#include <unicode/search.h>
#include <unicode/stsearch.h>
#include <unicode/uscript.h>
#include <unicode/uchar.h>
#include <unicode/uversion.h>
#include <unicode/ushape.h>

#define VERSION_HEX(major, minor, patch) \
  (((major) << 24) | ((minor) << 16) | ((patch) << 8))

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
#include <unicode/uspoof.h>
#endif

#if U_ICU_VERSION_HEX >= 0x04040000
#include <unicode/normalizer2.h>
#include <unicode/selfmt.h>
#endif

#if U_ICU_VERSION_HEX >= 0x04060000
#include <typeinfo>
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(50, 0, 0)
#include <unicode/listformatter.h>
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(51, 0, 0)
#include <unicode/compactdecimalformat.h>
#include <unicode/unum.h>
#include <unicode/udisplaycontext.h>
#endif

#if U_ICU_VERSION_HEX >= VERSION_HEX(53, 0, 0)
#include <unicode/reldatefmt.h>
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
    SearchIterator_ID,
    ListFormatter_ID,
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

EXPORT PyObject *PyUnicode_FromUnicodeString(const UnicodeString *string);
EXPORT PyObject *PyUnicode_FromUnicodeString(const UChar *chars, int size);

EXPORT UnicodeString &PyBytes_AsUnicodeString(PyObject *object,
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

// helper class, to allow argument parsing with proper cleanup
class charsArg {
private:
    const char *str;
    PyObject *obj;

    void clear()
    {
        Py_XDECREF(obj);
    }

public:
    charsArg() : str(NULL), obj(NULL) {}

    ~charsArg()
    {
        clear();
    }

    const char *c_str() const
    {
        return str;
    }

    size_t size() const
    {
        return strlen(str);
    }

#if PY_VERSION_HEX >= 0x02070000
    // Allow using this class wherever a const char * is statically expected
    operator const char *() const
    {
        return str;
    }
#else
    // Old python APIs were extremely unclean about constness of char strings
    operator char *() const
    {
        return const_cast<char *>(str);
    }
#endif

    // Point to an existing bytes object. We don't own the buffer.
    void borrow(PyObject *bytes)
    {
        clear();
        obj = NULL;
        str = PyBytes_AS_STRING(bytes);
    }

    // Point to a newly created bytes object, which we own and will clean.
    void own(PyObject *bytes)
    {
        clear();
        obj = bytes;
        str = PyBytes_AS_STRING(bytes);
    }
};

#if defined(_MSC_VER) || defined(PYPY_VERSION)

#define parseArgs __parseArgs
#define parseArg __parseArg

int __parseArgs(PyObject *args, const char *types, ...);
int __parseArg(PyObject *arg, const char *types, ...);

#ifdef PYPY_VERSION
int _parseArgs(PyObject *args, int count, const char *types, va_list list);
#else
int _parseArgs(PyObject **args, int count, const char *types, va_list list);
#endif

#else

#define parseArgs(args, types, rest...) \
    _parseArgs(((PyTupleObject *)(args))->ob_item, \
               PyObject_Size(args), types, ##rest)

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
