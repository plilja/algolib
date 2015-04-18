#!/usr/bin/env python

import sys
import os
import tempfile
import glob
import filecmp
import time
from argparse import ArgumentParser

usage = "usage: %prog [options] program_to_test"
parser = ArgumentParser(description="Testrunner for programming puzzles, expects test files to be places in a directory called test")
parser.add_argument("-v", "--verbose", action="store_true", help="Be verbose", required=False, default=False)
parser.add_argument("-e", "--executor", dest="executor", default="", help="Execute the program with this executor (ex: java)")
parser.add_argument("program")
args = parser.parse_args()

program = args.program

if program[0] != '.':
    program = "./" + program

f = file(program)

program_path = os.path.dirname(program) 
test_search_path = program_path + "/test/*.in"

try:
    for test_file in glob.glob(test_search_path):
        start = time.time()
        os.system(args.executor + " " + program + "<" + test_file + " > answer.tmp")
        end = time.time()
        test_exp_file = test_file.replace(".in", ".ans")
        if not filecmp.cmp(test_exp_file, "answer.tmp"):
            print test_file + ", FAILED"
        elif args.verbose:
            print test_file + ", succes"
        if args.verbose:
            print test_file + ", execution time = " + str(end - start)
finally:
    if os.path.isfile("answer.tmp"):
        os.remove("answer.tmp")



