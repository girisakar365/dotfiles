#!/bin/sh

export PATH="$PATH:$HOME/dotfiles/scripts"

./dotfiles/status/main.sh &
./.fehbg &
picom &
libinput-gestures &

exec dwm

