#!/bin/bash

IFS=$'\n'



while IFS='\n' read -r LINE; do
   echo "$LINE"
done < tests/input.txt | ./project testfile.csv

