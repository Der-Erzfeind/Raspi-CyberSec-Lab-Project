#!/bin/bash

scriptdir="$(dirname "$0")"
logdir="$(dirname "$0")/../Logs"

read -n 3 cmd
if [ "$cmd" == "log" ]; then
	cat $logdir/wifiMonitor.log


if [ "$cmd" == "on" ]; then
	$(iw event -T | sed '/phy/d') > $logdir/wifiMonitor.log

elif [ "$cmd" == "off" ]; then
	kill $(pgrep -f "iw event -T") && echo "stopped monitoring"
fi
