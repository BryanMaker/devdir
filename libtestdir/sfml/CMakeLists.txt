cmake_minimum_required(VERSION 2.6)
project(game)

find_package(SFML REQUIRED COMPONENTS graphics network audio window system)

if(SFML_FOUND)
  add_executable(game main.cpp game.cpp)
  target_link_libraries(game sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
  target_include_directories(game PUBLIC ./)
endif()
