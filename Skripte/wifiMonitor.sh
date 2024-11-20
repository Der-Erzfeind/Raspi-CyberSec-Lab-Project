#!/usr/bin/bash

read -n 3 state
if [ "$state" == "on" ]; then
	iw event -T | sed '/phy/d' & echo "started monitoring"
elif [ "$state" == "off" ]; then
	kill $(pgrep -f "iw event -T") && echo "stopped monitoring"
fi
