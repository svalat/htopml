######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
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

######################################################
add_executable(testHttpNode testHttpNode.cpp)
target_link_libraries(testHttpNode htopml-server ${SVUNITTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
htopml_add_test(testHttpNode)

######################################################
add_executable(testHttpRequest testHttpRequest.cpp)
target_link_libraries(testHttpRequest htopml-server ${SVUNITTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
htopml_add_test(testHttpRequest)