#!/bin/bash

scriptdir="$(dirname "$0")"

read -n 4 connection

if [ "$connection" == "WEP" ]; then
	exists=$(nmcli connection show | sed -n '/Wifi-WEP /p')
	if [ -z "$exists" ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WEP" ssid "WEPnetwork" password "TestSetup123" ifname wlan1
		sudo nmcli connection down Wifi-WEP
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.key-mgmt none
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.group wep104, wep40
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.auth-alg shared
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 "test1"
		sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.pmf 1
	fi
		sudo nmcli connection up Wifi-WEP
		echo "WEP" | $scriptdir/uartSendNI.sh

elif [ "$connection" == "WPA" ]; then
	exists=$(nmcli connection show | sed -n '/Wifi-WPA /p')
	if [ -z "$exists" ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA" ssid "WPAnetwork" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.key-mgmt wpa-psk
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.group tkip
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.pairwise tkip
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.proto wpa
		sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.pmf 1
	fi
		sudo nmcli connection up Wifi-WPA
		echo "WPA" | $scriptdir/uartSendNI.sh


elif [ "$connection" == "WPA2" ]; then 
	exists=$(nmcli connection show | sed -n '/Wifi-WPA2/p')
	if [ -z "$exists" ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA2" ssid "WPA2network" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA2
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.key-mgmt wpa-psk
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.group ccmp
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.pairwise ccmp
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.proto rsn
		sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.pmf 2
	fi
		sudo nmcli connection up Wifi-WPA2
		echo "WPA2" | $scriptdir/uartSendNI.sh

#WPA3 transition mode

#elif [ "$connection" == "WPAt" ]; then 
#	exists=$(nmcli connection show | sed -n '/Wifi-WPAt/p')
#	if [ -z "$exists" ]; then
#		sudo nmcli device wifi hotspot con-name "Wifi-WPAt" ssid "WPAtnetwork" password "TestSetup123" ifname wlan1 
#		sudo nmcli connection down Wifi-WPAt
#		sudo nmcli connection modify Wifi-WPAt 802-11-wireless-security.key-mgmt wpa-psk
#	fi
#		sudo nmcli connection up Wifi-WPAt
#		echo "WPAt" | $scriptdir/uartSendNI.sh

elif [ "$connection" == "WPA3" ]; then 
	exists=$(nmcli connection show | sed -n '/Wifi-WPA3/p')
	if [ -z "$exists" ]; then
		sudo nmcli device wifi hotspot con-name "Wifi-WPA3" ssid "WPA3network" password "TestSetup123" ifname wlan1 
		sudo nmcli connection down Wifi-WPA3
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.key-mgmt sae
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.group ccmp
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.pairwise ccmp
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.proto rsn
		sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.pmf 3
	fi
		sudo nmcli connection up Wifi-WPA3
		echo "WPA3" | $scriptdir/uartSendNI.sh
fi
