#!/bin/bash
cd ~/
mkdir .table-engine
cd .table-engine
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest