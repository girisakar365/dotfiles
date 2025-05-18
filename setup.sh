#!/bin/bash
echo Moving necessary files
echo touchpad config file moved!
sudo cp conf/40-libinput.conf /etc/X11/xorg.conf.d/
echo gestures config file moved!
sudo cp conf/libinput-gestures.conf /etc/

echo Installing default pkgs:
sudo pacman -S --needed ttf-dejavu ttf-noto-nerd libxft libxinerama feh xdotool wmctrl brightnessctl upower
sudo pacman -S --needed --sync flameshot
sudo pacman -S --needed firefox git unzip wget

echo Installing yay:
mkdir -p ~/Downloads
cd ~/Downloads
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
cd ../..
yay -S --needed visual-studio-code-bin
yay -S --needed nerd-fonts-jetbrains-mono
yay -S --needed nerd-fonts-hack
yay -S --needed nerd-fonts-ubuntu-mono