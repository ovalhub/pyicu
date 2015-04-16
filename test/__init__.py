# test package

import sys

if __name__ == "__main__":
    if sys.version_info >= (2, 7):
        import os, unittest

        def load_tests(loader, standard_tests, pattern):
            if pattern is None:
                pattern = 'test*.py'
            this_dir = os.path.dirname(__file__)
            package_tests = loader.discover(start_dir=this_dir, pattern=pattern)
            standard_tests.addTests(package_tests)
            return standard_tests

        unittest.main()
    else:
        print >>sys.stderr, 'Unit test discovery requires Python 2.7 or later'
        try:
            from pkg_resources import require
            with_setuptools = require('setuptools')[0].parsed_version
            print >>sys.stderr, "Use: 'python setup.py test' instead"
        except ImportError:
            pass
