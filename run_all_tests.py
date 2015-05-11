#!/usr/bin/python

import os

def get_cpp_includes(f, visited = set()):
    if f in visited:
        return []
    visited |= {f}
    res = []
    if f.endswith('.cpp'):
        res += [f]
    else:
        pot_cpp_file = f[:-2] + '.cpp'
        if os.path.exists(pot_cpp_file):
            res += get_cpp_includes(pot_cpp_file)

    fo = open(f)
    includes_lines = filter(lambda l : l.startswith("#include") and '.h"' in l, fo.readlines())
    include_files = map(lambda l : l[l.index(" ") + 2 : -2], includes_lines)
    fo.close()
    root = f[:f.rindex("/") + 1]
    for inc in include_files:
        res += get_cpp_includes(root + inc)
    return res

def run_tests_in_dir(d):
    cpp_files = []
    for f in os.listdir(d):
        if f.endswith('.cpp') or f.endswith('.h'):
            cpp_files += get_cpp_includes(d + '/' + f)
    
    command = "c++ -O2 -std=c++11 -o runner"
    for f in cpp_files:
        command += " " + f

    os.system(command)
    os.system("./util/checksol.py runner -d " + d + "/test")
    os.remove("runner")


for root, dirs, files in os.walk('.'):
    if root.endswith('tests'):
        dir_names = [root + "/" + d for d in os.listdir(root)]
        dir_names = filter(os.path.isdir, dir_names)
        map(run_tests_in_dir, dir_names)





