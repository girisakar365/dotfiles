#!/bin/bash

# Get the link speed using iw (requires root or proper permissions)
speed=$(iw dev "$(iw dev | awk '$1=="Interface"{print $2}')" link | awk '/tx bitrate/ {print $3, $4}')

# Get signal strength as before
signal=$(nmcli -g IN-USE,SIGNAL dev wifi | grep '*' | awk -F: '{print $2}')

echo "  : ${signal}% - ${speed}"
