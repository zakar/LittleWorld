Little World
============

This fork is about our team homework.
We mainly changed the AI and add some new rendering scheme.
We also use lua as the configure script

REQUIRED:
---------
* any c++ compiler (just install xcode if you are on mac)
* GLUT and OpenGL c++ library (just install xcode if you are on mac)
* SFML 1.6 c++ library (http://www.sfml-dev.org/tutorials/1.6/)
* lua-5.1.4 (http://www.lua.org/download.html)

INSTALLING:
-----------
* Download lua-5.1.4 and Compile it
* Move the liblua.a to proper directory (May be you should edit FindLUA.cmake)
* Clone the LittleWorld project
* Type "make" to build the game
* Type "./build/littleWorld" to start the game

RUNNING:
-----------
We don't provide picture resource. 
But you can use your own picture by changing the code here:
src/tool/config.lua
src/game/Menu.cpp

