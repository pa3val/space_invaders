cmake_minimum_required(VERSION 3.10.0)
project(space_inviders VERSION 0.1.0 LANGUAGES C CXX)

add_executable(space_inviders
 main.cpp
 managers/game_manager.cpp
 entities/entity.cpp
 managers/collision_manager.cpp
 entities/bullet.cpp
 entities/player.cpp
 entities/shooter.cpp
 managers/input_manager.cpp
 game_states/level_state.cpp
 managers/renderer.cpp
 managers/signal_manager.cpp
 game_states/menu_state.cpp)

find_package(Curses REQUIRED)

target_link_libraries(space_inviders PRIVATE ${CURSES_LIBRARIES})

target_include_directories(space_inviders PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/entities
    ${CMAKE_SOURCE_DIR}/managers
    ${CMAKE_SOURCE_DIR}/game_states
)
