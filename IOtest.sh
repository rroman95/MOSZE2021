#!/bin/bash

IFS=$'\n'

<<IGNORE
printf 'edit a1 asd\n' | ./project
printf 'add 2 rows\n' | ./project
printf 'add 2 columns\n' | ./project
printf 'edit c3 end\n' | ./project
IGNORE
printf 'exit\n' | ./project
