#!/bin/bash

read -n 3 cmd
if [ "$cmd" == "log" ]; then
	cat /home/pi/Raspi-CyberSec-Lab-Project/Logs/wifiMonitor.log


if [ "$cmd" == "on" ]; then
	$(iw event -T | sed '/phy/d') > /home/pi/Raspi-CyberSec-Lab-Project/Logs/wifiMonitor.log

elif [ "$cmd" == "off" ]; then
	kill $(pgrep -f "iw event -T") && echo "stopped monitoring"
fi
