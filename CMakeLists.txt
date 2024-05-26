cmake_minimum_required(VERSION 3.28)
project(final VERSION 0.1.0 LANGUAGES CXX)

# language standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# dependencies
find_package(spdlog REQUIRED)
add_subdirectory(al_game)

# [main] target
FILE(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})
# [main] include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/al_game/include)
# [main] link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE al_game)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
