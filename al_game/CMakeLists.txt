cmake_minimum_required(VERSION 3.28)
project(al_game VERSION 0.1.0 LANGUAGES CXX)

# language standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

# output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# main target
FILE(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})

# [main] include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# dependencies
find_package(spdlog REQUIRED)
find_package(Allegro REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
        spdlog::spdlog
        Allegro::allegro
        Allegro::allegro_acodec
        Allegro::allegro_audio
        Allegro::allegro_dialog
        Allegro::allegro_font
        Allegro::allegro_image
        Allegro::allegro_main
        Allegro::allegro_primitives
        Allegro::allegro_ttf
)
