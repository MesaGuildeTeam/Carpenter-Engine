# Table Engine

![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![](https://img.shields.io/badge/JavaScript-323330?style=for-the-badge&logo=javascript&logoColor=F7DF1E)

A Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine will be to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

## Tech Stack

Building the game engine requires the following packages (can be installed in ubuntu's package repos):
- emscripten
- make

## Building Process
Use the following build process to build the engine

```
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
make
```

this will not be the final build process. The game engine will be packaged within an npm package(?) along with any other tools the game engine will come with in the future.