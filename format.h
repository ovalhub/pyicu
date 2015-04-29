/* ====================================================================
 * Copyright (c) 2004-2010 Open Source Applications Foundation.
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

#ifndef _format_h
#define _format_h

class t_format : public _wrapper {
public:
    Format *object;
};

extern PyTypeObject FormatType_;
extern PyTypeObject FieldPositionType_;
extern PyTypeObject ParsePositionType_;
#if U_ICU_VERSION_HEX >= 0x04000000
extern PyTypeObject PluralRulesType_;
#endif

PyObject *t_format_format(t_format *self, PyObject *args);
PyObject *wrap_Format(Format *format);
#if U_ICU_VERSION_HEX >= 0x04000000
PyObject *wrap_PluralRules(PluralRules *rules, int flag);
#endif

void _init_format(PyObject *m);


#endif /* _format_h */
