#!/bin/bash

IFS=$'\n'


INPUT = "edit a1 asd"
INPUT | ./project
printf 'edit a1 asd\n' | ./project
