#! /usr/bin/bash

juicedir="../../juice-shop"

read -n 3 cmd

if [ "$cmd" == "on" ]; then
	sudo nmcli connection up Wifi-JuiceShop
	cd $juicedir
	npm start &

elif [ "$cmd" == "off" ]; then
	kill -s SIGINT $(pgrep -f "^node build/app$") && echo "juice-shop server stopped"
	sudo nmcli connection down Wifi-JuiceShop

fi


