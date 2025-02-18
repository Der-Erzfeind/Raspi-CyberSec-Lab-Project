#!/bin/bash

sudo cat "$(dirname "$0")/service.txt"  > /etc/systemd/system/PiSecLab.service
