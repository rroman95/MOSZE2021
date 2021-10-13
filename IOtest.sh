#!/bin/bash

IFS=$'\n'


#./project input.csv < input.txt

echo "edit   a1    asd   
add 2  rows
add 2 columns
edit c2 LE GRANDE FINALE
save output.csv 
exit " | ./project
