######################################################
#build htopmld exe (for tests)
add_definitions(-DSKEEP_DEFAULT_USER_PAGES)
add_executable(userhtopmld ../main.cpp HtopmlAutoHttpNodes.cpp HtopmlAutoTypeToJson.cpp)
target_link_libraries(userhtopmld mongoose htopml-server htopml-json htopml-http-nodes htopml-common)
target_link_libraries(userhtopmld ${CMAKE_THREAD_LIBS_INIT})
