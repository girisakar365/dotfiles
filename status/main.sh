#!/bin/bash

datetime(){
    ~/suckless/status/date_time.sh
}

wifi(){
    ~/suckless/status/wifi.sh
}

battery(){
    ~/suckless/status/battery.sh
}

vol_perc(){
    ~/suckless/status/vol_perc.sh
}

while :; do
    xsetroot -name "$(datetime) | $(vol_perc) | $(wifi) | $(battery)"
    sleep 1
done