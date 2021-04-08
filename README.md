# README file for PyICU

## Welcome

Welcome to PyICU, a Python extension wrapping the ICU C++ libraries.

ICU stands for "International Components for Unicode".
These are the i18n libraries of the Unicode Consortium.
They implement much of the Unicode Standard,
many of its companion Unicode Technical Standards,
and much of Unicode CLDR.

The PyICU source code is hosted at https://gitlab.pyicu.org/main/pyicu.

The ICU homepage is http://site.icu-project.org/

See also the CLDR homepage at http://cldr.unicode.org/

## Installing PyICU

PyICU is a python extension implemented in C++ that wraps the C/C++ ICU library.
It is known to also work as a [PyPy](https://www.pypy.org/) extension.
Unless ``pkg-config`` and the ICU libraries and headers are already installed,
building PyICU from the sources on [PyPI](https://pypi.org/project/PyICU/)
involves more than just a ``pip`` call. Many operating systems distribute
pre-built binary packages of ICU and PyICU, see below.

  - Mac OS X
    - Ensure ICU is installed and can be found by `pkg-config` (as `icu-config` was [deprecated](http://userguide.icu-project.org/howtouseicu#TOC-C-Makefiles) as of ICU 63.1), either by following [ICU build instructions](https://unicode-org.github.io/icu/userguide/icu4c/build.html), or by using Homebrew:
      ```sh
      # install libicu (keg-only)
      brew install pkg-config icu4c

      # let setup.py discover keg-only icu4c via pkg-config
      export PATH="/usr/local/opt/icu4c/bin:/usr/local/opt/icu4c/sbin:$PATH"
      export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:/usr/local/opt/icu4c/lib/pkgconfig"
      ```
    - Install PyICU **with the same C++ compiler as your Python distribution**
      ([more info](https://gitlab.pyicu.org/main/pyicu/merge_requests/140#issuecomment-782283491)):
      ```sh
      # EITHER - when using a gcc-built CPython (e.g. from Homebrew)
      export CC="$(which gcc)" CXX="$(which g++)"
      # OR - when using system CPython or another clang-based CPython, ensure system clang is used (for proper libstdc++ https://gitlab.pyicu.org/main/pyicu/issues/5#issuecomment-291631507):
      unset CC CXX

      # avoid wheels from previous runs or PyPI
      pip install --no-binary=:pyicu: pyicu
      ```

  - Debian
    ```sh
    apt-get update
    
    # EITHER - from apt directly https://packages.debian.org/source/stable/pyicu
    apt-get install python3-icu
    # OR - from source
    apt-get install pkg-config libicu-dev
    pip install --no-binary=:pyicu: pyicu
    ```

  - Ubuntu: similar to Debian, there is a pyicu
    [package](https://packages.ubuntu.com/source/xenial/python/pyicu)
    available via ``apt``.

  - Alpine Linux: there is a pyicu
    [package](https://pkgs.alpinelinux.org/package/edge/community/x86/py3-icu)
    available via ``apk``.

  - NetBSD: there is a pyicu [package](https://pkgsrc.se/textproc/py-ICU)
    available via ``pkg_add``.

  - OpenBSD: there is a pyicu [package](https://openports.se/textproc/py-ICU)
    available via ``pkg_add``.

  - Other operating systems: see below.

## Building PyICU

Before building PyICU the ICU libraries must be built and installed. Refer
to each system's [instructions](https://unicode-org.github.io/icu/userguide/icu4c/build.html) for more information.

PyICU is built with setuptools:

   - verify that ``pkg-config`` is available (the ``icu-config`` program is
     [deprecated](http://userguide.icu-project.org/howtouseicu#TOC-C-Makefiles)
     as of ICU 63.1)
     ```sh
     pkg-config --cflags --libs icu-i18n
     ```
     If this command returns an error or doesn't return the paths expected
     then ensure that the ``INCLUDES``, ``LFLAGS``, ``CFLAGS`` and ``LIBRARIES``
     dictionaries in ``setup.py`` contain correct values for your platform.
     Starting with ICU 60, ``-std=c++11`` must appear in your CFLAGS or be the
     default for your C++ compiler.

   - build and install pyicu
     ```sh
     python setup.py build
     sudo python setup.py install
     ```

## Running PyICU

  - Mac OS X
    Make sure that ``DYLD_LIBRARY_PATH`` contains paths to the directory(ies)
    containing the ICU libs.

  - Linux & Solaris
    Make sure that ``LD_LIBRARY_PATH`` contains paths to the directory(ies)
    containing the ICU libs or that you added the corresponding ``-rpath``
    argument to ``LFLAGS``.

  - Windows
    Make sure that ``PATH`` contains paths to the directory(ies)
    containing the ICU DLLs.


## What's available

See the [CHANGES](https://gitlab.pyicu.org/main/pyicu/blob/main/CHANGES) file
for an up to date log of changes and additions.


## API Documentation

There is no API documentation for PyICU. The API for ICU is documented at
https://unicode-org.github.io/icu-docs/apidoc/released/icu4c/ and the
following patterns can be used to translate from the C++ APIs to the
corresponding Python APIs.

### strings

The ICU string type, [UnicodeString](https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/classicu_1_1UnicodeString.html), is a type pointing at a mutable array of [UChar](https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/umachine_8h.html#a6bb9fad572d65b305324ef288165e2ac) Unicode 16-bit wide characters and is described [here](https://unicode-org.github.io/icu-docs/apidoc/dev/icu4c/classicu_1_1UnicodeString.html#details). The Python 3 [str](https://docs.python.org/3/library/stdtypes.html#str) type is described [here](https://docs.python.org/3/library/stdtypes.html#index-26) and [here](https://docs.python.org/3/howto/unicode.html). The Python 2 [unicode](https://docs.python.org/2.7/reference/datamodel.html#index-23) type is described [here](https://docs.python.org/2.7/library/stdtypes.html#sequence-types-str-unicode-list-tuple-bytearray-buffer-xrange).

Because of their differences, ICU's and Python's string objects are not merged
into the same type when crossing the C++ boundary but converted.

ICU APIs taking ``UnicodeString`` arguments have been overloaded to also
accept arguments that are Python 3 ``str`` or Python 2 ``unicode`` objects.
Python 2 ``str`` objects are auto-decoded into ICU strings using the ``utf-8``
encoding.

To convert a Python 3 ``bytes`` or a Python 2 ``str`` object encoded in an
encoding other than ``utf-8`` to an ICU ``UnicodeString`` use the
``UnicodeString(str, encodingName)`` constructor.

ICU's C++ APIs accept and return ``UnicodeString`` arguments in several
ways: by value, by pointer or by reference.
When an ICU C++ API is documented to accept a ``UnicodeString`` reference
parameter, it is safe to assume that there are several corresponding
PyICU python APIs making it accessible in simpler ways:

For example, the ``'UnicodeString &Locale::getDisplayName(UnicodeString &)'``
API, documented
[here](https://unicode-org.github.io/icu-docs/apidoc/released/icu4c/classicu_1_1Locale.html#a61def321a9cfd9904b59e3f1897f835e),
can be invoked from Python in several ways:

1. The ICU way

        >>> from icu import UnicodeString, Locale
        >>> locale = Locale('pt_BR')
        >>> string = UnicodeString()
        >>> name = locale.getDisplayName(string)
        >>> name
        <UnicodeString: 'Portuguese (Brazil)'>
        >>> name is string
        True                  <-- string arg was returned, modified in place

2. The Python way

        >>> from icu import Locale
        >>> locale = Locale('pt_BR')
        >>> name = locale.getDisplayName()
        >>> name
        'Portuguese (Brazil)'

    A ``UnicodeString`` object was allocated and converted to a Python
    ``str`` object.

A UnicodeString can be converted to a Python unicode string with Python 3's
``str()`` or Python 2's ``unicode()`` constructor. The usual ``len()``,
comparison, `[]`` and ``[:]`` operators are all available, with the additional
twists that slicing is not read-only and that ``+=`` is also available since a
UnicodeString is mutable. For example:

    >>> name = locale.getDisplayName()
    'Portuguese (Brazil)'
    >>> name = UnicodeString(name)
    >>> name
    <UnicodeString: 'Portuguese (Brazil)'>
    >>> str(name)
    'Portuguese (Brazil)'
    >>> len(name)
    19
    >>> str(name)
    'Portuguese (Brazil)'
    >>> name[3]
    't'
    >>> name[12:18]
    <UnicodeString: 'Brazil'>
    >>> name[12:18] = 'the country of Brasil'
    >>> name
    <UnicodeString: 'Portuguese (the country of Brasil)'>
    >>> name += ' oh joy'
    >>> name
    <UnicodeString: 'Portuguese (the country of Brasil) oh joy'>

### error reporting

The C++ ICU library does not use C++ exceptions to report errors. ICU
C++ APIs return errors via a ``UErrorCode`` reference argument. All such
APIs are wrapped by Python APIs that omit this argument and throw an
``ICUError`` Python exception instead. The same is true for ICU APIs
taking both a ``ParseError`` and a ``UErrorCode``, they are both to be
omitted.

For example, the ``'UnicodeString &DateFormat::format(const Formattable &, UnicodeString &, FieldPosition &, UErrorCode &)'`` API, documented [here](https://unicode-org.github.io/icu-docs/apidoc/released/icu4c/classicu_1_1DateFormat.html#aae63209f1202550c91e2beed5691b062) is invoked from Python with:

    >>> from icu import DateFormat, Formattable
    >>> df = DateFormat.createInstance()
    >>> df
    <SimpleDateFormat: M/d/yy h:mm a>
    >>> f = Formattable(940284258.0, Formattable.kIsDate)
    >>> df.format(f)
    '10/18/99 3:04 PM'

Of course, the simpler ``'UnicodeString &DateFormat::format(UDate, UnicodeString &)'`` documented [here](https://unicode-org.github.io/icu-docs/apidoc/released/icu4c/classicu_1_1DateFormat.html#a5940ccf5676d3fa043d8255c55b7ddd1) can be used too:

    >>> from icu import DateFormat
    >>> df = DateFormat.createInstance()
    >>> df
    <SimpleDateFormat: M/d/yy h:mm a>
    >>> df.format(940284258.0)
    '10/18/99 3:04 PM'

### dates

ICU uses a double floating point type called ``UDate`` that represents the
number of milliseconds elapsed since 1970-jan-01 UTC for dates.

In Python, the value returned by the ``time`` module's ``time()``
function is the number of seconds since 1970-jan-01 UTC. Because of this
difference, floating point values are multiplied by 1000 when passed to
APIs taking ``UDate`` and divided by 1000 when returned as ``UDate``.

Python's ``datetime`` objects, with or without timezone information, can
also be used with APIs taking ``UDate`` arguments. The ``datetime``
objects get converted to ``UDate`` when crossing into the C++ layer.

### arrays

Many ICU API take array arguments. A list of elements of the array
element types is to be passed from Python.

### StringEnumeration

An ICU ``StringEnumeration`` has three ``next`` methods: ``next()`` which
returns ``str`` objects, ``unext()`` which returns ``str`` objects in Python 3
or ``unicode`` objects in Python 2 and ``snext()`` which returns
``UnicodeString`` objects. Any of these methods can be used as an iterator,
using the Python built-in ``iter`` function.

For example, let ``e`` be a ``StringEnumeration`` instance:

```python
e = TimeZone.createEnumeration()
[s for s in e] # a list of 'str' objects
[s for s in iter(e.unext, '')] # a list of 'str' or 'unicode' objects
[s for s in iter(e.snext, '')] # a list of 'UnicodeString' objects
```

### timezones

The ICU ``TimeZone`` type may be wrapped with an ``ICUtzinfo`` type for
usage with Python's ``datetime`` type. For example:

```python
from datetime import datetime
tz = ICUtzinfo(TimeZone.createTimeZone('US/Mountain'))
datetime.now(tz)
```

or, even simpler:

```python
tz = ICUtzinfo.getInstance('Pacific/Fiji')
datetime.now(tz)
```

To get the default time zone use:

```python
defaultTZ = ICUtzinfo.getDefault()
```

To get the time zone's id, use the ``tzid`` attribute or coerce the time
zone to a string:

```python
ICUtzinfo.getInstance('Pacific/Fiji').tzid -> 'Pacific/Fiji'
str(ICUtzinfo.getInstance('Pacific/Fiji')) -> 'Pacific/Fiji'
```
