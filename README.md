# Pong
This is a take on the classic game of Pong. It is built using the SDL2 library rather than a game engine. [SDL2](https://www.libsdl.org/index.php) simply provides low level access to things like keyboard/mouse IO and the graphics hardware through OpenGL and Direct3D. The game loop with rendering, physics, and event handling was custom made.

Objects/Game.cpp is where all the game logic conglomerates.

This project was a remake of an older attempt at remaking Pong that can be found [here](https://github.com/IAbouzied/Pong_Github). It is littered with poor practices. Every class is in one file, there are many global variables that should be private variables in classes, its just a mess...
