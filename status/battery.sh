#!/bin/sh

# Get battery status
STATE=$(upower -i $(upower -e | grep 'BAT') | grep 'state' | awk '{print $2}')
PERCENT=$(cat /sys/class/power_supply/BAT0/capacity)

# Set icons for charging/discharging
if [ "$STATE" = "charging" ]; then
    ICON=""
else
    ICON=""
fi

# Set icon for battery percentage 
if [ $PERCENT -gt 75 ] && [ $PERCENT -le 100 ]; then
    BAT=""
elif [ $PERCENT -gt 50 ] && [ $PERCENT -le 75 ]; then
    BAT=""
elif [ $PERCENT -gt 25 ] && [ $PERCENT -le 50 ]; then
    BAT=""
elif [ $PERCENT -gt 20 ] && [ $PERCENT -le 25 ]; then
    BAT=""
elif [ $PERCENT -gt 0 ] && [ $PERCENT -le 20 ]; then
    BAT=""
else
    BAT=""
fi
# Output in format suitable for slstatus
echo " $BAT : $PERCENT% $ICON "