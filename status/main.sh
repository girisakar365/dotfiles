#!/bin/bash

datetime(){
    ./status/date_time.sh
}

wifi(){
    ./status/wifi.sh
}

battery(){
    ./status/battery.sh
}

vol_perc(){
    ./status/vol_perc.sh
}

while :; do
    xsetroot -name "$(datetime)|$(vol_perc)|$(wifi)|$(battery)"
    sleep 1
done
