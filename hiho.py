#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re
import codecs
import sys
import argparse

class Entry:
    URL = r'http://hihocoder.com/problemset/problem/'
    def __init__(self, name=None, number=0):
        self.name = name
        self.number = number

    def parse(self, line):
        m = re.match(r'\|.*?\|\[(?P<name>.*?)\].*?\|\[(?P<number>.*?)\].*?\|', line, re.U)
        assert m, u'Malformed line: {}'.format(line).encode('utf-8')
        self.name = m.group('name')
        self.number = m.group('number')

    def __str__(self):
        return u'[{name}]({url}{number})|[{number}](solutions/{number})'.format(name=self.name, url=Entry.URL, number=self.number).encode('utf-8')

class Table:
    def __init__(self):
        self.entries = {}

    def parse(self, lines):
        for line in lines:
            e = Entry()
            e.parse(line)
            self.entries[e.number] = e

    def add(self, entry):
        if self.entries.get(entry.number, None):
            return False
        self.entries[entry.number] = entry
        return True

    def __str__(self):
        order = 1
        ret = []
        for k in sorted(self.entries):
            ret.append('|{order}|{content}|'.format(order=order, content=str(self.entries[k])))
            order += 1
        return '\n'.join(ret)

class ReadMe:
    def __init__(self, path):
        self.path = path
        self.header = []
        self.table = Table()
        self.trailor = []
        self.parse()

    def parse(self):
        table_start = False
        table_end = True
        with codecs.open(self.path, mode='r', encoding='utf-8') as fin:
            for line in fin.readlines():

                if not table_end and line == '\n':
                    table_end = True
                    line = '\n\n'

                if not table_start:
                    self.header.append(line)
                elif not table_end:
                    e = Entry()
                    e.parse(line)
                    self.table.add(e)
                else:
                    self.trailor.append(line)

                if not table_start and line.startswith('|---|-------|----------|'):
                    table_start = True
                    table_end = False

    def write(self, path=None):
        if not path:
            path = self.path
        with open(path, mode='w') as fout:
            fout.write(str(self))

    def add_solution(self, title, number):
        return self.table.add(Entry(title, number))

    def __str__(self):
        ret = []
        ret.append(''.join(self.header).encode('utf-8'))
        ret.append(str(self.table))
        ret.extend(''.join(self.trailor).encode('utf-8'))
        return ''.join(ret)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
            description="""description:
    hiho facilitates update README
""",
epilog="""examples:
  """)

    parser.add_argument("-n", "--number", type=str, metavar="<number>", required=True, help="Specify the question number")
    parser.add_argument("-t", "--title", type=str, metavar="<title>", required=True, help="Specify the question title")

    args = parser.parse_args(sys.argv[1:])
    args.title = args.title.decode('utf-8')

    r = ReadMe(r'./README.md')
    if r.add_solution(args.title, args.number):
        print 'Add success'
    else:
        print '{title}({number}) is already solved.'.format(title=args.title.encode('utf-8'), number=args.number)
    r.write()
