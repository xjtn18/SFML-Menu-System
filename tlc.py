#!/usr/bin/env python3
#################################################
## File name: tlc.py
## File type: Python 3.8 source file
## Author: Jacob Nardone
## Created on: Thu Aug 13th, 2020
## About: 'tlc' -> 'total line count'
##		Takes abitrary number of directory names or file names as CL arguments. 
##		Counts total proper lines of code (non-empty).
#################################################

import sys
import os
import time




def count_file(filepath: str):
    line_count = 0
    with open(filepath, "rb") as f:
        for line in f:
            if line.strip():
                line_count += 1
    return line_count


def count(obj : str):
    tot_line_count = 0

    for root, subdirs, files in os.walk(os.path.abspath(obj)):
        for subdir in subdirs:
            # recursive search
            tot_line_count += count(os.path.join(root, subdir))
        for file in files:
            tot_line_count += count_file(os.path.join(root, file))

    return tot_line_count


if __name__ == "__main__":
    tot_line_count = 0 # stores the count of the non-whitespace lines in the given directories

    if len(sys.argv) == 1:
        print("Error: no directory names given")
        time.sleep(1)
        sys.exit()

    try:
        print("Counting lines in ", sys.argv[1:], ":", sep="")
        for obj in sys.argv[1:]:
            tot_line_count += count(obj)
        print("==>", tot_line_count, "lines counted.")

    except FileNotFoundError:
        print("Given directories / files not found.")
        time.sleep(1)



