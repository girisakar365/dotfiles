#!/bin/bash

signal=$(nmcli -g IN-USE,SIGNAL dev wifi | grep '*' | awk -F: '{print $2}')
echo " : ${signal}%"