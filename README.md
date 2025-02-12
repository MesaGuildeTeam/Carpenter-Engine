# Table Engine

![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![](https://img.shields.io/badge/JavaScript-323330?style=for-the-badge&logo=javascript&logoColor=F7DF1E)

Table Engine is a Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine is primarily to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

The game engine comes with both the framework to develop games in the game engine, and a CLI to assist developing the game such as installing compilers and building the game for you.

# Getting Started

Building with the game engine requires the following tools before proceeding
- node.js (Required)
- Python (may be needed if the emsdk installer can not use its own python)

## Setting up a Game
To use the the engine in your own project:
```sh
npm install --save-dev table-engine
npx table setup # install emscripten for the toolkit, and generates necessary folders
```

This will install/update emscripten for the user in a recognized directory and create any required folders for developing with the game engine.

you should then create a `src` folder and add a main.cpp file for your main. Here is an example script to try:
```cpp
#include <Game.hpp>
#include <UI/UILabel.hpp>

using namespace Engine;

class ExampleScene : public Scene {
public:
  ExampleScene() : Scene("ExampleScene") {
    UI::UILabel* label = new UI::UILabel("Label", "Hello World from Table Engine");
    AddChild(label);
  }
};

Game game{Game::getInstance(new ExampleScene())};

extern "C" {
  void CallDraw() { game.DrawScene(); }
  void CallUpdate(float dt) { game.UpdateScene(dt); }
}
```
> This is `examples/HelloWorld.cpp`.
> 
> If you wish to try more examples, see the `examples` folder.

## Running the Game
When you are ready to test the game, you can build the game and run it with `npx table build -cl`.
This will compile and link the game engine into a .wasm and .js file. 

To test the game from here, you can run `npx table dev` to start the testing environment. 
This will open a web server on `http://localhost:3000/runtime` 

When you are ready to package the whole static web app, you can run `npx table build -p` which packages the static page on top of the compiled .wasm file into build/.

# Build it Yourself
to build the game engine yourself for contributing (assuming you have not cloned the repo yet), you will need to use the following process.

```sh
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
npm start
npm run build
```

This will install emsdk similar to using a release of the project, and build the game engine into .o files.

If you want to read more about the technical details of the game engine, I recommend to start with docs/overview.md

# Credits

Music for Demonstration for Examples/SoundTest.cpp: Roberto Selles
Drop Sound Effect: [Pixabay](https://pixabay.com/sound-effects/drop-sound-effect-240899/)