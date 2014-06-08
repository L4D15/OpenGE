OpenGE
===============

[![Build Status](https://travis-ci.org/L4D15/OpenGE.svg?branch=master)](https://travis-ci.org/L4D15/OpenGE)

OpenGE stands for Open Game Engine, a free and open source game engine with educational purposes in mind.

## Compiling

The following libraries must be present in your system to be able to compile OpenGE, the rest are included in the repository and will be compiled along the engine.

Libraries:
* OpenGL
* SDL2
* SDL_Image
* SDL_TTF
* Boost
* Lua 5.1
* LuaBind

### OS X

Install [Brew](http://brew.sh/) (I can't find a reason you don't already have it). You can install all the libraries from brew like this:

`brew install SDL2 SDL2_Image SDL2_TTF Boost lua luabind`
