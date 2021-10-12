#!/bin/bash

IFS=$'\n'


./project
INPUT = "edit a1 asd"
INPUT | ./project
printf 'exit\n' | ./project
