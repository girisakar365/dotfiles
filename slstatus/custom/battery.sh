#!/bin/sh

# Get battery status
STATE=$(upower -i $(upower -e | grep 'BAT') | grep 'state' | awk '{print $2}')
PERCENT=$(upower -i $(upower -e | grep 'BAT') | grep "percentage" | awk '{print $2}')

# Set icons for charging/discharging
if [ "$STATE" = "charging" ]; then
    ICON="↑"
else
    ICON="↓"
fi

# Output in format suitable for slstatus
echo "Battery: $PERCENT $ICON"
