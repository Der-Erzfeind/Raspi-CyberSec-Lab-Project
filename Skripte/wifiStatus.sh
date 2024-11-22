#!/usr/bin/bash

sleep 1
print "\033[2J\033[1;1H"; 
sudo nmcli dev wifi show-password
