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
#further monitoring
#		nmcli monitor | grep -E 'wlan1: (connected|disconnected|using*)' >> "$logdir/.nmcliMonitor.tmp" &
#		iw event -T | sed '/phy/d' | awk '{ print strftime("[%H:%M:%S]"), $0 }' >> "$logdir/.iwEvent.tmp" &
#		nmcli monitor | grep -E 'wlan1: (connected|disconnected|using*)' | awk '{ print strftime("[%H:%M:%S]"), $0 }' >> "$logdir/.nmcliMonitor.tmp" &
#		journalctl -f -u NetworkManager | grep wlan1 | awk '{sub(/^.*[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]+)?/, ""); sub(/^ device \(wlan1\): /, ""); print $0}'

		printf "\n   started monitoring"
		sleep 0.5
	fi

elif [ "$cmd" == "off" ]; then
	kill $(pgrep -f "iw event -T") 
#	kill $(pgrep -f "nmcli monitor") 
	printf "\n   stopped monitoring"
	sleep 0.5
fi
