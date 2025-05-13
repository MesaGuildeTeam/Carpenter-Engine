#!/bin/sh
cd ~/
mkdir .mesaguilde
cd .mesaguilde
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest