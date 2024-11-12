#! /usr/bin/bash
cd ~/juice-shop
npm start &
sleep 10
buffer=`ps auxwww | grep "node build/app"`
pid=$(echo "$buffer" | awk 'NR==2 {print $2}')
echo "$pid" > pid.txt
echo server pid: $pid