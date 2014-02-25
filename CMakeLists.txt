cmake_minimum_required(VERSION 2.6)
project(EGGGEN)

include_directories (${EGGGEN_SOURCE_DIR})

include ($ENV{katydid}/build/MonarchConfig.cmake)
include_directories (${Monarch_INCLUDE_DIRS})
link_directories (${Monarch_LIBRARY_DIRS})

add_executable (eggGen.o eggGen.cxx)
target_link_libraries (eggGen.o ${Monarch_LIBRARIES})
