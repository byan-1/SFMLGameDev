cmake_minimum_required(VERSION 3.13)
project(SFMLGame VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)
set(SOURCES main.cpp Game.cpp Aircraft.cpp Entity.cpp SceneNode.cpp SpriteNode.cpp World.cpp Command.cpp CommandQueue.cpp Player.cpp)

include_directories(${PROJECT_SOURCE_DIR})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(SFMLGame ${SOURCES})
target_link_libraries(SFMLGame sfml-graphics)