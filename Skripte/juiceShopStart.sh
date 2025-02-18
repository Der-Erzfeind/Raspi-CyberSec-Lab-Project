#! /usr/bin/bash

dir="$(dirname "$0")/../../juice-shop"

sudo nmcli device wifi hotspot con-name "Wifi-JuiceShop" ssid "JuiceShop" password "JuiceShop" ifname wlan1

cd $dir
npm start &
