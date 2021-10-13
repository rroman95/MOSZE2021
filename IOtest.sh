#!/bin/bash

IFS=$'\n'



while IFS='\n' read -r LINE; do
   echo "$LINE"
done < input.txt | ./project

<<ASD
echo "edit   a1    asd   
add 2  rows
add 2 columns
edit c2 LE GRANDE FINALE   
save output.csv   
exit      " | ./project
ASD


#./project input.csv < input.txt
<<VENTING
Feladom, mert valszeg valami linuxos line ending miatt ha az IOtest.sh fájlban
az exit parancs mögé nem rakok egyetlen egy (1 !!!!!!!) whitespace-t, akkor
valamiért a workfloban nem akarja felismerni,és a findCommandForSwitchStatement Unknown Command üzenetet dob.
Ezt a kódot itt vagy 6 óra szenvedés után hoztam össze, de tulajdonképpen ugyan azt csinálja, mint az 
"./project input.csv < input.txt" parancs, valamiért mind2 "megeszi" a szaros exit parancsot.
Aki rájön, hogy ez miért van, azt meghívom egy sörre/borra.
VENTING


