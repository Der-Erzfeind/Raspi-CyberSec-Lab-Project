#! /usr/bin/bash

UART_DEVICE="/dev/ttyS0"  
UART_SPEED=115200
stty -F $UART_DEVICE speed $UART_SPEED cs8 -cstopb -parenb

echo "reset" > "$UART_DEVICE"
sleep 1 
sudo nmcli device down wlan1 && echo "Wifi deactivated"
