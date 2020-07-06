#!/usr/bin/env bash
set -e
rm -rf cmake-build-{debug,release} dist nlnum.egg-info build
python3.6 setup.py install
python3.6 setup.py sdist
twine upload dist/*
