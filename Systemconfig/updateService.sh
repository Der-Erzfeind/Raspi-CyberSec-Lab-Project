#!/bin/bash

sudo cat "$(dirname "$0")/service.txt"  > /etc/systemd/system/PiSecLab.service

sudo systemctl enable PiSecLab.service
sudo systemctl disable getty@tty1.service
sudo systemctl daemon reload
sudo systemctl start PiSecLab.service
