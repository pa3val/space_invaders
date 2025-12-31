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
 game_states/menu_state.cpp
 game_states/game_over_state.cpp)

find_package(Curses REQUIRED)
find_package(Lua REQUIRED)
find_package(sol2 REQUIRED)

target_link_libraries(space_inviders PRIVATE 
    ${CURSES_LIBRARIES} 
    ${LUA_LIBRARIES}
    sol2::sol2
)
target_include_directories(space_inviders PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/entities
    ${CMAKE_SOURCE_DIR}/managers
    ${CMAKE_SOURCE_DIR}/game_states
    ${CMAKE_SOURCE_DIR}/managers
    ${LUA_INCLUDE_DIR}
)

file(COPY ${CMAKE_SOURCE_DIR}/levels/
    DESTINATION ${CMAKE_BINARY_DIR}/levels
    FILES_MATCHING PATTERN "*.lua")
file(COPY ${CMAKE_SOURCE_DIR}/levels/
    DESTINATION ${CMAKE_BINARY_DIR}/levels
    FILES_MATCHING PATTERN "*.txt")

file(GLOB LUA_CONFIG_FILES "${CMAKE_SOURCE_DIR}/*.lua")
file(COPY ${LUA_CONFIG_FILES}
    DESTINATION ${CMAKE_BINARY_DIR})