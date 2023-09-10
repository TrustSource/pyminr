import os
import sys

from setuptools import setup
from distutils.util import get_platform

minr_libs = []

if 'bdist_wheel' in sys.argv:
    if i := next((i for i, a in enumerate(sys.argv) if a in ['-p', '--plat-name']), None):
        plat_name = sys.argv[i + 1]
    else:
        plat_name = get_platform()

    plat_name = plat_name.replace('.', '_').replace('-', '_').split('_')

    if 'macosx' in plat_name:
        minr_libs = [os.path.join('lib', '*.dylib')]
    elif 'win' in plat_name:
        minr_libs = [os.path.join('lib', '*.dll')]
    else:
        minr_libs = [os.path.join('lib', '*.so')]

setup(
    name='pyminr',
    python_requires='>=3.8',
    packages=[
        'pyminr'
    ],
    version='0.1.1',
    description='A Python library wrapper for the SCANOSS Mining tool]',
    author='EACG GmbH',
    license='GPL-2.0',
    url='https://github.com/TrustSource/pyminr',
    download_url='https://github.com/TrustSource/pyminr',
    keywords=['SCANOSS', 'Minr'],
    classifiers=[],
    install_requires=[],
    package_data={
        'pyminr': minr_libs
    },
    setup_requires=[
        'wheel'
    ]
)