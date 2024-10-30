#! /usr/bin/bash
sudo nmcli device wifi hotspot con-name "Wifi-WEP" ssid "WEPtest" password "Kurmeeljfkdas231" ifname wlan1
sudo nmcli device down wlan1
sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.key-mgmt none
sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.group wep104
sudo nmcli connection modify Wifi-WEP 802-11-wireless-security.wep-key0 "61a3c4e8f2"
sudo nmcli device up wlan1