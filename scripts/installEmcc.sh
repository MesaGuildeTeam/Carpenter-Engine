# Install emscripten
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest || ./emsdk.bat install latest
./emsdk activate latest || ./emsdk.bat activate latest