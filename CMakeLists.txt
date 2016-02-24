cmake_minimum_required(VERSION 3.3)
project(Rogue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Characters/AbstractCharacter.cpp Characters/AbstractCharacter.h  Room.cpp Room.h ExitRoom.cpp ExitRoom.h Level.cpp Level.h Characters/Hero.cpp Characters/Hero.h Characters/Enemy.cpp Characters/Enemy.h Controllers/GameController.cpp Controllers/GameController.h Views/ConsoleInputOutput.cpp Views/ConsoleInputOutput.h Items/Item.h Views/GameOutput.cpp Views/GameOutput.h Items/Item.cpp Items/Weapon.cpp Items/Weapon.h Items/Potion.cpp Items/Potion.h Items/Armor.cpp Items/Armor.h Mst.cpp Mst.h Visitor.h ItemVisitable.h Views/DeafultLevelOutput.cpp Views/DeafultLevelOutput.h)
add_executable(Rogue ${SOURCE_FILES})