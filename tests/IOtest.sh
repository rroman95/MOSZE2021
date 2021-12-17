#!/bin/bash

IFS=$'\n'



while IFS='\n' read -r LINE; do
   echo "$LINE"
done < input.txt | ./project

