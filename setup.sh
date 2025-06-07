#!/bin/bash
echo Moving necessary files
echo touchpad config file moved!
sudo cp conf/40-libinput.conf /etc/X11/xorg.conf.d/
echo gestures config file moved!
sudo cp conf/libinput-gestures.conf /etc/

echo Installing default pkgs:
sudo pacman -S --needed libxft libxinerama feh xdotool wmctrl brightnessctl upower iw
sudo pacman -S --needed --sync flameshot
sudo pacman -S --needed firefox git unzip wget

echo installing fonts
sudo pacman -S --needed nerd-fonts

echo Installing yay:
mkdir -p ~/Downloads
cd ~/Downloads
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
cd ../..
rm -r yay

echo Installing through yay
yay -S --needed visual-studio-code-bin 

echo Making suckless softwares:
cd dwm
sudo make clean install
cd ../dmenu
sudo make clean install
cd ../st
sudo make clean install
cd ../slock
sudo make clean install
cd ..
