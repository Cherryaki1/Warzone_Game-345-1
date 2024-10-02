cmake_minimum_required(VERSION 3.27)
project(Warzone_Game_a1_COMP345)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Cards)
include_directories(GameEngine)
include_directories(Map)
include_directories(Orders)
include_directories(Player)

add_executable(Warzone_Game_a1_COMP345
    Cards/Cards.cpp
    Cards/Cards.h
    Cards/CardsDriver.cpp
    GameEngine/GameEngine.cpp
    GameEngine/GameEngine.h
    GameEngine/GameEngineDriver.cpp
    Map/Map.cpp
    Map/Map.h
    Map/MapDriver.cpp
    Orders/Orders.cpp
    Orders/Orders.h
    Orders/OrdersDriver.cpp
    Player/Player.cpp
    Player/Player.h
    Player/PlayerDriver.cpp
    MainDriver.cpp
    MainDriver.h
        GameEngine/GameEngineDriver.h)
