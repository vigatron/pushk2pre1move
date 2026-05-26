cmake_minimum_required(VERSION 3.16)

project(pushk2pre1move LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/mods
)

file( GLOB_RECURSE source_list_mods 
    src/*
    mods/*
)

add_compile_definitions(DBG_VERBOSE=1)

add_executable(${PROJECT_NAME} ${source_list_mods} )

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

add_custom_target(localinstall
    COMMAND ${CMAKE_COMMAND} --install . --prefix $ENV{HOME}/bin
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Установка в локальную папку $ENV{HOME}/bin"
)