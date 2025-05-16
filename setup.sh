#!/bin/bash

echo Installing default pkgs:
sudo pacman -S --needed ttf-dejavu ttf-noto-nerd libxft libxinerama feh xdotool wmctrl brightnessctl
sudo pacman --sync flameshot
sudo pacman -S firefox git unzip wget

echo Installing yay:
mkdir -p ~/Downloads
cd ~/Downloads
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
cd ../..
yay -S visual-studio-code-bin
yay -S nerd-fonts-jetbrains-mono
yay -S nerd-fonts-hack
yay -S nerd-fonts-ubuntu-mono