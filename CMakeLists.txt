cmake_minimum_required(VERSION 2.8)
project(internalhtmlspytoolkit)

include_directories(${CMAKE_SOURCE_DIR}/extern_deps/mongoose)

add_subdirectory(extern_deps)
add_subdirectory(src)

add_executable(ihstkd main.cpp)
target_link_libraries(ihstkd InternalHtmlSpyToolKit mongoose)
target_link_libraries(ihstkd dl pthread)