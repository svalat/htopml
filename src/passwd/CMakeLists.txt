######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#build htopmld exe (for tests)
add_executable(htopml-passwd main.cpp)
target_link_libraries(htopml-passwd mongoose ${CMAKE_THREAD_LIBS_INIT})

######################################################
INSTALL(TARGETS htopml-passwd
        RUNTIME DESTINATION bin)
