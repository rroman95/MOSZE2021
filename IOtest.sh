#!/bin/bash

IFS=$'\n'


INPUT = "edit a1 asd"
INPUT | ./project
printf 'exit\n' | ./project
