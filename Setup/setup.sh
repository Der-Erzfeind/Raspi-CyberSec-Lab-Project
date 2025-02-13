#! /usr/bin/bash
sudo chmod +x ~/BA/Skripte/*.sh
g++ ~/BA/Program/main.cpp -Wall -Wextra -O2 -o main.out -lpigpio


# systemd service for starting application on Startup
sudo cat ./Systemconfig/service.txt > /etc/systemd/system/hackerypi.service
sudo systemctl install hackerypi.service
sudo systemctl daemon-reload
sudo systemctl restart hackerypi.service

# installation of juice shop



# mqtt setup

