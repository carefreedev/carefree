try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

REQUIRES = open('requirements.txt').read().strip().split('\n')

VERSION = open('VERSION').read().strip()

setup(
  name='carefree-objects',
  version=VERSION,
  description=(
    "A thread-safe object manager extension for C++"
    " - Python Tools"
    ),
  author='Stefan Zimmermann',
  author_email='zimmermann.code@gmail.com',
  url='http://bitbucket.org/StefanZimmermann/carefree-objects',

  license='LGPLv3',

  install_requires=REQUIRES,

  packages=[
    'cfo',
    'cfo.jinja',
    'cfo.jinja.macros',
    'cfo.pkg',
    ],
  package_data={
    'cfo.jinja.macros': [
      'cfo',
      ],
    }
  )
