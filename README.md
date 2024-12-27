# Table Engine

![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![](https://img.shields.io/badge/JavaScript-323330?style=for-the-badge&logo=javascript&logoColor=F7DF1E)

A Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine will be to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

The game engine comes with both the framework to develop games in the game engine, and a CLI to assist developing the game such as installing compilers and building the game for you.

## Tech Stack

Building the game engine requires the following packages before proceeding:
- node.js
- Python (may be needed if the emsdk installer can not use its own python)

## Usage
To use the the engine in your own project:
```sh
npm install --save-dev table-engine
npx table setup # install emscripten into your project, and generates necessary folders
npx table build # takes the existing game code from src, compiles, links, and packages it with a static HTML5 and CSS page
```

This process will generate the following standardized folders: `objs` and `build`. From here you can distribute the static webpage as needed.

## Build it Yourself
to build the game engine yourself (assuming you have not cloned the repo yet), you will need to use the following process.

```sh
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
npm run build
```

This will install emsdk similar to using a release of the project, and build the game engine into .o files.

If you want to read more about the technical details of the game engine, I recommend to start with docs/overview.md