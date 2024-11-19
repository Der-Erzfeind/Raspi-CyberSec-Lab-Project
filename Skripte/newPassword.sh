#!/usr/bin/bash
#
read -n 4 connection
if [ "$connection" == "WEP" ]; then
	randNumber=$((RANDOM % $(wc -l < ../passwords/passwordsWEP.txt) +1))
	newpassword=$(sed -n "${randNumber}p" ../passwords/passwordsWEP.txt)
	sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 $newpassword
else
	randNumber=$((RANDOM % $(wc -l < ../passwords/passwordsWPA.txt) +1))
	newpassword=$(sed -n "${randNumber}p" ../passwords/passwordsWPA.txt)
	sudo nmcli connection modify Wifi-$connection 802-11-wireless-security.psk $newpassword
fi
sudo nmcli connection down Wifi-$connection && sudo nmcli connection up Wifi-$connection
echo "password: $newpassword"
