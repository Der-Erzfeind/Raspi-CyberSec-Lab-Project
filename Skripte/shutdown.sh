#!/bin/bash

dir="$(dirname "$0")"

$dir/wifiReset.sh
$dir/juiceShopStop.sh
echo "shutting down"
sudo shutdown now
