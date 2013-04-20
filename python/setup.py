from distutils.core import setup

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

  install_requires=[
    'jinja-tools >= 0.1a6',
    ],
  packages=[
    'cfo',
    'cfo.jinja',
    ]
  )
