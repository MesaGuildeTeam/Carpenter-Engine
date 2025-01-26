# Table Engine

![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![](https://img.shields.io/badge/JavaScript-323330?style=for-the-badge&logo=javascript&logoColor=F7DF1E)

A Modular C++ Game Engine designed to take advantage of WebAssembly and web browser technology to create flexible web clients.
The purpose of the game engine will be to develop 2D and 2.5D games, but the goal is for the engine to be engine to be flexible that you can add any feature possible.

The game engine comes with both the framework to develop games in the game engine, and a CLI to assist developing the game such as installing compilers and building the game for you.

## Tech Stack

Building the game engine requires the following tools before proceeding
- node.js (Required)
- Python (may be needed if the emsdk installer can not use its own python)

## Usage
To use the the engine in your own project:
```sh
npm install --save-dev table-engine
npx table setup # install emscripten for the toolkit, and generates necessary folders
```

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

When you are ready to build, you can use the following command to build the project

```sh
npx table build # takes the existing game code from src, compiles, links, and packages it with a static HTML5 and CSS page
```

This process will generate the following standardized folders: `objs` and `build`. From here you can distribute the built SPA as needed

## Build it Yourself
to build the game engine yourself (assuming you have not cloned the repo yet), you will need to use the following process.

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