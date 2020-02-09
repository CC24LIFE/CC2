#!/usr/bin/env python3

from setuptools import setup, find_packages
import os
setup(
    name         = 'CC2',
    version      = '0.1',
    description  = 'Client-Specific Equivalence Checking of C Programs version 2',
    scripts      = ['bin/CC2', 'bin/CLEVERC'],
    packages     = find_packages(),
    include_package_data=True,
    package_dir = {'CC2': 'CC2' },
    install_requires=[
        'pycparser>=0.1'
    ]
)