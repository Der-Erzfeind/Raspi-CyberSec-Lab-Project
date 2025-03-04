#!/usr/bin/bash

scriptdir="$(dirname "$0")"
pwddir="$scriptdir/../Passwords"

read -n 4 connection
if [ "$connection" == "WEP" ]; then
	randNumber=$((RANDOM % $(wc -l < $pwddir/passwordsWEP.txt) +1))
	newpassword=$(sed -n "${randNumber}p" $pwddir/passwordsWEP.txt)
	sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 $newpassword
else
	randNumber=$((RANDOM % $(wc -l < $pwddir/passwordsWPA.txt) +1))
	newpassword=$(sed -n "${randNumber}p" $pwddir/passwordsWPA.txt)
	sudo nmcli connection modify Wifi-$connection 802-11-wireless-security.psk $newpassword
fi
if [ "$($scriptdir/wifiStatus.sh | xargs)" != "disconnected" ]; then
	sudo nmcli connection down Wifi-$connection && sudo nmcli connection up Wifi-$connection
fi
echo "password: $newpassword"
