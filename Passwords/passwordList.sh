#!/usr/bin/bash

cd ~/Bachelorarbeit/Passwords

min=1
max=$(wc -l < realhuman_phill.txt)  # Only get the line count
i=1

while [ $i -le 100 ]; do
    rand=$((RANDOM % (max - min + 1) + min))
    sed -n "${rand}p" realhuman_phill.txt >> passwords.txt
    echo $rand
    ((i++))  # Increment i
done

