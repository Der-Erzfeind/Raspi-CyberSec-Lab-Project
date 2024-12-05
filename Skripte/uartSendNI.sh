#!/usr/bin/bash

read -n 4 connection


UART_DEVICE="/dev/ttyS0"  
UART_SPEED=115200

stty -F $UART_DEVICE speed $UART_SPEED cs8 -cstopb -parenb


if [ $(sudo nmcli dev wifi show-password | wc -l) -gt 4 ]; then
	ssid=$(sudo nmcli dev wifi show-password | sed -ne "1,4d" -e "s/SSID: //p")
	passwd=$(sudo nmcli dev wifi show-password | sed -ne "1,4d" -e "s/Password: //p")
else
	ssid=$(sudo nmcli dev wifi show-password | sed -n "s/SSID: //p")
	passwd=$(sudo nmcli dev wifi show-password | sed -n "s/Password: //p")
fi

DATA="$connection $ssid $passwd"

echo "$DATA" > "$UART_DEVICE"

echo "Data sent: $DATA"

