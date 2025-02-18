#! /usr/bin/bash

appdir="$(dirname "$0")"

# make scripts executable
sudo chmod +x appdir/Skripte/*.sh

# compile program
make -C Program all

# systemd service for starting application on Startup
sudo cat appdir/Systemconfig/service.txt > /etc/systemd/system/PiSecLab.service
sudo systemctl install PiSecLab.service
sudo systemctl daemon-reload
sudo systemctl restart PiSecLab.service

# installation of juice shop



# mqtt setup

