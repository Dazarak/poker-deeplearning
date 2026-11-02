cmake_minimum_required(VERSION 3.20)
project(poker-deeplearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_options(-Wall -Wextra -O3 -march=native)

add_executable(poker-deeplearning
    poker-ai/src/main.cpp
    poker-ai/src/PokerAI.cpp
    poker-holdem-engine/src/GameContext.cpp
    poker-holdem-engine/src/Holdem.cpp
    poker-holdem-engine/src/Player.cpp
    poker-hand-evaluator/src/Card.cpp
    poker-hand-evaluator/src/Engine.cpp
    poker-hand-evaluator/src/HandResult.cpp
)

# Indiquer où trouver tous les fichiers d'en-tête (.h) de ton projet et des sous-modules
target_include_directories(poker-deeplearning PRIVATE 
    include
    poker-ai/include
    poker-holdem-engine/include
    poker-hand-evaluator/include
)