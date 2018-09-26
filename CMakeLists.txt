cmake_minimum_required(VERSION 3.10)
project(LNCF)

set(CMAKE_CXX_STANDARD 11)


file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

set(RESOURCE_FILES
        src/Assets/player.png
        src/Assets/foes.png
        src/Assets/PressStart2P.ttf
        src/Assets/level_01.tmx
        src/Assets/tileset_level_01.tsx
        src/Assets/tileset_level_01.png
        src/Assets/menuMusic.ogg
        src/Assets/kick.wav
        src/Assets/punch.wav
        src/Assets/enemyPunch.wav)

FILE(COPY ${RESOURCE_FILES} DESTINATION "${CMAKE_BINARY_DIR}")

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(TMXLITE REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        ${TMXLITE_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${TMXLITE_LIBRARIES})

set(CPACK_GENERATOR DragNDrop)
set(CPACK_DMG_VOLUME_NAME ${PROJECT_NAME})
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Install CACHE PATH "install here" FORCE)

install(TARGETS ${PROJECT_NAME} DESTINATION deb CONFIGURATIONS Debug)
install(FILES
        ${CMAKE_BINARY_DIR}/player.png
        ${CMAKE_BINARY_DIR}/foes.png
        ${CMAKE_BINARY_DIR}/PressStart2P.ttf
        ${CMAKE_BINARY_DIR}/level_01.tmx
        ${CMAKE_BINARY_DIR}/tileset_level_01.tsx
        ${CMAKE_BINARY_DIR}/tileset_level_01.png
        ${CMAKE_BINARY_DIR}/menuMusic.ogg
        ${CMAKE_BINARY_DIR}/kick.wav
        ${CMAKE_BINARY_DIR}/punch.wav
        ${CMAKE_BINARY_DIR}/enemyPunch.wav
        DESTINATION deb CONFIGURATIONS Debug)

include(CPack)