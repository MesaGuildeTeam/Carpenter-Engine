# Overview

To make this game engine compatible with web browsers, the system uses OpenGL ES 2.0. This allows for GLSL shader compatibility on not only just web, but it can expand to native desktop, and more conveniently, mobile. When you are programming your vertex and fragment shaders, there are a collection of pre-defined uniforms you can use to design your shaders:

# Vertex Shaders

## `uniform vec2 window`

the whole purpose of the window uniform is to pass your window dimensions to the game engine. This is intended for scaling your objects to fit the users window to how you wish your game to behave.

# Fragment Shaders