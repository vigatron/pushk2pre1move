cmake_minimum_required(VERSION 3.5)
project(MyQtProject CXX)

set(PRJNAME pushk2pre1move)


# set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_BUILD_TYPE "MinSizeRel")


include_directories(. src mods misc)

file( GLOB_RECURSE source_list_mods 
    src/*.cpp  src/*.hpp
    mods/*.cpp mods/*.hpp
    misc/*.cpp misc/*.hpp )

add_executable(${PRJNAME} src/main.cpp ${source_list_mods} )
add_custom_command(TARGET ${PRJNAME} POST_BUILD COMMAND cp "${PROJECT_BINARY_DIR}/${PRJNAME}"     "$ENV{HOME}/bin/${PRJNAME}"        )
add_custom_command(TARGET ${PRJNAME} POST_BUILD COMMAND cp -r "${CMAKE_SOURCE_DIR}/cfg"			 "/tmp/ramdisk/${PRJNAME}" )
add_custom_command(TARGET ${PRJNAME} POST_BUILD COMMAND cp -r "${CMAKE_SOURCE_DIR}/examples"	 "/tmp/ramdisk/${PRJNAME}" )
