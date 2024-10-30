#! /usr/bin/bash
sudo nmcli device wifi hotspot con-name "Wifi-WPA2" ssid "WPA2test" password "Kurmeeljfkdas231" ifname wlan1 
sudo nmcli device down wlan1
sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.key-mgmt wpa-psk
sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.group ccmp
sudo nmcli connection modify Wifi-WPA2 802-11-wireless-security.proto rsn
sudo nmcli device up wlan1