cmake_minimum_required(VERSION 3.10)
project(cpp_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(game
    src/Entity.cpp
    src/Monk.cpp
    src/Monster.cpp
    src/Room.cpp
    src/RoomFactory.cpp
    src/Dungeon.cpp
    src/Combat.cpp
    src/CombatStrategy.cpp
    src/Game.cpp
    src/main.cpp
)
