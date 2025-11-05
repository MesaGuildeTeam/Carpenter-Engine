# Contributing - Overview

This file includes everything you need to know about how to modify Carpenter
Engine on your own. This file includes:
- The tech stack
- building the engine
file structure overview

# Tech Stack
Carpender Engine uses both a framework for to assist building games, and a toolkit
written with node.js to streamline the game development process. For the bare
minimum the only software you will need is Node.js. From here, you will have an
easy way to install emsdk for use within developing games for the game engine

Here are some general tools to view resources:

Tool | Description
---|---
Markdown | General documentation markup language
PlantUML | Designing software structure before implementing
Doxygen | Generated documentation similar to javadocs for C++
JsDoc | Generated documentation similar to javadocs for JavaScript

## Framework
Here are the tools used specifically along the game engine framework:

Tool | Description
---|---
Emscripten | The webassembly C/C++ compiler used to build the game and engine
JavaScript | Game engine wrapper for the web app
HTML5/CSS | The Foundation to giving the game engine a DOM to work with

## Toolkit
As for the toolkit, here are the important features:

Tool | Description
---|---
Node.js | The foundation of the game engine
Jest | General purpose unit testing

# Building the Engine Framework

If you are building from source, use the following build process to build the
engine code.

```
git clone https://github.com/MesaGuildeTeam/Carpenter-Engine
cd Carpenter-Engine
npm install
npm run build
```

# Project Structure
These folders show

'Assets'
- Used to store all the assets used in the examples

'bin'
- The npm executables are stored here to assist with the game engine

`docs`
- All the documentation. If you use doxygen on the source code, you will see the
game engine documentation will be packaged into docs/doxygen

`examples`
- examples used to test the modules of the game engine in a manual environment.
They can either be practical examples, or they can be generic tests to see how
the features behave.

`include`
- C/C++ Header libraries used by the engine but should not be accessed through
the game engine itself

`scripts`
- anything involving shell scripts are probably stored in here.

`src`
- All the source code of the product including the engine framework and the
toolkit to assist developing a game with this.
- `./`: the toolkit cli and any future javascript code should be stored here
- `classes`: JavaScript
- `engine`: C++ code used to hold the structure of the game engine
- `static`: a simple example of how the webpage should be setup

`tests`
- All Unit tests are performed here. These tests can either be in JavaScript
tested in Jest, or a C++ unit test that gets compiled to WASM before running.

# Code Style
The code style for both C++ and JavaScript for the game engine will follow
Google's standard for C++ as close as possible. The main rules that are however
required are to keep lines below 80 characters, and documentation generation is
created using the `/** */` comment notation. Header file guards will use the 
`#ifndef` style, and the file guards will be defined with the following format
where `[FILENAME]` is the name of the file without the extension.

```cpp
#ifndef ENGINE_[FILENAME]
#define ENGINE_[FILENAME]

...

#endif
```

Everything is intended to be programmed in an Object-Oriented manner as much as
possible, but some functional programming is allowed as an interface between
languages in the engine.
