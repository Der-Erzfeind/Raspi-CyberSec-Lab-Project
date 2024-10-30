#! /usr/bin/bash
sudo nmcli device wifi hotspot con-name "Wifi-WPA" ssid "WPAtest" password "Kurmeeljfkdas231" ifname wlan1 
sudo nmcli device down wlan1
sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.key-mgmt wpa-psk
sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.group tkip
sudo nmcli connection modify Wifi-WPA 802-11-wireless-security.proto wpa
sudo nmcli device up wlan1