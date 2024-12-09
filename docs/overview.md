# Overview
\mainpage

A Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine will be to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

For the design document, please refer to [This Google Document](https://docs.google.com/document/d/1oLOHmxrwEfjTDFo12rYifWIXcJgFl-JyXFgPHCGT00A)

# Tech Stack

Tool | Description
---|---
Emscripten | The webassembly C/C++ compiler used to build the game and engine
JavaScript | Game engine wrapper for the web app
HTML5/CSS | The Foundation to giving the game engine a DOM to work with
Doxygen | Generated documentation pages similar to javadocs for C++
PlantUML | Designing software structure before implementing

# Building the Engine

Use the following build process to build the engine

```
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
make
```

this will not be the final build process. The game engine will be packaged within an npm package(?) along with any other tools the game engine will come with in the future.

## Project Structure

`docs`
- All the documentation. If you use doxygen on the source code, you will see the game documentation will be packaged into docs/doxygen

`src`
- All the source code of the product. Currently, the only code stored in here is the engine code, and the distributed static page for the game engine