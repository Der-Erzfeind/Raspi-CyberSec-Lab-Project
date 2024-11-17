#!/usr/bin/bash
#
sudo nmcli device down wlan1 
read -n 3 connection
if [ "$connection" == "WEP" ]; then
	randNumber=$((RANDOM % $(wc -l < ../passwords/passwordsWEP.txt) +1))
	newpassword=$(sed -n "${randNumber}p" ../passwords/passwordsWEP.txt)
	sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 $newpassword
else
	randNumber=$((RANDOM % $(wc -l < ../passwords/passwordsWPA.txt) +1))
	newpassword=$(sed -n "${randNumber}p" ../passwords/passwordsWPA.txt)
	sudo nmcli connection modify Wifi-$connection 802-11-wireless-security.psk $newpassword
fi
echo "password: $newpassword"
