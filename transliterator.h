/* ====================================================================
 * Copyright (c) 2009-2010 Open Source Applications Foundation.
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

#ifndef _transliterator_h
#define _transliterator_h

class t_transliterator : public _wrapper {
public:
    Transliterator *object;
};


U_NAMESPACE_BEGIN

class U_EXPORT PythonTransliterator : public Transliterator {
  protected:
    t_transliterator *self;

  public:
    /**
     * ICU "poor man's RTTI", returns a UClassID for the actual class.
     */
    virtual UClassID getDynamicClassID() const;

    /**
     * ICU "poor man's RTTI", returns a UClassID for this class.
     */
    static UClassID getStaticClassID();

    PythonTransliterator(t_transliterator *self, UnicodeString& id);
    PythonTransliterator(t_transliterator *self, UnicodeString& id,
                         UnicodeFilter *adoptedFilter);

    /**
     * Copy constructor.
     */
    PythonTransliterator(const PythonTransliterator&);

    /**
     * Destructor.
     */
    virtual ~PythonTransliterator();

    /**
     * Transliterator API.
     */
    virtual Transliterator* clone(void) const;

    /**
     * Implements {@link Transliterator#handleTransliterate}.
     */
    virtual void handleTransliterate(Replaceable& text,
                                     UTransPosition& pos,
                                     UBool incremental) const;
};

U_NAMESPACE_END


extern PyTypeObject TransliteratorType;

PyObject *wrap_Transliterator(Transliterator *transliterator, int flags);
PyObject *wrap_Transliterator(const Transliterator &transliterator);

void _init_transliterator(PyObject *m);


#endif /* _transliterator_h */
