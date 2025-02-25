#!/usr/bin/bash

read -n 4 connection

UART_DEVICE="/dev/ttyS0"  
UART_SPEED=115200

stty -F $UART_DEVICE speed $UART_SPEED cs8 -cstopb -parenb

ssid=$($(dirname "$0")/wifiStatus.sh | sed -n "s/SSID: //p")
password=$($(dirname "$0")/wifiStatus.sh | sed -n "s/Password: //p")

echo "reset" > "$UART_DEVICE"
sleep 1

DATA="$connection $ssid $password"
echo "$DATA" > "$UART_DEVICE"
echo "Data sent: $DATA"

