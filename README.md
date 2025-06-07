# MY DESKTOP ENVIRONMENT

## 1. PATCHES

### DWM PATCHES:

1. alt-tab: For switching working window.
2. fibonacci: Tailing in a clean order
3. restartsig: Refresh dwm without restarting x11 server.
4. uselessgap: Butifies the layout.

### DMENU PATCHES:
1. alpha: for tranparency
2. bar height: for managing size
3. center: to put it on the center
4. grid: for grid layout (of no use rn)
5. password: for auth into any thing using dmenu

### ST PATCHES:
1. scrollback: for scroll function on st
2. alpha: transparency

### SLOCK PATCHES: NONE

__NOTE__: You can see the .diff file on every folder.

## 2.  CONF

1. [40-libinput.conf](./conf/40-libinput.conf):
    
    For Touch Pad natural scroll and other confg.

2. [libinput-gestures.conf](./conf/libinput-gestures.conf)

    For touchpad gesture contorl.

## 3. Status Scripts
Date, time, wifi, volume and battery info via [status](./status/) is displayed on status bar.

## 4. Other Scripts:
They are for running any app or services through dmenu. Include the path of [scripts](./scripts)

## 5. setup script
Just run the [setup.sh](./setup.sh) script to get all the dependencies for the env. This file still has some issues so you might need to see for any missing depedencies and install it on your own.


__NOTE__: No gaurentee or warrnty of this env working on your machine. Apply at your own risk!