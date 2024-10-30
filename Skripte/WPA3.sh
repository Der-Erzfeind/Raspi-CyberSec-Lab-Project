#! /usr/bin/bash
sudo nmcli device wifi hotspot con-name "Wifi-WPA3" ssid "WPA3test" password "Kurmeeljfkdas231" ifname wlan1 
sudo nmcli device down wlan1
sudo nmcli connection modify Wifi-WPA3 802-11-wireless-security.key-mgmt sae
sudo nmcli device up wlan1