#!/bin/bash

IFS=$'\n'


./project
printf  'edit a1 asd\n' | ./project
printf 'exit\n' | ./project
