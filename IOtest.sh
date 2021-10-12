#!/bin/bash

IFS=$'\n'


./project
send "edit a1 asd"
printf 'exit\n' | ./project
