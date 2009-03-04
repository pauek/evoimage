
from distutils.core import setup, Extension

evoimg = Extension('evoimg',
                   sources = ['pyevoimg.cc'],
                   include_dirs = ['../libevoimg'],
                   libraries = ['evoimg'],
                   library_dirs = ['../libevoimg'])

setup (name = 'evoimg',
       version = '0.0.1',
       description = 'Evolution of Images',
       ext_modules = [evoimg])
