#!/usr/bin/env python

import sys
import os
import tempfile
import glob
import filecmp
import time
from argparse import ArgumentParser

usage = "usage: %prog [options] program_to_test"
parser = ArgumentParser(description="""Testrunner for programming puzzles, runs a program against each 
        .in-file and checks the output against the corresponding .out-file using unix diff""")
parser.add_argument("-v", "--verbose", action="store_true", help="Be verbose", required=False, default=False)
parser.add_argument("-e", "--executor", dest="executor", default="", help="Execute the program with this executor (ex: java or python)")
parser.add_argument("-d", "--directory", dest="directory", default="", help="""The directory where test files with extensions .in 
        and .ans can be found (default is a a folder named test placed as 
        a subfolder to the folder where the program is located)""")
parser.add_argument("program")
args = parser.parse_args()

program = args.program

if program[0] != '.':
    program = "./" + program

f = open(program)

program_path = os.path.dirname(program) 
if args.directory:
    test_search_path = "%s/*.in" % args.directory
else:
    test_search_path = "%s/test/*.in" % program_path
success = True
tests_found = False

try:
    for test_file in glob.glob(test_search_path):
        tests_found = True
        start = time.time()
        os.system(args.executor + " " + program + "<" + test_file + " > answer.tmp")
        end = time.time()
        test_exp_file = test_file.replace(".in", ".ans")
        if not filecmp.cmp(test_exp_file, "answer.tmp"):
            success = False
            print(test_file + ", FAILED")
        elif args.verbose:
            print(test_file + ", succes")
        if args.verbose:
            print(test_file + ", execution time = " + str(end - start))
finally:
    if os.path.isfile("answer.tmp"):
        os.remove("answer.tmp")

if not tests_found:
    print("No test files found")
elif success:
    print("Success")
else:
    print("Failed (%s)" % program)

