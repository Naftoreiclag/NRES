cmake_minimum_required (VERSION 2.6)

project (NRES)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/include")

# locate all the files
file (GLOB NRES_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file (GLOB NRES_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_library (NRES STATIC ${NRES_SRC} ${NRES_INCLUDE})

install (TARGETS NRES 
LIBRARY DESTINATION "lib"
ARCHIVE DESTINATION "lib")
