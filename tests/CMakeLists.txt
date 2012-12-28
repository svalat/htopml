######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
include(${CMAKE_SOURCE_DIR}/cmake/unittest-macros.cmake)

######################################################
add_definitions(-DTEST_DATA="${CMAKE_CURRENT_SOURCE_DIR}/datas")
include_directories(${SVUNITTEST_INCLUDE_DIRS})

######################################################
add_executable(testJson testJson.cpp)
target_link_libraries(testJson htopml-json ${SVUNITTEST_LIBRARY})
htopml_add_test(testJson)

######################################################
add_executable(testCommon testCommon.cpp)
target_link_libraries(testCommon htopml-common ${SVUNITTEST_LIBRARY})
htopml_add_test(testCommon)
