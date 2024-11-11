#! /usr/bin/bash
pid=read "pid.txt"
kill -s SIGINT $pid
 
