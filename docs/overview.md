# Overview
\mainpage

Table Engine is a Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine will be to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

The game engine comes with both the framework to develop games in the game engine, and a CLI to assist developing the game such as installing compilers and building the game for you.

For the design document, please refer to [This Google Document](https://docs.google.com/document/d/1oLOHmxrwEfjTDFo12rYifWIXcJgFl-JyXFgPHCGT00A)

# Tech Stack
The game engine uses both a framework for to assist building games, and a toolkit written with node.js to streamline the game development process. For the bare minimum the only software you will need is Node.js. From here, you will have an easy way to install emsdk for use within developing games for the game engine 

Here are some general tools to view resources:
Tool | Description
---|---
Markdown | General documentation markup language
PlantUML | Designing software structure before implementing

## Framework
Here are the tools used specifically along the game engine framework:
Tool | Description
---|---
Emscripten | The webassembly C/C++ compiler used to build the game and engine
JavaScript | Game engine wrapper for the web app
HTML5/CSS | The Foundation to giving the game engine a DOM to work with
Doxygen | Generated documentation similar to javadocs for C++

## Toolkit
As for the toolkit, here are the important features
Tool | Description
---|---
Node.js | The foundation of the game engine
JsDoc | Generated documentation similar to javadocs for JavaScript
Jest | General purpose unit testing

# Building the Engine Framework

If you are building from source, use the following build process to build the engine code. 

```
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
npm install
npm run build
```

##

# Project Structure

'bin'
- The npm executables are stored here to assist with the game engine 

`docs`
- All the documentation. If you use doxygen on the source code, you will see the game engine documentation will be packaged into docs/doxygen

`scripts`
- anything involving the terminal is probably running in here. 

`src`
- All the source code of the product including the engine framework and the toolkit to assist developing a game with this.
- `./`: the toolkit cli and any future javascript code should be stored here 
- `engine`: C++ code used to hold the structure of the game engine
- `static`: a simple example of how the webpage should be setup

`examples`
- examples used to test the modules of the game engine in a manual environment. They can either be practical examples, or they can be generic tests to see how the features behave.