#!/bin/bash

# Run the wpctl command and extract the volume percentage (as a float) without the '%' sign
volume=$(wpctl get-volume @DEFAULT_AUDIO_SINK@ | awk '{print $2*10}')

# Display the volume percentage correctly
echo "${volume}"
