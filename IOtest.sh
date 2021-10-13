#!/bin/bash

IFS=$'\n'


#./project input.csv < input.txt

declare -a ARRAY
while IFS= read -r line; do
    echo "Text read from file: $line"
    ARRAY+=$line
done < input.txt
echo "Array elements:"

#echo ${#ARRAY[@]}

for i in ${ARRAY[@]}; do 
printf "$i\n" | ./project; 
done 

<<COMMENT
echo "edit   a1    asd   
add 2  rows
add 2 columns
edit c2 LE GRANDE FINALE
save output.csv 
exit" | ./project
COMMENT
