#!/usr/bin/bash

cd ~/Bachelorarbeit/Passwords
lines=$(wc -l < 100kPasswords.txt)
i=1
while [ $i -le $lines ]; do
    currPassword=$(sed -n "${i}p" < 100kPasswords.txt)
    currCharCount=${#currPassword}
    if [ $currCharCount -ge 8 ] && [ $currCharCount -le 63 ]; then
        echo "$currPassword" >> passwordsWPA.txt
    fi
    if [ $currCharCount -eq 5 ] || [ $currCharCount -eq 13 ]; then
        echo "$currPassword" >> passwordsWEP.txt
    fi
    ((i++))
done
    
