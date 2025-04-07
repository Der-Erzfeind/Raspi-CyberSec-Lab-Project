#!/bin/bash

read -n 1 cmd

if [ $cmd == 1 ]; then
	echo "activating SSH hotspot"
	sleep 2
	sudo nmcli connection up SSH
fi

if [ $cmd == 2 ]; then
	echo "connecting to Handy"
	sleep 2
	sudo nmcli connection up Handy
fi

if [ $cmd == 3 ]; then
	echo "restarting systemd service"
	sleep 2
	sudo systemctl daemon-reload
	sudo systemctl restart PiSecLab.service
fi

if [ $cmd == 4 ]; then
	sudo nmcli connection up "WLAN von Jonas"
	echo "connecting to WLAN von Jonas"
	sleep 2
fi

if [ $cmd == 5 ]; then
	echo "restarting now"
	sleep 2
	sudo reboot
fi
