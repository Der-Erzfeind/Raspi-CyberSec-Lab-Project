#!/bin/bash

scriptdir="$(dirname "$0")"
UART_DEVICE="/dev/ttyS0"  
UART_SPEED=115200

read -n 3 command

if [ "$command" == "on" ]; then
	if [ "$($scriptdir/wifiStatus.sh | xargs)" == "disconnected" ]; then
		printf "\n   wifi not connected"
		sleep 0.5
	else
		stty -F $UART_DEVICE speed $UART_SPEED cs8 -cstopb -parenb
		echo "mqtt" > "$UART_DEVICE"
		$scriptdir/../Program/mqtt.out &
		printf "\n   started mqtt conversation\n"
		sleep 0.5	
	fi
elif [ "$command" == "off" ]; then
	echo "reset" > "$UART_DEVICE"
	kill $(pgrep -f "mqtt.out") 
	printf "\n   stopped conversation\n"
	sleep 0.5	
fi
	
