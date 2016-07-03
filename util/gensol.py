#!/usr/bin/env python

import sys
import os
import glob
from argparse import ArgumentParser

parser = ArgumentParser(description="Generate ans-files from a solution known to be correct")
parser.add_argument("-e", "--executor", dest="executor", default="", help="Execute the program with this executor (ex: java or python)")
parser.add_argument("program")
args = parser.parse_args()

prog = args.program
if prog[0] != '.':
    prog = './' + prog

command = prog
if args.executor:
    command = args.executor + ' ' + command

program_path = os.path.dirname(prog) 
test_search_path = program_path + "/test/*.in"

for test_file in glob.glob(test_search_path):
    test_exp_file = test_file.replace(".in", ".ans")
    if not os.path.isfile(test_exp_file):
        os.system(command + " < " + test_file + " > " + test_exp_file)


