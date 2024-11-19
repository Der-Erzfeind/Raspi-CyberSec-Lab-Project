#! /usr/bin/bash
sudo nmcli device wifi hotspot con-name "Wifi-JuiceShop" ssid "JuiceShop" password "JuiceShop" ifname wlan1
#sudo nmcli connection down Wifi-JuiceShop
#sudo nmcli connection modify Wifi-JuiceShop band a
#sudo nmcli connection modify Wifi-JuiceShop channel 6 
#sudo nmcli connection modify Wifi-JuiceShop 802-11-wireless-security.key-mgmt none
#sudo nmcli connection modify Wifi-JuiceShop 802-11-wireless-security.auth-alg open
#sudo nmcli connection up Wifi-JuiceShop
cd ~/juice-shop
npm start &
