#!/bin/bash

IFS=$'\n'



echo "edit a1 asd
add 2 rows
add 2 columns
edit c3 LE GRANDE FINALE
exit" | ./project 2>&1 | tee good_output.csv
