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

### Linux

The libraries we need to install in the system are:
* Boost
* lua
* LuaBind
* SDL2
* SDL2_Image
* SDL2_TTF

If they are present in your distro repositories install from there or if you feel brave enough compile them your self. Since the versions in the repositories are likely to be very old or outdated the following guide will try to get you the most recent version of each library.

Boost:

1. Download source core from [here](http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download)
2. Unzip and navigate to the folder.
3. Install required libraries and tools `sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev`
4. Prepare Boost to be compiled with `./bootstrap.sh --prefix=/usr/local`
5. Start compilation with `sudo ./b2 --with=all install`. This will take a while (15~30 minutes).

lua:

1. `sudo apt-get install lua5.1 lua5.1-policy-dev`
2. Done.