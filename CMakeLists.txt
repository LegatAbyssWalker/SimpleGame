cmake_minimum_required(VERSION 3.1)
project(SimpleGame CXX)

find_package(SFML 2.5 COMPONENTS graphics)

add_executable(main Main.cpp Player.cpp Coin.cpp)

target_link_libraries(main sfml-graphics)
