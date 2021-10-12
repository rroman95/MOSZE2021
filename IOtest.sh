#!/bin/bash

IFS=$'\n'


./project input.csv << EOF
echo "edit a1 asdasd
add 2 rows
add 2 columns
edit c3 LE GRANDE FINALE
save output.csv
exit"
EOF

