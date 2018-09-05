#!/usr/bin/env python3

import os
import sys
import yaml

path = '/afs/nd.edu/user34/jhill9/Systems/cse-20289-sp18-assignments/homework07/texts/'

books = os.listdir(path)

print("|{:^20}|{:^10}|{:^10}|{:^11}|".format('FILE', 'OLD SIZE', 'NEW SIZE', 'RATIO'))
print('|',('-')*18,'|',('-')*8,'|',('-')*8,'|',('-')*9,'|')

text = dict()

for b in books:
    old_size = 8*(os.stat(path + b).st_size)
    new_size = 0;
    text = yaml.load(os.popen('./huff -f yaml {}'.format(path + b)))
    encoding = ""
    for t in text:
        new_size += len(text[t]['encoding']) * (text[t]['count'])
    ratio = round((new_size/old_size*100), 2)
    print("|{:>20}|{:>10}|{:>10}|{:>10}%|".format(b, old_size, new_size, ratio))
