######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#Cmake basic options
cmake_minimum_required(VERSION 2.8)
project(htopml)
set(HTMLTOP_VERSION "0.0.0")

######################################################
#global setup
enable_testing()
add_definitions(-DVERSION="${HTMLTOP_VERSION}")

######################################################
#Delegate some cmake scripts
include(${CMAKE_SOURCE_DIR}/cmake/user-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/cpack-options.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/check-deps.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/enable-options.cmake)

######################################################
#some include dirs
include_directories(${CMAKE_SOURCE_DIR}/extern-deps/mongoose)

######################################################
#manage subdirs
add_subdirectory(extern-deps)
add_subdirectory(src)
if (NOT DISABLE_TESTS)
	add_subdirectory(tests)
endif (NOT DISABLE_TESTS)
add_subdirectory(user-analysis)

######################################################
#build htopmld exe (for tests)
add_executable(htopmld main.cpp)
target_link_libraries(htopmld mongoose htopml-server htopml-json htopml-http-nodes htopml-common)
target_link_libraries(htopmld ${CMAKE_THREAD_LIBS_INIT})

######################################################
#build libhtopml
add_library(htopml SHARED main.cpp)
target_link_libraries(htopml mongoose htopml-server htopml-json htopml-http-nodes htopml-common)
target_link_libraries(htopml ${CMAKE_THREAD_LIBS_INIT})
SET_TARGET_PROPERTIES(htopml PROPERTIES COMPILE_FLAGS -DENABLE_INSTR_LIB)

######################################################
#install procedure
INSTALL(TARGETS htopml
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        LIBRARY DESTINATION lib${LIB_SUFFIX})
