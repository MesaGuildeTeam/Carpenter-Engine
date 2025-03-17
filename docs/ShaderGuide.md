# Overview

To make this game engine compatible with web browsers, the system uses OpenGL ES 2.0. This allows for GLSL shader compatibility on not only just web, but it can expand to native desktop, and more conveniently, mobile. When you are programming your vertex and fragment shaders, there are a collection of pre-defined uniforms you can use to design your shaders:

# General Parameters

## Window
`uniform vec2 window`

> [!note] to be refactored into matrix

the whole purpose of the window uniform is to pass your window dimensions to the game engine. This is intended for scaling your objects to fit the users window to how you wish your game to behave.

# Vertex Shaders

## Position 
`attribute vec3 a_Position`

The position of the vertex stored as a vec3

## UV Coordinates
`attribute vec2 a_UV`

The texture coordinates of a vertex stored from 0 to 1.

## Normals
`attribute vec3 a_Normal`

The normal vector of the vertex. 
In most cases, this should be normalized to a unit vector but it will face away from the triangle it is associated with.

# Fragment Shaders