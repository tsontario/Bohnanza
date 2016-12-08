cmake_minimum_required(VERSION 3.6)
project(CSI2372Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Chain.cpp Chain.h gemstones.cpp  cardfactory.cpp table.cpp deck.cpp tradearea.cpp hand.cpp discardpile.cpp player.cpp Card.h )
add_executable(CSI2372Project ${SOURCE_FILES})