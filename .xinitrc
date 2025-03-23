#!/bin/sh

export PATH="$PATH:$HOME/suckless/scripts"
echo "PATH is: $PATH"  # Debugging output
./suckless/status/main.sh &
./.fehbg &
picom &
slstatus &
syndaemon -i 1.0 -t -k -d &

exec dwm
