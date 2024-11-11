#! /usr/bin/bash
cd ~/juice-shop
npm start &
sleep(1)
buffer=`ps auxwww | grep "node build/app"`
pid=$(echo "$buffer" | awk '{print $2}')
echo "$pid" > pid.txt
