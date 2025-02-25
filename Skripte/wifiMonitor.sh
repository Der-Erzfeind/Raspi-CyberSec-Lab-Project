#!/bin/bash

scriptdir="$(dirname "$0")"
logdir="$(dirname "$0")/../Logs"

read -n 3 cmd

if [ "$cmd" == "del" ]; then
	> "$logdir/wifiMonitor.log"
	printf "\n   deleted log"
	sleep 0.5

elif [ "$cmd" == "on" ]; then
	if [ "$(pgrep -f "iw event -T")" ]; then
		printf "\n   monitoring already active"
	else
		iw event -T | sed '/phy/d' >> "$logdir/wifiMonitor.log" &
#not working yet
		$(nmcli monitor | grep -E 'wlan1: (connected|disconnected|using*)') >> "$logdir/wifiMonitor.log" &
		printf "\n   started monitoring"
		sleep 0.5
	fi

elif [ "$cmd" == "off" ]; then
	kill $(pgrep -f "iw event -T") 
	kill $(pgrep -f "nmcli monitor") 
	printf "\n   stopped monitoring"
	sleep 0.5
fi
