#!/usr/bin/python

import random, sys, string, argparse
from optparse import OptionParser

class randline:
    def __init__(self, filename, lo_hi, arr, stdin_file):
        if lo_hi:
            self.lines = arr
        elif filename == "no_file":
            self.lines = stdin_file
            if(len(self.lines) <= 0):
                return 0
        else:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()

    def chooseline(self):
        return random.choice(self.lines)

    def chooselineremove(self):
        word = random.choice(self.lines)
        self.lines.remove(word)
        return word

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... [FILE]
  or:  shuf -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-i", "--input-range",
                      action="store", dest="lo_hi", default=False,
                      help="treat each number LO through HI as an input line")
    parser.add_option("-n", "--head-count", default=sys.maxsize,
                      action="store", dest="count",
                      help="output at most COUNT lines")
    parser.add_option("-r", "--repeat",
                      action="store_true", dest="repeat", default=False,
                      help="output lines can be repeated")
    options, args = parser.parse_args(sys.argv[1:])

    try:
        count = int(options.count)
    except:
        parser.error("invalid COUNT: {0}".
                     format(options.count))
    if count < 0:
        parser.error("invalid line count: {0}".
                     format(count))

    if options.lo_hi:
        try:
            nums = options.lo_hi.split("-")
            num1 = int(nums[0])
            num2 = int(nums[1])
        except:
            parser.error("invalid input range '" + str(options.lo_hi) + "'".
                         format(options.lo_hi))
        if num2 < num1:
            parser.error("invalid input range '" + str(options.lo_hi) + "'".
                         format(options.lo_hi))
    lohiArr = []
    file_count = 0
    stdin_file = []

    if options.lo_hi:
        input_file = ""
        while num1 <= num2:
            lohiArr.append(str(num1)+'\n')
            num1 += 1
    
    if len(args) > 1 and not options.lo_hi:
        parser.error("wrong number of operands")

    try:
        input_file = args[0]
    except:
        input_file = "no_file"
    
    if input_file == "-":
        input_file = "no_file"

    if options.lo_hi and input_file != "no_file":
        print("segmentation fault")
        #Why would I even have to reproduce this. It's so dumb...
        return 0

    if options.lo_hi:
        file_count = len(lohiArr)
    elif input_file != "no_file":
        with open(input_file, 'r') as f:
            for line in f:
                file_count += 1
    else:
        stdin_file = sys.stdin.readlines()
        for line in stdin_file:
            file_count += 1

    if file_count < count and not options.repeat:
        count = file_count

    try:
        generator = randline(input_file, options.lo_hi, lohiArr, stdin_file)
        i = 0
        while i < count:
            if options.repeat:
                sys.stdout.write(generator.chooseline())
            else:
                sys.stdout.write(generator.chooselineremove())
            i+=1
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
