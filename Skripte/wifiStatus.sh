#!/bin/bash

if [ "$(nmcli dev | sed -n '/^wlan1[[:space:]]/s/^[^ ]*[ ]*[^ ]*[ ]*\([^ ]*\).*/\1/p')" == "disconnected" ]; then
	printf "\n   disconnected"
else
	if [ "$(sudo nmcli dev wifi show-password ifname wlan1 | sed -n "s/Security: //p")" == "WEP" ]; then
		connection="WEP"
		ssid=$(sudo cat /etc/NetworkManager/system-connections/Wifi-WEP.nmconnection | sed -n 's/ssid=//p')
		password=$(sudo cat /etc/NetworkManager/system-connections/Wifi-WEP.nmconnection | sed -n 's/wep-key0=//p')
		printf "\nSecurity: %s\nSSID: %s\nPassword: %s\n" $connection $ssid $password
	else
		printf "\n"
		sudo nmcli dev wifi show-password ifname wlan1
	fi
fi	

