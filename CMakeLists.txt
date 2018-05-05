cmake_minimum_required(VERSION 3.10)
project(LNCF)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

set(RESOURCE_FILES src/Assets/player.png src/Assets/foes.png src/Assets/Roboto-Black.ttf)
FILE(COPY ${RESOURCE_FILES} DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})
