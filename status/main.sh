#!/bin/bash

datetime(){
    ~/dotfiles/status/date_time.sh
}

wifi(){
    ~/dotfiles/status/wifi.sh
}

battery(){
    ~/dotfiles/status/battery.sh
}

vol_perc(){
    ~/dotfiles/status/vol_perc.sh
}

while :; do
    xsetroot -name "    $(datetime) | $(vol_perc) | $(wifi) | $(battery)"
    sleep 1
done
