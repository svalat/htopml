######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
include(${CMAKE_SOURCE_DIR}/cmake/unittest-macros.cmake)

######################################################
add_executable(testJson testJson.cpp)
target_link_libraries(testJson htopml-json gtest)
htopml_add_test(testJson)
