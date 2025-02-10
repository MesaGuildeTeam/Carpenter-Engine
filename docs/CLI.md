# The Command Line Interface
The purpose of the CLI is to offer a minimal toolkit to assist developing with the game engine. Currently it offers a way to install emscripten, and a standardized way to build the game engine.

## Setup
Setup will perform the following tasks
- install emscripten for use with the game engine
- generate necessary folders for the toolkit to behave as needed

When setting up emscripten, it will create a folder in your user's home directory called `.table-engine`. From here it will clone emscripten, pull any needed changes, install the latest version and activate it.

Another step will make sure that the folders `build` and `objs` are generated. These folders will be required folders as mentioned in the building section.

## Building

The build process is standardized so that libraries can be linked easier on compilation. The goal of this system is to generate `.o` files for webassembly, then link all the libraries needed for the final game project in a way that a single webassembly file is generated. This then gets packaged with the rest of a static website to be distributed with the game engine

### Process
1. Generate WASM `.o` files from `.cpp`
2. Link all .o files in the project into a single `.js` and `.wasm` file
3. package any required HTML and CSS files for to distribute the game with any further steps desired

> ### Current plans for improvement
> One of the issues with this system at the moment is that it compiles *every* file in this project. In the future, there should be a system to monitor which files have not been modified since last compilation, and to not recompile those files.

### Cleaning
with the `flip` command, you can clean your project folder, and all of the .o files built in the folder

## Testing
testing compiles and runs all tests in tests/CPP into tests/WASM before running the tests.

You can also run `table dev` to test the runtime of the game.