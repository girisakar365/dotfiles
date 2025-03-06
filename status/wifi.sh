#!/bin/bash

# Function to get the current Wi-Fi signal strength
get_signal_strength() {
    local signal
    signal=$(nmcli -g IN-USE,SIGNAL dev wifi | grep '*' | awk -F: '{print $2}')
    echo "Wi-Fi: ${signal}%"
}

# Function to show Wi-Fi QR code (when hovered or clicked)
show_qr_code() {
    nmcli device wifi show
}

# Check argument for hover/click
if [[ $1 == "qr" ]]; then
    show_qr_code
else
    get_signal_strength
fi
