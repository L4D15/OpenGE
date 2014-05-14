OpenGE
===============

OpenGE stands for Open Game Engine, a free and open source game engine with educational purposes in mind.

## Compiling

The following libraries must be present in your system to be able to compile OpenGE, the rest are included in the repository and will be compiled along the engine.

Libraries:
* OpenGL.
* SDL2.
* SDL_Image.
* SDL_TTF.
* Boost.

### OS X

Install [Brew](http://brew.sh/) (I can't find a reason you don't already have it). You can install all the libraries from brew, but in the case of boost install with the `--with-python` argument so the Boost.Python library is also installed.