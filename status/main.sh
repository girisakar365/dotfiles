#!/bin/bash

datetime(){
    $HOME/dotfiles/status/date_time.sh
}

wifi(){
    $HOME/dotfiles/status/wifi.sh
}

battery(){
    $HOME/dotfiles/status/battery.sh
}

vol_perc(){
    $HOME/dotfiles/status/vol_perc.sh
}

while :; do
    xsetroot -name "$(datetime)|$(vol_perc)|$(wifi)|$(battery)"
    sleep 1
done
