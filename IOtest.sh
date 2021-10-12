#!/bin/bash

IFS=$'\n'


./project input.csv;echo "edit a1 asd
add 2 rows
add 2 columns
edit c3 LE GRANDE FINALE
save output.csv
exit" | ./project

