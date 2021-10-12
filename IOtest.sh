#!/bin/bash

IFS=$'\n'


./project
./project  << 'edit a1 asd'
printf 'exit\n' | ./project
