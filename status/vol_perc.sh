#!/bin/bash

# Run the wpctl command and extract the volume percentage (as a float) without the '%' sign
volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2*10}')
state=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | grep -o "\[MUTED\]")

# Display the volume percentage correctly
if [ "$state" = "[MUTED]" ]; then
    icon=""
else
    icon=""
fi
echo "$icon : ${volume}%"
