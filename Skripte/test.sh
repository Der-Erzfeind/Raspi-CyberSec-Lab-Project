#!/bin/bash

scriptdir="$(dirname "$0")"
logdir="$scriptdir/../Logs"
fifo_pipe="$logdir/wifiMonitor.fifo"

read -n 3 cmd

if [ "$cmd" == "del" ]; then
    > "$logdir/wifiMonitor.log"
    printf "\n   deleted log"
    sleep 0.5

elif [ "$cmd" == "on" ]; then
    if pgrep -f "iw event -T" > /dev/null; then
        printf "\n   monitoring already active"
    else
        [ -p "$fifo_pipe" ] || mkfifo "$fifo_pipe"

        cat "$fifo_pipe" | tee -a "$logdir/wifiMonitor.log" &

        iw event -T | sed '/phy/d' > "$fifo_pipe" 2>&1 &
        nmcli monitor | grep -E 'wlan1: (connected|disconnected|using*)' > "$fifo_pipe" 2>&1 &
#output noch nicht richtig
#        journalctl -f -u NetworkManager | grep wlan1 | awk '{sub(/^.*[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]+)?/, ""); sub(/^ device \(wlan1\): /, ""); print $0}' > "$fifo_pipe" 2>&1 &

        printf "\n   started monitoring"
        sleep 0.5
    fi

elif [ "$cmd" == "off" ]; then
    pkill -f "iw event -T"
    pkill -f "nmcli monitor"
#    pkill -f "journalctl"

    rm -f "$fifo_pipe"

    printf "\n   stopped monitoring"
    sleep 0.5
fi

