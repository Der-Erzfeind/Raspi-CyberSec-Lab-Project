#! /usr/bin/bash
pid=`cat ~/juice-shop/pid.txt`
kill -s SIGINT $pid
echo "juice-shop server stopped"
 
