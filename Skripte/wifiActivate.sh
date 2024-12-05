#! /usr/bin/bash

read -n 4 connection
if [ "$connection" == "WEP" ]; then
	exists=$(nmcli connection show | sed -n '/Wifi-WEP /p')
	if [ !$exists ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WEP" ssid "WEPtest" password "TestSetup123" ifname wlan1
		sudo nmcli connection down Wifi-WEP
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.key-mgmt none
		# sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.group wep104
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 "test1"
	fi
		sudo nmcli connection up Wifi-WEP
		echo "WEP" | $(dirname "$0")/uartSendNI.sh

elif [ "$connection" == "WPA" ]; then
	exists=$(nmcli connection show | sed -n '/Wifi-WPA /p')
	if [ !$exists ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA" ssid "WPAtest" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.key-mgmt wpa-psk
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.group tkip
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.proto wpa
	fi
		sudo nmcli connection up Wifi-WPA
		echo "WPA" | $(dirname "$0")/uartSendNI.sh


elif [ "$connection" == "WPA2" ]; then 
	exists=$(nmcli connection show | sed -n '/Wifi-WPA2/p')
	if [ !$exists ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA2" ssid "WPA2test" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA2
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.key-mgmt wpa-psk
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.group ccmp
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.proto rsn
	fi
		sudo nmcli connection up Wifi-WPA2
		echo "WPA2" | $(dirname "$0")/uartSendNI.sh

elif [ "$connection" == "WPA3" ]; then 
	exists=$(nmcli connection show | sed -n '/Wifi-WPA3/p')
	if [ !$exists ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA3" ssid "WPA3test" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA3
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.key-mgmt sae
	fi
		sudo nmcli connection up Wifi-WPA3
		echo "WPA3" | $(dirname "$0")/uartSendNI.sh
fi
