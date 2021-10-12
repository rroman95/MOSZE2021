#!/bin/bash

IFS=$'\n'


./project >> testoutput.txt
printf 'exit\n' | ./project
