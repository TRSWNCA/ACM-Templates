#!/bin/bash

# Delete Generate Files
find . -name "*.in" -type f -print -exec rm -rf {} \;
find . -name "*.out" -type f -print -exec rm -rf {} \;

# Grenerate the README file
python modify.py

# Github commit
git add .
git commit -a
git push
