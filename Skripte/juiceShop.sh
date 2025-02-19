#! /usr/bin/bash

juicedir="$(dirname "$0")/../../juice-shop"

read -n 3 cmd

if [ "$cmd" == "on" ]; then
	sudo nmcli device wifi hotspot con-name "Wifi-JuiceShop" ssid "JuiceShop" password "JuiceShop" ifname wlan1
	cd $juicedir
	npm start &

elif [ "$cmd" == "off" ]; then
	kill -s SIGINT $(pgrep -f "^node build/app$") && echo "juice-shop server stopped"
	sudo nmcli connection down Wifi-JuiceShop

fi


