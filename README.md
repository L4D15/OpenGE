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

1. Download source code from [here](http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download)
2. Unzip and navigate to the folder.
3. Install required libraries and tools `sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev`
4. Prepare Boost to be compiled with `./bootstrap.sh --prefix=/usr/local`
5. Start compilation with `sudo ./b2 --with=all install`. This will take a while (15~30 minutes).

lua and LuaBind:

1. `sudo apt-get install lua5.1 lua5.1-policy-dev`
2. `sudo apt-get install libluabind-dev`

OpenGL:

1. `sudo apt-get install mesa-common-dev`
2. `sudo apt-get install libgl1-mesa-dev`

SDL2:

1. Download the source code from [here](http://www.libsdl.org/download-2.0.php).
2. Unzip and navigate to the folder.
3. `./configure`
4. `make`
5. `sudo make install`

SDL2_Image:

1. Download the source code from [here](https://www.libsdl.org/projects/SDL_image/)
2. To enable support of image formats other than BMP: `sudo apt-get install libpng12-dev libjpeg-dev libtiff4-dev libwebp-dev`
3. `./configure`
4. `sudo make install`

SDL2_TTF:

1. Download the source code from [here](https://www.libsdl.org/projects/SDL_ttf/)
2. Install the FreeType library `sudo apt-get install libfreetype6-dev`
3. `./configure`
4. `make`
5. `sudo make install`

OpenGE also uses C++11 features, so you need a compiler compatible with it.

C++11:

1. `sudo add-apt-repository ppa:ubuntu-toolchain-r/test`
2. `sudo apt-get update`
3. `sudo apt-get install gcc-4.8 g++-4.8`
4. `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.6`
5. `sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 40 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8`
6. `sudo update-alternatives --config gcc` and select the 4.8 option.

At the time of the creation of this guide GCC have a bug where the use of `#elif` differs from `#else #if` so the project fails to compile luabind. Until thise parsing error is fixed in a newer version of GCC some tweaking in LuaBind files is necessary to make it work. The following list details the files and line of code where `#elif` must be changed for an `#else` and a nested `#if`:

* __/usr/include/luabind/detail/call_member.hpp__ [319]
* __/usr/include/luabind/detail/call_function.hpp__ [326]
* __/usr/include/luabind/wrapper_base.hpp__ [92]

__¡IMPORTANT!__ Remeber to add another `#endif` at the end of the file since we added a new `#if`. To clarify, we are changin from this:

```C++
#if (...)

#elif (...)

#endif
```

To this:

```C++
#if (...)

#else
	#if (...)

	#endif
#endif
```

If you, like me, find this bug pretty anoying feel free to email the LuaBind guys to change those lines of code and the GCC devs to fix the parser of GCC 4.8. In the mean time this is the only workaround in Linux :-(
