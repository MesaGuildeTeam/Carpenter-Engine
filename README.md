<picture>
  <source media="(prefers-color-scheme: dark)" srcset="docs/CarpenterEngine_Logo.png">
  <img src="docs/CarpenterEngine_Logo_Light.png" alt="Carpenter Engine"/>
</picture>

![LICENSED UNDER MPL-2.0](https://img.shields.io/badge/License-MPL%2D-2.0-red?style=for-the-badge)
[![Discord](https://img.shields.io/badge/Discord-7289DA?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/mXvpNy6wq7)

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
[![Emscripten](https://img.shields.io/badge/emscripten-darkgreen?style=for-the-badge)](https://emscripten.org/)
![Docs](https://img.shields.io/badge/doxygen-blue?style=for-the-badge)

![JavaScript](https://img.shields.io/badge/JavaScript-323330?style=for-the-badge&logo=javascript&logoColor=F7DF1E)
![npm](https://img.shields.io/badge/npm-CB3837?style=for-the-badge&logo=npm&logoColor=fff)
![NodeJS](https://img.shields.io/badge/Node.js-6DA55F?style=for-the-badge&logo=node.js&logoColor=white)

# Overview

Carpenter Engine is a C++ Game Engine designed to take advantage of WebAssembly
and web browser technology to offer a "build once, run anywhere" solution to C++
game development. Our studio will be using this engine for 2D and 2.5D games to
ensure an easy and optimal framework that emphasizes our strengths in programming.
However, we will ensure to offer an extensive 3D graphics engine that supports a
wide range of platforms in a single build.

Carpenter Engine comes with both the framework to develop games, and a CLI to
assist developing the game such as installing compilers and building the game
for you. You will also receive a runtime environment to test your game while
you develop it.

# Getting Started

Building with the game engine requires the following tools before proceeding
- Node.js (Required)
- Python (may be needed if the emsdk installer can not use its own python)

## Setting up a Game
To use the the engine in your own project:
```sh
npm install --save-dev table-engine
npx table setup # install emscripten for the toolkit, and generates necessary folders
```

This will install/update emscripten for the user in a recognized directory and
create any required folders for developing with the game engine.

you should then create a `src` folder and add a main.cpp file for your main.
Here is an example script to try:
```cpp
#include <Game.hpp>
#include <UI/UILabel.hpp>
#include <Graphics/Shapes.hpp>

using namespace Engine;

class ExampleScene : public Scene {
  private:
  Graphics::Cube mesh;
  Graphics::Texture texture;
  float time = 0;
  UI::UILabel label;

  public:
  ExampleScene() : Scene("ExampleScene"), texture("Assets/placeholder.png"),
  label("Label", "Hello World") {
    AddChild(&label);
  }

  void Draw() override {
    Scene::Draw();

    Game::getInstance().GetRenderer().UseTexture(texture, GL_TEXTURE0);
    Game::getInstance().GetRenderer().DrawMesh(&mesh, {0, 0, 10}, {1, 1, 1},
      {-35, time, 0});
  }

  void Update(float dt) override {
    time += 2 * dt;
  }
};

Game game{Game::getInstance(new ExampleScene())};
```
> This is `examples/HelloWorld.cpp`.
>
> If you wish to try more examples, see the `examples` folder.

## Running the Game
When you are ready to test the game, you can build the game and run it with
`npx table build -cl`. This will compile and link the game engine into a .wasm
and .js file.

To test the game from here, you can run `npx table dev` to start the testing
environment. This will open a web server on `http://localhost:3000/runtime`

When you are ready to package the whole static web app, you can run `npx table build -p`
which packages the static page on top of the compiled `.wasm` file into `build/`.

# Contributing
Although we will try our hardest to catch and work on issues on our own, we
will gladly look into any feedback you guys offer, and resolve bugs that you may
have discovered on your own. If you wish to contribute to the issues, ensure that
you are creating your own fork and we will manage any pull requests you offer If
we approve the implementation of the feature. Any request or bug report you offer
should be in the Issues section of the repo, and we will take care of it as soon
as we can.

## Requests

Although we will implement primarily what we need, we are always open to requests
and suggestions. we will only ask for the request, and how the game engine will 
benefit from this. If we agree that a feature is in our scope, we will put it in
our schedule to implement it and it will be done as soon as we can. 

## Reporting a Bug
If you need to report a bug, ensure you have the following:
- Bug Description
- How to replicate
- Hardware and Browser Specs

The amount of hardware you include is not the biggest concern, we are most
concerned about the browser you are using. We currently maintain primarily for
Chrome/Chromium based browsers only, but we are also looking into supporting
Firefox based browsers too.

## Building the Engine yourself
to build the game engine on your computer for contributing (assuming you have
not cloned the repo yet), we suggest you start with the following process.

```sh
git clone https://github.com/MesaGuildeTeam/Table-Engine
cd Table-Engine
npm start
npm run build
```

This will install emsdk similar to using a release of the project, and build the
game engine into .o files.

If you want to read more about the technical details of the game engine, I
recommend to start with docs/overview.md.

# Credits

Music for Demonstration: Roberto Selles

Drop Sound Effect: [Pixabay](https://pixabay.com/sound-effects/drop-sound-effect-240899/)

Placeholder Texture: [Jummit on OpenGameArt](https://opengameart.org/content/grid-placeholder-texture-templategridalbedopng)
