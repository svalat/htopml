######################################################
#build htopmld exe (for tests)
add_definitions(-DSKEEP_DEFAULT_USER_PAGES)
add_executable(userhtopmld ../main.cpp HtopmlAutoHttpNodes.cpp HtopmlAutoTypeToJson.cpp)
target_link_libraries(userhtopmld htopml)
target_link_libraries(userhtopmld ${CMAKE_THREAD_LIBS_INIT})
