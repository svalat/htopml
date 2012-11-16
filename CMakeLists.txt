cmake_minimum_required(VERSION 2.8)
project(htopml)

include_directories(${CMAKE_SOURCE_DIR}/extern-deps/mongoose)

add_subdirectory(extern-deps)
add_subdirectory(src)

add_executable(htopmld main.cpp)
target_link_libraries(htopmld mongoose htopml-server htopml-json htopml-web-nodes)
target_link_libraries(htopmld dl pthread)

add_library(htopml SHARED main.cpp)
target_link_libraries(htopml mongoose htopml-server htopml-json htopml-web-nodes)
target_link_libraries(htopml dl pthread)
SET_TARGET_PROPERTIES(htopml PROPERTIES COMPILE_FLAGS -DENABLE_INSTR_LIB)