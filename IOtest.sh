#!/bin/bash

IFS=$'\n'

# ./project input.csv < input.txt   <-- Opens project with input.csv as arg and streamt input.txt as command line inputs

echo "edit a1 asd
add 2 rows
add 2 columns
edit c2 LE GRANDE FINALE
save output.csv
exit" | ./project

