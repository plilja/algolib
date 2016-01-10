#!/usr/bin/env python

import sys
import os
import tempfile
import glob
import filecmp

program = sys.argv[1]

if program[0] != '.':
    program = "./" + program

f = open(program)

program_path = os.path.dirname(program) 
test_search_path = program_path + "/test/*.in"

for test_file in glob.glob(test_search_path):
    test_exp_file = test_file.replace(".in", ".ans")
    if not os.path.isfile(test_exp_file):
        os.system(program + " < " + test_file + " > " + test_exp_file)


