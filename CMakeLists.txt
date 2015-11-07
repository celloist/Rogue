cmake_minimum_required(VERSION 3.3)
project(Rogue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Characters/AbstractCharacter.cpp Characters/AbstractCharacter.h AbstractItem.cpp AbstractItem.h Room.cpp Room.h ExitRoom.cpp ExitRoom.h Level.cpp Level.h Characters/Hero.cpp Characters/Hero.h Characters/Enemy.cpp Characters/Enemy.h Controllers/GameController.cpp Controllers/GameController.h Views/ConsoleInputOuput.cpp Views/ConsoleInputOuput.h Item.h Views/GameOutput.cpp Views/GameOutput.h)
add_executable(Rogue ${SOURCE_FILES})