#!/bin/bash

scriptdir="$(dirname "$0")"
UART_DEVICE="/dev/ttyS0"  
UART_SPEED=115200

if [ "$($scriptdir/wifiStatus.sh | xargs)" == "disconnected" ]; then
	printf "\n   wifi not connected"
	sleep 0.5
else
	stty -F $UART_DEVICE speed $UART_SPEED cs8 -cstopb -parenb
	echo "mqtt" > "$UART_DEVICE"
	printf "\n   started mqtt conversation"
	sleep 0.5	
fi
