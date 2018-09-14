# Pong
This is a take on the classic game of Pong. It is built without a game engine. The game loop with rendering, physics, and event handling is all custom made. SDL2 was used to provide low level access to things like keyboard/mouse IO and the graphics hardware. More can be found out about SDL2 [here](https://www.libsdl.org/index.php).

## Play
You can play the game by running  BuiltGame/Pong.exe!

![startingscreen](https://user-images.githubusercontent.com/16506575/45575485-4ed48f80-b839-11e8-8cf4-511822d09f1b.PNG)

![playingscreen](https://user-images.githubusercontent.com/16506575/45575484-4ed48f80-b839-11e8-9b22-dd4e0fdecb1d.PNG)

## More info
This project was a remake of an older attempt at remaking Pong that can be found [here](https://github.com/IAbouzied/Pong_Github). It is littered with poor practices. All the classes are in one file, there are many global variables that should be private variables in classes, its just a mess...
