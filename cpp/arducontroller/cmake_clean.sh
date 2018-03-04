#!/bin/bash
# Find and then delete all files under current directory (.) that:
#  1. contains cmake (case-&insensitive) in it's path (wholename)
#  2. name is not CMakeLists.txt and name is not cmake_clean.sh
find . -iwholename '*cmake*' -not -name CMakeLists.txt -not -name cmake_clean.sh -delete
