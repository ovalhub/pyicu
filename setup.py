
import os, sys

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

from distutils.spawn import find_executable

VERSION = '2.6'
ICU_MAX_MAJOR_VERSION = '68'  # max supported major version of ICU

try:
    from subprocess import check_output as subprocess_check_output

    def check_output(popenargs):
        print("(running '%s')" %(' '.join(popenargs)))
        return subprocess_check_output(popenargs)

except ImportError:
    from subprocess import Popen, PIPE

    def check_output(*popenargs):
        print("(running '%s')" %(' '.join(*popenargs)))
        process = Popen(stdout=PIPE, *popenargs)
        output, ignore = process.communicate()
        retcode = process.poll()
        if retcode:
            raise RuntimeError((retcode, popenargs[0], output))
        return output


def configure_with_icu_config(flags, config_args, label):
    try:
        output = check_output(('icu-config',) + config_args).strip()
        if sys.version_info >= (3,):
            output = str(output, 'ascii')
        flags.extend(output.split())
        if output:
            print('Adding %s="%s" from %s' % (label, output,
                                              find_executable('icu-config')))
    except:
        print('Could not configure %s with icu-config' %(label))
        raise


def configure_with_pkg_config(flags, config_args, label):
    try:
        output = check_output(('pkg-config',) + config_args + ('icu-i18n',)).strip()
        if sys.version_info >= (3,):
            output = str(output, 'ascii')
        flags.extend(output.split())
        if output:
            print('Adding %s="%s" from %s' % (label, output,
                                              find_executable('pkg-config')))
    except:
        print('Could not configure %s with pkg-config' %(label))
        raise


try:
    ICU_VERSION = os.environ['ICU_VERSION']
except:
    try:
        ICU_VERSION = check_output(('icu-config', '--version')).strip()
    except:
        try:
            ICU_VERSION = check_output(('pkg-config', '--modversion', 'icu-i18n')).strip()
        except:
            raise RuntimeError('''
Please install pkg-config on your system or set the ICU_VERSION environment
variable to the version of ICU you have installed.
        ''')
    if sys.version_info >= (3,):
        ICU_VERSION = str(ICU_VERSION, 'ascii')

print('''
Building PyICU %s for ICU %s (max ICU major version supported: %s)
''' %(VERSION, ICU_VERSION, ICU_MAX_MAJOR_VERSION))

CONFIGURE_WITH_ICU_CONFIG = {
    'darwin': True,
    'linux': True,
    'freebsd': False, # not tested
    'win32': False,   # no icu-config
    'sunos5': False,  # not tested
    'cygwin': False,  # not tested
}

CONFIGURE_WITH_PKG_CONFIG = {
    'darwin': False,  # no pkg-config ?
    'linux': True,
    'freebsd': False, # not tested
    'win32': False,   # no pkg-config ?
    'sunos5': False,  # not tested
    'cygwin': False,  # not tested
}

INCLUDES = {
    'darwin': [],
    'linux': [],
    'freebsd': ['/usr/local/include'],
    'win32': ['c:/icu/include'],
    'sunos5': [],
    'cygwin': [],
}

if sys.platform == 'win32' and sys.version_info < (3,9):
    ver_flag = '/D%s=\\"%s\\"'
else:
    ver_flag = '-D%s="%s"'

VER_FLAGS = [ver_flag %('PYICU_VER', VERSION),
             ver_flag %('PYICU_ICU_MAX_VER', ICU_MAX_MAJOR_VERSION)]

PEDANTIC_FLAGS = {
    'darwin': ['-pedantic'],
    'linux': ['-pedantic', '-Wno-variadic-macros'],
    'freebsd': ['-pedantic'],
    'win32': [],
    'sunos5': [],
    'cygwin': ['-pedantic'],
}

CFLAGS = {
    'darwin': [],
    'linux': [],
    'freebsd': ['-std=c++11'],
    'win32': ['/Zc:wchar_t', '/EHsc'],
    'sunos5': ['-std=c++11'],
    'cygwin': ['-D_GNU_SOURCE=1', '-std=c++11'],
}

# added to CFLAGS when setup is invoked with --debug
DEBUG_CFLAGS = {
    'darwin': ['-O0', '-g', '-DDEBUG'],
    'linux': ['-O0', '-g', '-DDEBUG'],
    'freebsd': ['-O0', '-g', '-DDEBUG'],
    'win32': ['/Od', '/DDEBUG'],
    'sunos5': ['-DDEBUG'],
    'cygwin': ['-Og', '-g', '-DDEBUG'],
}

LFLAGS = {
    'darwin': [],
    'linux': [],
    'freebsd': ['-L/usr/local/lib'],
    'win32': ['/LIBPATH:c:/icu/lib'],
    'sunos5': [],
    'cygwin': [],
}

LIBRARIES = {
    'darwin': [],
    'linux': [],
    'freebsd': ['icui18n', 'icuuc', 'icudata'],
    'win32': ['icuin', 'icuuc', 'icudt'],
    'sunos5': ['icui18n', 'icuuc', 'icudata'],
    'cygwin': ['icui18n', 'icuuc', 'icudata'],
}

platform = sys.platform
if platform.startswith(('linux', 'gnu')):
    platform = 'linux'
elif platform.startswith('freebsd'):
    platform = 'freebsd'

if 'PYICU_INCLUDES' in os.environ:
    _includes = os.environ['PYICU_INCLUDES'].split(os.pathsep)
else:
    _includes = INCLUDES[platform]

if 'PYICU_CFLAGS' in os.environ:
    _cflags = os.environ['PYICU_CFLAGS'].split(os.pathsep)
else:
    _cflags = CFLAGS[platform]
    try:
        if CONFIGURE_WITH_ICU_CONFIG[platform]:
            try:
                configure_with_icu_config(
                    _cflags, ('--cxxflags', '--cppflags'), 'CFLAGS')
            except:
                if CONFIGURE_WITH_PKG_CONFIG[platform]:
                    configure_with_pkg_config(_cflags, ('--cflags',), 'CFLAGS')
                else:
                    raise
        elif CONFIGURE_WITH_PKG_CONFIG[platform]:
            configure_with_pkg_config(_cflags, ('--cflags',), 'CFLAGS')
    except:
        if not _cflags:
            raise RuntimeError('''
Please install pkg-config on your system or set the PYICU_CFLAGS environment 
variable to the flags required by the C++ compiler to find the header files
for ICU, and possibly -std=c++11 if using ICU version >= 60
            ''')

if '--debug' in sys.argv:
    if 'PYICU_DEBUG_CFLAGS' in os.environ:
        _cflags += os.environ['PYICU_DEBUG_CFLAGS'].split(os.pathsep)
    else:
        _cflags += DEBUG_CFLAGS[platform]

_cflags += VER_FLAGS # + PEDANTIC_FLAGS[platform]

if 'PYICU_LFLAGS' in os.environ:
    _lflags = os.environ['PYICU_LFLAGS'].split(os.pathsep)
else:
    _lflags = LFLAGS[platform]
    try:
        if CONFIGURE_WITH_ICU_CONFIG[platform]:
            try:
                configure_with_icu_config(_lflags, ('--ldflags',), 'LFLAGS')
            except:
                if CONFIGURE_WITH_PKG_CONFIG[platform]:
                    configure_with_pkg_config(_lflags, ('--libs',), 'LFLAGS')
                else:
                    raise
        elif CONFIGURE_WITH_PKG_CONFIG[platform]:
            configure_with_pkg_config(_lflags, ('--libs',), 'LFLAGS')
    except:
        if not _lflags:
            raise RuntimeError('''
Please install pkg-config on your system or set the PYICU_LFLAGS environment
variable to the flags required by the linker to find the libraries for ICU
            ''')
      

if 'PYICU_LIBRARIES' in os.environ:
    _libraries = os.environ['PYICU_LIBRARIES'].split(os.pathsep)
elif ICU_VERSION < '58':
    _libraries = LIBRARIES[platform][:] + ['icule']
else:
    _libraries = LIBRARIES[platform]

if sys.version_info < (2, 4):
    def sorted(iterable, *args, **kwargs):
        iterable = list(iterable)
        iterable.sort(*args, **kwargs)
        return iterable


setup(name="PyICU",
      description='Python extension wrapping the ICU C++ API',
      long_description=open('README.md').read(),
      long_description_content_type="text/markdown",
      version=VERSION,
      test_suite="test",
      url='https://github.com/ovalhub/pyicu',
      author='Andi Vajda',
      author_email='github@ovaltofu.org',
      license='MIT',
      classifiers=[
          'Development Status :: 5 - Production/Stable',
          'Environment :: Console',
          'Intended Audience :: Developers',
          'License :: OSI Approved',
          'Operating System :: OS Independent',
          'Programming Language :: C++',
          'Programming Language :: Python',
          'Programming Language :: Python :: 2',
          'Programming Language :: Python :: 3',
          'Programming Language :: Python :: Implementation :: CPython',
          'Programming Language :: Python :: Implementation :: PyPy',
          'Topic :: Software Development :: Localization',
          'Topic :: Software Development :: Internationalization'],
      ext_modules=[Extension('_icu',
                             [filename for filename in sorted(os.listdir(os.curdir))
                              if filename.endswith('.cpp')],
                             include_dirs=_includes,
                             extra_compile_args=_cflags,
                             extra_link_args=_lflags,
                             libraries=_libraries)],
      packages=['icu'],
      py_modules=['PyICU'],
      tests_require=['pytest', 'six'])
