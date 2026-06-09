cmake_minimum_required(VERSION 4.1)
project(PokemonGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PokemonGame
        CombatGraph.h
        main.cpp
        MetaAnalyzer.h
        PokemonBase.h
        main.cpp
)
