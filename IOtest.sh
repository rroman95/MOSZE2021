#!/bin/bash

IFS=$'\n'


#./project input.csv < input.txt

while IFS= read -r line; do
    echo "Text read from file: $line"
done < input.txt

<<COMMENT
echo "edit   a1    asd   
add 2  rows
add 2 columns
edit c2 LE GRANDE FINALE
save output.csv 
exit" | ./project
COMMENT
