
import os, sys

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

from distutils.spawn import find_executable

VERSION = '2.2'

try:
    from subprocess import check_output
except ImportError:
    from subprocess import Popen, PIPE


    def check_output(*popenargs):
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


try:
    ICU_VERSION = os.environ['ICU_VERSION']
except:
    try:
        ICU_VERSION = check_output(('icu-config', '--version')).strip()
        if sys.version_info >= (3,):
            ICU_VERSION = str(ICU_VERSION, 'ascii')
    except:
        raise RuntimeError('''
Please set the ICU_VERSION environment variable to the version of
ICU you have installed.
        ''')

print('''
Building PyICU %s for ICU %s
''' %(VERSION, ICU_VERSION))

CONFIGURE_WITH_ICU_CONFIG = {
    'darwin': True,
    'linux': True,
    'freebsd': False, # not tested
    'win32': False,   # no icu-config
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

CFLAGS = {
    'darwin': ['-DPYICU_VER="%s"' %(VERSION)],
    'linux': ['-DPYICU_VER="%s"' %(VERSION)],
    'freebsd': ['-DPYICU_VER="%s"' %(VERSION), '-std=c++11'],
    'win32': ['/Zc:wchar_t', '/EHsc', '/DPYICU_VER=\\"%s\\"' %(VERSION)],
    'sunos5': ['-DPYICU_VER="%s"' %(VERSION), '-std=c++11'],
    'cygwin': ['-DPYICU_VER="%s"' %(VERSION), '-D_GNU_SOURCE=1', '-std=c++11'],
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
    if CONFIGURE_WITH_ICU_CONFIG[platform]:
        configure_with_icu_config(
            _cflags, ('--cxxflags', '--cppflags'), 'CXXFLAGS')

if '--debug' in sys.argv:
    if 'PYICU_DEBUG_CFLAGS' in os.environ:
        _cflags += os.environ['PYICU_DEBUG_CFLAGS'].split(os.pathsep)
    else:
        _cflags += DEBUG_CFLAGS[platform]

if 'PYICU_LFLAGS' in os.environ:
    _lflags = os.environ['PYICU_LFLAGS'].split(os.pathsep)
else:
    _lflags = LFLAGS[platform]
    if CONFIGURE_WITH_ICU_CONFIG[platform]:
        configure_with_icu_config(_lflags, ('--ldflags',), 'LDFLAGS')

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
      version=VERSION,
      test_suite="test",
      url='https://github.com/ovalhub/pyicu',
      author='Andi Vajda',
      author_email='github@ovaltofu.org',
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
