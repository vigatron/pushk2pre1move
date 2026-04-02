cmake_minimum_required(VERSION 3.16)

project(pushk2pre1move LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/mods
                    ${CMAKE_SOURCE_DIR}/misc)

file( GLOB_RECURSE source_list_mods 
    src/*.cpp  src/*.hpp
    mods/*.cpp mods/*.hpp
    misc/*.cpp misc/*.hpp )

add_compile_definitions(DBG_VERBOSE=0)

add_executable(${PROJECT_NAME} ${source_list_mods} )

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "$ENV{HOME}/bin")