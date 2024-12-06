#!/bin/bash

read -n 4 connection

if [ "$connection" == "WEP" ]; then
	ssid=$(cat /etc/NetworkManager/system-connections/Wifi-WEP.nmconnection | sed -n 's/ssid=//p')
	password=$(cat /etc/NetworkManager/system-connections/Wifi-WEP.nmconnection | sed -n 's/wep-key0=//p')
	printf "\nSecurity: %s\nSSID: %s\nPassword: %s" $connection $ssid $password
fi
	
sleep 0.1
printf "\n"
sudo nmcli dev wifi show-password 

