cmake_minimum_required(VERSION 3.10.0)
project(space_inviders VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(space_inviders
 main.cpp
 managers/game_manager.cpp
 entities/entity.cpp
 managers/collision_manager.cpp
 entities/bullet.cpp
 entities/player.cpp
 entities/shooter.cpp
 entities/enemy.cpp
 entities/damageable.cpp
 managers/input_manager.cpp
 game_states/level_state.cpp
 managers/renderer.cpp
 managers/signal_manager.cpp
 managers/level_manager.cpp
 managers/audio_manager.cpp
 game_states/menu_state.cpp
 game_states/game_over_state.cpp)

find_package(Lua REQUIRED)

find_package(sol2 CONFIG REQUIRED)

find_path(CURSES_INCLUDE_DIR NAMES curses.h)
find_library(CURSES_LIBRARY NAMES pdcurses curses)

find_path(MINIAUDIO_INCLUDE_DIRS "miniaudio.h")

message(STATUS "LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message(STATUS "CURSES_INCLUDE_DIR: ${CURSES_INCLUDE_DIR}")
message(STATUS "CURSES_LIBRARY: ${CURSES_LIBRARY}")

target_include_directories(space_inviders PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/entities
    ${CMAKE_SOURCE_DIR}/managers
    ${CMAKE_SOURCE_DIR}/game_states
    ${LUA_INCLUDE_DIR}
    ${CURSES_INCLUDE_DIR}
    ${MINIAUDIO_INCLUDE_DIRS}
)

target_link_libraries(space_inviders PRIVATE 
    ${LUA_LIBRARIES}
    ${CURSES_LIBRARY}
    sol2::sol2
)

file(COPY ${CMAKE_SOURCE_DIR}/levels/
    DESTINATION ${CMAKE_BINARY_DIR}/levels
    FILES_MATCHING PATTERN "*.lua")
file(COPY ${CMAKE_SOURCE_DIR}/levels/
    DESTINATION ${CMAKE_BINARY_DIR}/levels
    FILES_MATCHING PATTERN "*.txt")
file(COPY ${CMAKE_SOURCE_DIR}/sounds/
    DESTINATION ${CMAKE_BINARY_DIR}/sounds
    FILES_MATCHING PATTERN "*")
    

file(GLOB LUA_CONFIG_FILES "${CMAKE_SOURCE_DIR}/*.lua")
file(COPY ${LUA_CONFIG_FILES}
    DESTINATION ${CMAKE_BINARY_DIR})
