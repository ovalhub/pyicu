/* ====================================================================
 * Copyright (c) 2004-2011 Open Source Applications Foundation.
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
#include "locale.h"
#include "iterators.h"
#include "macros.h"


/* ForwardCharacterIterator */

class t_forwardcharacteriterator : public _wrapper {
public:
    ForwardCharacterIterator *object;
};

static PyObject *t_forwardcharacteriterator_nextPostInc(t_forwardcharacteriterator *self);
static PyObject *t_forwardcharacteriterator_next32PostInc(t_forwardcharacteriterator *self);
static PyObject *t_forwardcharacteriterator_hasNext(t_forwardcharacteriterator *self);

static PyMethodDef t_forwardcharacteriterator_methods[] = {
    DECLARE_METHOD(t_forwardcharacteriterator, nextPostInc, METH_NOARGS),
    DECLARE_METHOD(t_forwardcharacteriterator, next32PostInc, METH_NOARGS),
    DECLARE_METHOD(t_forwardcharacteriterator, hasNext, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(ForwardCharacterIterator, t_forwardcharacteriterator, UObject,
             ForwardCharacterIterator, abstract_init, NULL);

/* CharacterIterator */

class t_characteriterator : public _wrapper {
public:
    CharacterIterator *object;
};

static PyObject *t_characteriterator_first(t_characteriterator *self);
static PyObject *t_characteriterator_firstPostInc(t_characteriterator *self);
static PyObject *t_characteriterator_first32(t_characteriterator *self);
static PyObject *t_characteriterator_first32PostInc(t_characteriterator *self);
static PyObject *t_characteriterator_last(t_characteriterator *self);
static PyObject *t_characteriterator_last32(t_characteriterator *self);
static PyObject *t_characteriterator_current(t_characteriterator *self);
static PyObject *t_characteriterator_current32(t_characteriterator *self);
static PyObject *t_characteriterator_next(t_characteriterator *self);
static PyObject *t_characteriterator_next32(t_characteriterator *self);
static PyObject *t_characteriterator_previous(t_characteriterator *self);
static PyObject *t_characteriterator_previous32(t_characteriterator *self);
static PyObject *t_characteriterator_setToStart(t_characteriterator *self);
static PyObject *t_characteriterator_setToEnd(t_characteriterator *self);
static PyObject *t_characteriterator_setIndex(t_characteriterator *self,
                                              PyObject *arg);
static PyObject *t_characteriterator_setIndex32(t_characteriterator *self,
                                                PyObject *arg);
static PyObject *t_characteriterator_hasPrevious(t_characteriterator *self);
static PyObject *t_characteriterator_startIndex(t_characteriterator *self);
static PyObject *t_characteriterator_endIndex(t_characteriterator *self);
static PyObject *t_characteriterator_getIndex(t_characteriterator *self);
static PyObject *t_characteriterator_getLength(t_characteriterator *self);
static PyObject *t_characteriterator_move(t_characteriterator *self,
                                          PyObject *args);
static PyObject *t_characteriterator_getText(t_characteriterator *self,
                                             PyObject *args);

static PyMethodDef t_characteriterator_methods[] = {
    DECLARE_METHOD(t_characteriterator, first, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, firstPostInc, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, first32, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, first32PostInc, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, last, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, last32, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, current, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, current32, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, next, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, next32, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, previous, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, previous32, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, setToStart, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, setToEnd, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, setIndex, METH_O),
    DECLARE_METHOD(t_characteriterator, setIndex32, METH_O),
    DECLARE_METHOD(t_characteriterator, hasPrevious, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, startIndex, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, endIndex, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, getIndex, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, getLength, METH_NOARGS),
    DECLARE_METHOD(t_characteriterator, move, METH_VARARGS),
    DECLARE_METHOD(t_characteriterator, getText, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CharacterIterator, t_characteriterator, ForwardCharacterIterator,
             CharacterIterator, abstract_init, NULL);

/* UCharCharacterIterator */

class t_ucharcharacteriterator : public _wrapper {
public:
    UCharCharacterIterator *object;
    PyObject *text;
};

static int t_ucharcharacteriterator_init(t_ucharcharacteriterator *self,
                                         PyObject *args, PyObject *kwds);
static PyObject *t_ucharcharacteriterator_setText(t_ucharcharacteriterator *self, PyObject *args);

static PyMethodDef t_ucharcharacteriterator_methods[] = {
    DECLARE_METHOD(t_ucharcharacteriterator, setText, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

static void t_ucharcharacteriterator_dealloc(t_ucharcharacteriterator *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->text);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(UCharCharacterIterator, t_ucharcharacteriterator,
             CharacterIterator, UCharCharacterIterator,
             t_ucharcharacteriterator_init, t_ucharcharacteriterator_dealloc);

/* StringCharacterIterator */

class t_stringcharacteriterator : public _wrapper {
public:
    StringCharacterIterator *object;
};

static int t_stringcharacteriterator_init(t_stringcharacteriterator *self,
                                          PyObject *args, PyObject *kwds);
static PyObject *t_stringcharacteriterator_setText(t_stringcharacteriterator *self, PyObject *args);

static PyMethodDef t_stringcharacteriterator_methods[] = {
    DECLARE_METHOD(t_stringcharacteriterator, setText, METH_VARARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(StringCharacterIterator, t_stringcharacteriterator,
             UCharCharacterIterator, StringCharacterIterator,
             t_stringcharacteriterator_init, NULL);

/* BreakIterator */

class t_breakiterator : public _wrapper {
public:
    BreakIterator *object;
    PyObject *text;
};

static PyObject *t_breakiterator_getText(t_breakiterator *self);
static PyObject *t_breakiterator_setText(t_breakiterator *self, PyObject *arg);
static PyObject *t_breakiterator_first(t_breakiterator *self);
static PyObject *t_breakiterator_last(t_breakiterator *self);
static PyObject *t_breakiterator_previous(t_breakiterator *self);
static PyObject *t_breakiterator_nextBoundary(t_breakiterator *self,
                                              PyObject *args);
static PyObject *t_breakiterator_current(t_breakiterator *self);
static PyObject *t_breakiterator_following(t_breakiterator *self,
                                           PyObject *arg);
static PyObject *t_breakiterator_preceding(t_breakiterator *self,
                                           PyObject *arg);
static PyObject *t_breakiterator_isBoundary(t_breakiterator *self,
                                            PyObject *arg);
static PyObject *t_breakiterator_getLocale(t_breakiterator *self,
                                           PyObject *args);
static PyObject *t_breakiterator_getLocaleID(t_breakiterator *self,
                                             PyObject *args);
static PyObject *t_breakiterator_createWordInstance(PyTypeObject *type,
                                                    PyObject *arg);
static PyObject *t_breakiterator_createLineInstance(PyTypeObject *type,
                                                    PyObject *arg);
static PyObject *t_breakiterator_createCharacterInstance(PyTypeObject *type,
                                                         PyObject *arg);
static PyObject *t_breakiterator_createSentenceInstance(PyTypeObject *type,
                                                        PyObject *arg);
static PyObject *t_breakiterator_createTitleInstance(PyTypeObject *type,
                                                     PyObject *arg);
static PyObject *t_breakiterator_getAvailableLocales(PyTypeObject *type);
static PyObject *t_breakiterator_getDisplayName(PyTypeObject *type,
                                                PyObject *args);

static PyMethodDef t_breakiterator_methods[] = {
    DECLARE_METHOD(t_breakiterator, getText, METH_NOARGS),
    DECLARE_METHOD(t_breakiterator, setText, METH_O),
    DECLARE_METHOD(t_breakiterator, first, METH_NOARGS),
    DECLARE_METHOD(t_breakiterator, last, METH_NOARGS),
    DECLARE_METHOD(t_breakiterator, previous, METH_NOARGS),
    DECLARE_METHOD(t_breakiterator, nextBoundary, METH_VARARGS),
    DECLARE_METHOD(t_breakiterator, current, METH_NOARGS),
    DECLARE_METHOD(t_breakiterator, following, METH_O),
    DECLARE_METHOD(t_breakiterator, preceding, METH_O),
    DECLARE_METHOD(t_breakiterator, isBoundary, METH_O),
    DECLARE_METHOD(t_breakiterator, getLocale, METH_VARARGS),
    DECLARE_METHOD(t_breakiterator, getLocaleID, METH_VARARGS),
    DECLARE_METHOD(t_breakiterator, createWordInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, createLineInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, createCharacterInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, createSentenceInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, createTitleInstance, METH_O | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, getAvailableLocales, METH_NOARGS | METH_CLASS),
    DECLARE_METHOD(t_breakiterator, getDisplayName, METH_VARARGS | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

static void t_breakiterator_dealloc(t_breakiterator *self)
{
    if (self->flags & T_OWNED)
        delete self->object;
    self->object = NULL;

    Py_CLEAR(self->text);

    Py_TYPE(self)->tp_free((PyObject *) self);
}

DECLARE_TYPE(BreakIterator, t_breakiterator, UObject, BreakIterator,
             abstract_init, t_breakiterator_dealloc);

/* RuleBasedBreakIterator */

class t_rulebasedbreakiterator : public _wrapper {
public:
    RuleBasedBreakIterator *object;
    PyObject *text;  /* used by inherited BreakIterator.setText() */
};

static int t_rulebasedbreakiterator_init(t_rulebasedbreakiterator *self,
                                         PyObject *args, PyObject *kwds);
static PyObject *t_rulebasedbreakiterator_getRules(t_rulebasedbreakiterator *self, PyObject *args);
static PyObject *t_rulebasedbreakiterator_getRuleStatus(t_rulebasedbreakiterator *self);

static PyMethodDef t_rulebasedbreakiterator_methods[] = {
    DECLARE_METHOD(t_rulebasedbreakiterator, getRules, METH_VARARGS),
    DECLARE_METHOD(t_rulebasedbreakiterator, getRuleStatus, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(RuleBasedBreakIterator, t_rulebasedbreakiterator,
             BreakIterator, RuleBasedBreakIterator,
             t_rulebasedbreakiterator_init, NULL);

/* DictionaryBasedBreakIterator */

class t_dictionarybasedbreakiterator : public _wrapper {
public:
    DictionaryBasedBreakIterator *object;
};

static int t_dictionarybasedbreakiterator_init(t_dictionarybasedbreakiterator *self, PyObject *args, PyObject *kwds);

static PyMethodDef t_dictionarybasedbreakiterator_methods[] = {
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(DictionaryBasedBreakIterator, t_dictionarybasedbreakiterator,
             RuleBasedBreakIterator, DictionaryBasedBreakIterator,
             t_dictionarybasedbreakiterator_init, NULL);

/* CanonicalIterator */

class t_canonicaliterator : public _wrapper {
public:
    CanonicalIterator *object;
};

static int t_canonicaliterator_init(t_canonicaliterator *self,
                                    PyObject *args, PyObject *kwds);
static PyObject *t_canonicaliterator_getSource(t_canonicaliterator *self,
                                               PyObject *args);
static PyObject *t_canonicaliterator_setSource(t_canonicaliterator *self,
                                               PyObject *arg);
static PyObject *t_canonicaliterator_reset(t_canonicaliterator *self);
static PyObject *t_canonicaliterator_next(t_canonicaliterator *self,
                                          PyObject *args);

static PyMethodDef t_canonicaliterator_methods[] = {
    DECLARE_METHOD(t_canonicaliterator, getSource, METH_VARARGS),
    DECLARE_METHOD(t_canonicaliterator, setSource, METH_O),
    DECLARE_METHOD(t_canonicaliterator, next, METH_VARARGS),
    DECLARE_METHOD(t_canonicaliterator, reset, METH_NOARGS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CanonicalIterator, t_canonicaliterator, UObject,
             CanonicalIterator, t_canonicaliterator_init, NULL);

/* CollationElementIterator */

class t_collationelementiterator : public _wrapper {
public:
    CollationElementIterator *object;
};

static PyObject *t_collationelementiterator_reset(t_collationelementiterator *self);
static PyObject *t_collationelementiterator_next(t_collationelementiterator *self);
static PyObject *t_collationelementiterator_previous(t_collationelementiterator *self);
static PyObject *t_collationelementiterator_setText(t_collationelementiterator *self, PyObject *arg);
static PyObject *t_collationelementiterator_getOffset(t_collationelementiterator *self);
static PyObject *t_collationelementiterator_setOffset(t_collationelementiterator *self, PyObject *arg);
static PyObject *t_collationelementiterator_getMaxExpansion(t_collationelementiterator *self, PyObject *arg);
static PyObject *t_collationelementiterator_strengthOrder(t_collationelementiterator *self, PyObject *arg);
static PyObject *t_collationelementiterator_primaryOrder(PyTypeObject *type, PyObject *arg);
static PyObject *t_collationelementiterator_secondaryOrder(PyTypeObject *type, PyObject *arg);
static PyObject *t_collationelementiterator_tertiaryOrder(PyTypeObject *type, PyObject *arg);
static PyObject *t_collationelementiterator_isIgnorable(PyTypeObject *type, PyObject *arg);

static PyMethodDef t_collationelementiterator_methods[] = {
    DECLARE_METHOD(t_collationelementiterator, setText, METH_O),
    DECLARE_METHOD(t_collationelementiterator, next, METH_VARARGS),
    DECLARE_METHOD(t_collationelementiterator, previous, METH_VARARGS),
    DECLARE_METHOD(t_collationelementiterator, reset, METH_NOARGS),
    DECLARE_METHOD(t_collationelementiterator, getOffset, METH_NOARGS),
    DECLARE_METHOD(t_collationelementiterator, setOffset, METH_O),
    DECLARE_METHOD(t_collationelementiterator, getMaxExpansion, METH_O),
    DECLARE_METHOD(t_collationelementiterator, strengthOrder, METH_O),
    DECLARE_METHOD(t_collationelementiterator, primaryOrder, METH_O | METH_CLASS),
    DECLARE_METHOD(t_collationelementiterator, secondaryOrder, METH_O | METH_CLASS),
    DECLARE_METHOD(t_collationelementiterator, tertiaryOrder, METH_O | METH_CLASS),
    DECLARE_METHOD(t_collationelementiterator, isIgnorable, METH_O | METH_CLASS),
    { NULL, NULL, 0, NULL }
};

DECLARE_TYPE(CollationElementIterator, t_collationelementiterator, UObject,
             CollationElementIterator, abstract_init, NULL);


/* ForwardCharacterIterator */

static PyObject *t_forwardcharacteriterator_nextPostInc(t_forwardcharacteriterator *self)
{
    UChar c = self->object->nextPostInc();

    if (c == ForwardCharacterIterator::DONE)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyInt_FromLong(c);
}

static PyObject *t_forwardcharacteriterator_next32PostInc(t_forwardcharacteriterator *self)
{
    UChar32 c = self->object->next32PostInc();

    if (c == ForwardCharacterIterator::DONE)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyInt_FromLong(c);
}

static PyObject *t_forwardcharacteriterator_hasNext(t_forwardcharacteriterator *self)
{
    int b = self->object->hasNext();
    Py_RETURN_BOOL(b);
}

static PyObject *t_forwardcharacteriterator_iter(t_forwardcharacteriterator *self)
{
    Py_RETURN_SELF();
}

static PyObject *t_forwardcharacteriterator_richcmp(t_forwardcharacteriterator *self, PyObject *arg, int op)
{
    int b = 0;
    ForwardCharacterIterator *i;

    if (!parseArg(arg, "P", TYPE_ID(ForwardCharacterIterator), &i))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *i;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}


/* CharacterIterator */

static PyObject *t_characteriterator_first(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->first());
}

static PyObject *t_characteriterator_firstPostInc(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->firstPostInc());
}

static PyObject *t_characteriterator_first32(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->first32());
}

static PyObject *t_characteriterator_first32PostInc(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->first32PostInc());
}

static PyObject *t_characteriterator_last(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->last());
}

static PyObject *t_characteriterator_last32(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->last32());
}

static PyObject *t_characteriterator_current(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->current());
}

static PyObject *t_characteriterator_current32(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->current32());
}

static PyObject *t_characteriterator_next(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->next());
}

static PyObject *t_characteriterator_next32(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->next32());
}

static PyObject *t_characteriterator_previous(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->previous());
}

static PyObject *t_characteriterator_previous32(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->previous32());
}

static PyObject *t_characteriterator_setToStart(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->setToStart());
}

static PyObject *t_characteriterator_setToEnd(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->setToEnd());
}

static PyObject *t_characteriterator_setIndex(t_characteriterator *self,
                                              PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong((long) self->object->setIndex(i));

    return PyErr_SetArgsError((PyObject *) self, "setIndex", arg);
}

static PyObject *t_characteriterator_setIndex32(t_characteriterator *self,
                                                PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong((long) self->object->setIndex32(i));

    return PyErr_SetArgsError((PyObject *) self, "setIndex32", arg);
}

static PyObject *t_characteriterator_hasPrevious(t_characteriterator *self)
{
    int b = self->object->hasPrevious();
    Py_RETURN_BOOL(b);
}

static PyObject *t_characteriterator_startIndex(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->startIndex());
}

static PyObject *t_characteriterator_endIndex(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->endIndex());
}

static PyObject *t_characteriterator_getIndex(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->getIndex());
}

static PyObject *t_characteriterator_getLength(t_characteriterator *self)
{
    return PyInt_FromLong((long) self->object->getLength());
}

static PyObject *t_characteriterator_move(t_characteriterator *self,
                                          PyObject *args)
{
    int delta;
    CharacterIterator::EOrigin origin;

    if (!parseArgs(args, "ii", &delta, &origin))
        return PyInt_FromLong((long) self->object->move(delta, origin));

    return PyErr_SetArgsError((PyObject *) self, "move", args);
}

static PyObject *t_characteriterator_getText(t_characteriterator *self,
                                             PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object->getText(_u);
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            self->object->getText(*u);
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getText", args);
}


/* UCharCharacterIterator */

static int t_ucharcharacteriterator_init(t_ucharcharacteriterator *self,
                                         PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    int len, start, end, pos;

    switch (PyTuple_Size(args)) {
      case 2:
        if (!parseArgs(args, "Wi", &u, &self->text, &len))
        {
            self->object = new UCharCharacterIterator(u->getTerminatedBuffer(), len);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 3:
        if (!parseArgs(args, "Wii", &u, &self->text, &len, &pos))
        {
            self->object = new UCharCharacterIterator(u->getTerminatedBuffer(), len, pos);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 5:
        if (!parseArgs(args, "Wiiii", &u, &self->text, &len, &start, &end, &pos))
        {
            self->object = new UCharCharacterIterator(u->getTerminatedBuffer(), len, start, end, pos);
            self->flags = T_OWNED;
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

static PyObject *t_ucharcharacteriterator_setText(t_ucharcharacteriterator *self, PyObject *args)
{
    UnicodeString *u;
    int32_t length;

    if (!parseArgs(args, "Wi", &u, &self->text, &length))
    {
        self->object->setText(u->getTerminatedBuffer(), length);  /* ref'd */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setText", args);
}


/* StringCharacterIterator */

static int t_stringcharacteriterator_init(t_stringcharacteriterator *self,
                                          PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    int start, end, pos;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            self->object = new StringCharacterIterator(*u);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArgs(args, "Si", &u, &_u, &pos))
        {
            self->object = new StringCharacterIterator(*u, pos);
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 4:
        if (!parseArgs(args, "Siii", &u, &_u, &start, &end, &pos))
        {
            self->object = new StringCharacterIterator(*u, start, end, pos);
            self->flags = T_OWNED;
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

static PyObject *t_stringcharacteriterator_setText(t_stringcharacteriterator *self, PyObject *args)
{
    UnicodeString *u, _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        self->object->setText(*u); /* copied */
        Py_RETURN_NONE;
    }

    return t_ucharcharacteriterator_setText((t_ucharcharacteriterator *) self, args);
}


/* BreakIterator */

static PyObject *t_breakiterator_getText(t_breakiterator *self)
{
    CharacterIterator *iterator = self->object->getText().clone();
    return wrap_CharacterIterator(iterator, T_OWNED);
}

static PyObject *t_breakiterator_setText(t_breakiterator *self, PyObject *arg)
{
    UnicodeString *u;

    if (!parseArg(arg, "W", &u, &self->text))
    {
        self->object->setText(*u); /* ref'd */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setText", arg);
}

static PyObject *t_breakiterator_first(t_breakiterator *self)
{
    return PyInt_FromLong(self->object->first());
}

static PyObject *t_breakiterator_last(t_breakiterator *self)
{
    return PyInt_FromLong(self->object->last());
}

static PyObject *t_breakiterator_previous(t_breakiterator *self)
{
    return PyInt_FromLong(self->object->previous());
}

static PyObject *t_breakiterator_nextBoundary(t_breakiterator *self,
                                              PyObject *args)
{
    int32_t n;

    switch (PyTuple_Size(args)) {
      case 0:
        return PyInt_FromLong(self->object->next());
      case 1:
        if (!parseArgs(args, "i", &n))
            return PyInt_FromLong(self->object->next(n));
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "nextBoundary", args);
}

static PyObject *t_breakiterator_current(t_breakiterator *self)
{
    return PyInt_FromLong(self->object->current());
}

static PyObject *t_breakiterator_following(t_breakiterator *self,
                                           PyObject *arg)
{
    int32_t offset;

    if (!parseArg(arg, "i", &offset))
        return PyInt_FromLong(self->object->following(offset));

    return PyErr_SetArgsError((PyObject *) self, "following", arg);
}

static PyObject *t_breakiterator_preceding(t_breakiterator *self,
                                           PyObject *arg)
{
    int32_t offset;

    if (!parseArg(arg, "i", &offset))
        return PyInt_FromLong(self->object->preceding(offset));

    return PyErr_SetArgsError((PyObject *) self, "preceding", arg);
}

static PyObject *t_breakiterator_isBoundary(t_breakiterator *self,
                                            PyObject *arg)
{
    int32_t i;

    if (!parseArg(arg, "i", &i))
    {
        int b = self->object->isBoundary(i);
        Py_RETURN_BOOL(b);
    }

    return PyErr_SetArgsError((PyObject *) self, "isBoundary", arg);
}

static PyObject *t_breakiterator_getLocale(t_breakiterator *self,
                                           PyObject *args)
{
    ULocDataLocaleType type;
    Locale locale;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(locale = self->object->getLocale(ULOC_VALID_LOCALE, status));
        return wrap_Locale(locale);
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            STATUS_CALL(locale = self->object->getLocale(type, status));
            return wrap_Locale(locale);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocale", args);
}

static PyObject *t_breakiterator_getLocaleID(t_breakiterator *self,
                                             PyObject *args)
{
    ULocDataLocaleType type;
    const char *id;

    switch (PyTuple_Size(args)) {
      case 0:
        STATUS_CALL(id = self->object->getLocaleID(ULOC_VALID_LOCALE, status));
        return PyString_FromString(id);
      case 1:
        if (!parseArgs(args, "i", &type))
        {
            STATUS_CALL(id = self->object->getLocaleID(type, status));
            return PyString_FromString(id);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getLocaleID", args);
}

static inline PyObject *wrap_BreakIterator(BreakIterator *iterator)
{
#if U_ICU_VERSION_HEX < 0x04060000
    if (iterator->getDynamicClassID() ==
        RuleBasedBreakIterator::getStaticClassID())
        return wrap_RuleBasedBreakIterator(
            (RuleBasedBreakIterator *) iterator, T_OWNED);
#else
    if (dynamic_cast<RuleBasedBreakIterator *>(iterator) != NULL)
        return wrap_RuleBasedBreakIterator(
            (RuleBasedBreakIterator *) iterator, T_OWNED);
#endif

    return wrap_BreakIterator(iterator, T_OWNED);
}

static PyObject *t_breakiterator_createWordInstance(PyTypeObject *type,
                                                    PyObject *arg)
{
    Locale *locale;
    BreakIterator *iterator;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(iterator = BreakIterator::createWordInstance(*locale, status));
        return wrap_BreakIterator(iterator);
    }

    return PyErr_SetArgsError(type, "createWordInstance", arg);
}

static PyObject *t_breakiterator_createLineInstance(PyTypeObject *type,
                                                    PyObject *arg)
{
    Locale *locale;
    BreakIterator *iterator;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(iterator = BreakIterator::createLineInstance(*locale, status));
        return wrap_BreakIterator(iterator);
    }

    return PyErr_SetArgsError(type, "createLineInstance", arg);
}

static PyObject *t_breakiterator_createCharacterInstance(PyTypeObject *type,
                                                         PyObject *arg)
{
    Locale *locale;
    BreakIterator *iterator;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(iterator = BreakIterator::createCharacterInstance(*locale, status));
        return wrap_BreakIterator(iterator);
    }

    return PyErr_SetArgsError(type, "createCharacterInstance", arg);
}

static PyObject *t_breakiterator_createSentenceInstance(PyTypeObject *type,
                                                        PyObject *arg)
{
    Locale *locale;
    BreakIterator *iterator;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(iterator = BreakIterator::createSentenceInstance(*locale, status));
        return wrap_BreakIterator(iterator);
    }

    return PyErr_SetArgsError(type, "createSentenceInstance", arg);
}

static PyObject *t_breakiterator_createTitleInstance(PyTypeObject *type,
                                                     PyObject *arg)
{
    Locale *locale;
    BreakIterator *iterator;

    if (!parseArg(arg, "P", TYPE_CLASSID(Locale), &locale))
    {
        STATUS_CALL(iterator = BreakIterator::createTitleInstance(*locale, status));
        return wrap_BreakIterator(iterator);
    }

    return PyErr_SetArgsError(type, "createTitleInstance", arg);
}

static PyObject *t_breakiterator_getAvailableLocales(PyTypeObject *type)
{
    int count;
    const Locale *locales = BreakIterator::getAvailableLocales(count);
    PyObject *dict = PyDict_New();

    for (int32_t i = 0; i < count; i++) {
        Locale *locale = (Locale *) locales + i;
        PyObject *obj = wrap_Locale(locale, 0);
        PyDict_SetItemString(dict, locale->getName(), obj);
	Py_DECREF(obj);
    }

    return dict;
}

static PyObject *t_breakiterator_getDisplayName(PyTypeObject *type,
                                                PyObject *args)
{
    Locale *locale, *display;
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 1:
        if (!parseArgs(args, "P",
                       TYPE_CLASSID(Locale),
                       &locale))
        {
            BreakIterator::getDisplayName(*locale, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 2:
        if (!parseArgs(args, "PU",
                       TYPE_CLASSID(Locale),
                       &locale, &u))
        {
            BreakIterator::getDisplayName(*locale, *u);
            Py_RETURN_ARG(args, 1);
        }
        break;
        if (!parseArgs(args, "PP",
                       TYPE_CLASSID(Locale),
                       TYPE_CLASSID(Locale),
                       &locale, &display))
        {
            BreakIterator::getDisplayName(*locale, *display, _u);
            return PyUnicode_FromUnicodeString(&_u);
        }
        break;
      case 3:
        if (!parseArgs(args, "PPU",
                       TYPE_CLASSID(Locale),
                       TYPE_CLASSID(Locale),
                       &locale, &display, &u))
        {
            BreakIterator::getDisplayName(*locale, *display, *u);
            Py_RETURN_ARG(args, 2);
        }
        break;
    }

    return PyErr_SetArgsError(type, "getDisplayName", args);
}

static PyObject *t_breakiterator_iter(t_breakiterator *self)
{
    Py_RETURN_SELF();
}

static PyObject *t_breakiterator_iter_next(t_breakiterator *self)
{
    int n = self->object->next();

    if (n == BreakIterator::DONE)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyInt_FromLong(n);
}



static PyObject *t_breakiterator_richcmp(t_breakiterator *self,
                                         PyObject *arg, int op)
{
    int b = 0;
    BreakIterator *i;

    if (!parseArg(arg, "P", TYPE_ID(BreakIterator), &i))
    {
        switch (op) {
          case Py_EQ:
          case Py_NE:
            b = *self->object == *i;
            if (op == Py_EQ)
                Py_RETURN_BOOL(b);
            Py_RETURN_BOOL(!b);
          case Py_LT:
          case Py_LE:
          case Py_GT:
          case Py_GE:
            PyErr_SetNone(PyExc_NotImplementedError);
            return NULL;
        }
    }

    return PyErr_SetArgsError((PyObject *) self, "__richcmp__", arg);
}


/* RuleBasedBreakIterator */

static int t_rulebasedbreakiterator_init(t_rulebasedbreakiterator *self,
                                         PyObject *args, PyObject *kwds)
{
    UnicodeString *u, _u;
    charsArg path, name;

    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new RuleBasedBreakIterator();
        self->flags = T_OWNED;
        break;
      case 1:
        if (!parseArgs(args, "S", &u, &_u))
        {
            RuleBasedBreakIterator *iterator;

            INT_STATUS_PARSER_CALL(iterator = new RuleBasedBreakIterator(*u, parseError, status));
            self->object = iterator;
            self->flags = T_OWNED;
            break;
        }
        PyErr_SetArgsError((PyObject *) self, "__init__", args);
        return -1;
      case 2:
        if (!parseArg(args, "fn", &path, &name))
        {
            RuleBasedBreakIterator *iterator;
            UDataMemory *data;
            UErrorCode status;

            status = U_ZERO_ERROR;
            data = udata_open(path, NULL, name, &status);
            if (U_FAILURE(status))
            {
                ICUException(status).reportError();
                return -1;
            }

            status = U_ZERO_ERROR;
            iterator = new RuleBasedBreakIterator(data, status);
            if (U_FAILURE(status))
            {
                udata_close(data);
                ICUException(status).reportError();
                return -1;
            }

            self->object = iterator;
            self->flags = T_OWNED;
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

static PyObject *t_rulebasedbreakiterator_getRules(t_rulebasedbreakiterator *self, PyObject *args)
{
    switch (PyTuple_Size(args)) {
      case 0:
      {
          UnicodeString u = self->object->getRules();
          return PyUnicode_FromUnicodeString(&u);
      }
      case 1:
      {
          UnicodeString *u;
          if (!parseArgs(args, "U", &u))
          {
              u->setTo(self->object->getRules());
              Py_RETURN_ARG(args, 0);
          }
          break;
      }
    }

    return PyErr_SetArgsError((PyObject *) self, "getRules", args);
}

static PyObject *t_rulebasedbreakiterator_getRuleStatus(t_rulebasedbreakiterator *self)
{
    return PyInt_FromLong(self->object->getRuleStatus());
}



/* DictionaryBasedBreakIterator */

static int t_dictionarybasedbreakiterator_init(t_dictionarybasedbreakiterator *self, PyObject *args, PyObject *kwds)
{
    switch (PyTuple_Size(args)) {
      case 0:
        self->object = new DictionaryBasedBreakIterator();
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


/* CanonicalIterator */

static int t_canonicaliterator_init(t_canonicaliterator *self,
                                    PyObject *args, PyObject *kwds)
{
    UnicodeString *u;
    UnicodeString _u;

    if (!parseArgs(args, "S", &u, &_u))
    {
        CanonicalIterator *iterator;

        INT_STATUS_CALL(iterator = new CanonicalIterator(*u, status));
        self->object = iterator;
        self->flags = T_OWNED;

        return 0;
    }

    PyErr_SetArgsError((PyObject *) self, "__init__", args);
    return -1;
}

static PyObject *t_canonicaliterator_getSource(t_canonicaliterator *self,
                                               PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        _u = self->object->getSource();
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            u->setTo(self->object->getSource());
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "getSource", args);
}

static PyObject *t_canonicaliterator_setSource(t_canonicaliterator *self,
                                               PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->setSource(*u, status)); /* transient */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setSource", arg);
}

static PyObject *t_canonicaliterator_reset(t_canonicaliterator *self)
{
    self->object->reset();
    Py_RETURN_NONE;
}

static PyObject *t_canonicaliterator_next(t_canonicaliterator *self,
                                          PyObject *args)
{
    UnicodeString *u;
    UnicodeString _u;

    switch (PyTuple_Size(args)) {
      case 0:
        _u = self->object->next();
        if (_u.isBogus())
            Py_RETURN_NONE;
        return PyUnicode_FromUnicodeString(&_u);
      case 1:
        if (!parseArgs(args, "U", &u))
        {
            u->setTo(self->object->next());
            Py_RETURN_ARG(args, 0);
        }
        break;
    }

    return PyErr_SetArgsError((PyObject *) self, "next", args);
}

static PyObject *t_canonicaliterator_iter(t_canonicaliterator *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_canonicaliterator_iter_next(t_canonicaliterator *self)
{
    UnicodeString u = self->object->next();

    if (u.isBogus())
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyUnicode_FromUnicodeString(&u);
}


/* CollationElementIterator */

static PyObject *t_collationelementiterator_reset(t_collationelementiterator *self)
{
    self->object->reset();
    Py_RETURN_NONE;
}

static PyObject *t_collationelementiterator_next(t_collationelementiterator *self)
{
    int i;
    STATUS_CALL(i = self->object->next(status));
    return PyInt_FromLong(i);
}

static PyObject *t_collationelementiterator_previous(t_collationelementiterator *self)
{
    int i;
    STATUS_CALL(i = self->object->previous(status));
    return PyInt_FromLong(i);
}

static PyObject *t_collationelementiterator_setText(t_collationelementiterator *self, PyObject *arg)
{
    UnicodeString *u, _u;

    if (!parseArg(arg, "S", &u, &_u))
    {
        STATUS_CALL(self->object->setText(*u, status)); /* copied */
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setText", arg);
}

static PyObject *t_collationelementiterator_getOffset(t_collationelementiterator *self)
{
    return PyInt_FromLong(self->object->getOffset());
}

static PyObject *t_collationelementiterator_setOffset(t_collationelementiterator *self, PyObject *arg)
{
    int offset;

    if (!parseArg(arg, "i", &offset))
    {
        STATUS_CALL(self->object->setOffset(offset, status));
        Py_RETURN_NONE;
    }

    return PyErr_SetArgsError((PyObject *) self, "setOffset", arg);
}

static PyObject *t_collationelementiterator_getMaxExpansion(t_collationelementiterator *self, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong(self->object->getMaxExpansion(i));

    return PyErr_SetArgsError((PyObject *) self, "getMaxExpansion", arg);
}

static PyObject *t_collationelementiterator_strengthOrder(t_collationelementiterator *self, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong(self->object->strengthOrder(i));

    return PyErr_SetArgsError((PyObject *) self, "strengthOrder", arg);
}

static PyObject *t_collationelementiterator_primaryOrder(PyTypeObject *type, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong(CollationElementIterator::primaryOrder(i));

    return PyErr_SetArgsError(type, "primaryOrder", arg);
}

static PyObject *t_collationelementiterator_secondaryOrder(PyTypeObject *type, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong(CollationElementIterator::secondaryOrder(i));

    return PyErr_SetArgsError(type, "secondaryOrder", arg);
}

static PyObject *t_collationelementiterator_tertiaryOrder(PyTypeObject *type, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
        return PyInt_FromLong(CollationElementIterator::tertiaryOrder(i));

    return PyErr_SetArgsError(type, "tertiaryOrder", arg);
}

static PyObject *t_collationelementiterator_isIgnorable(PyTypeObject *type, PyObject *arg)
{
    int i;

    if (!parseArg(arg, "i", &i))
    {
        i = CollationElementIterator::isIgnorable(i);
        Py_RETURN_BOOL(i);
    }

    return PyErr_SetArgsError(type, "isIgnorable", arg);
}

static PyObject *t_collationelementiterator_iter(t_collationelementiterator *self)
{
    self->object->reset();
    Py_RETURN_SELF();
}

static PyObject *t_collationelementiterator_iter_next(t_collationelementiterator *self)
{
    int n;

    STATUS_CALL(n = self->object->next(status));

    if (n == CollationElementIterator::NULLORDER)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }

    return PyInt_FromLong(n);
}

DEFINE_RICHCMP(CollationElementIterator, t_collationelementiterator);


void _init_iterators(PyObject *m)
{
    ForwardCharacterIteratorType_.tp_iter =
        (getiterfunc) t_forwardcharacteriterator_iter;
    ForwardCharacterIteratorType_.tp_iternext =
        (iternextfunc) t_forwardcharacteriterator_nextPostInc;
    ForwardCharacterIteratorType_.tp_richcompare =
        (richcmpfunc) t_forwardcharacteriterator_richcmp;
    BreakIteratorType_.tp_iter = (getiterfunc) t_breakiterator_iter;
    BreakIteratorType_.tp_iternext = (iternextfunc) t_breakiterator_iter_next;
    BreakIteratorType_.tp_richcompare = (richcmpfunc) t_breakiterator_richcmp;
    CanonicalIteratorType_.tp_iter = (getiterfunc) t_canonicaliterator_iter;
    CanonicalIteratorType_.tp_iternext =
        (iternextfunc) t_canonicaliterator_iter_next;
    CollationElementIteratorType_.tp_iter =
        (getiterfunc) t_collationelementiterator_iter;
    CollationElementIteratorType_.tp_iternext =
        (iternextfunc) t_collationelementiterator_iter_next;
    CollationElementIteratorType_.tp_richcompare =
        (richcmpfunc) t_collationelementiterator_richcmp;

    INSTALL_TYPE(ForwardCharacterIterator, m);
    INSTALL_TYPE(CharacterIterator, m);
    REGISTER_TYPE(UCharCharacterIterator, m);
    REGISTER_TYPE(StringCharacterIterator, m);
    INSTALL_TYPE(BreakIterator, m);
    REGISTER_TYPE(RuleBasedBreakIterator, m);
    REGISTER_TYPE(DictionaryBasedBreakIterator, m);
    REGISTER_TYPE(CanonicalIterator, m);
    REGISTER_TYPE(CollationElementIterator, m);

    INSTALL_STATIC_INT(ForwardCharacterIterator, DONE);
    INSTALL_STATIC_INT(BreakIterator, DONE);

    INSTALL_STATIC_INT(CharacterIterator, kStart);
    INSTALL_STATIC_INT(CharacterIterator, kCurrent);
    INSTALL_STATIC_INT(CharacterIterator, kEnd);

    INSTALL_STATIC_INT(CollationElementIterator, NULLORDER);
}
