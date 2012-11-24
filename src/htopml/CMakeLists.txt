######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
set(HTOPML_SOURCES HtopmlHttpServer.cpp)
set(HTOPML_HEADERS HtopmlHttpServer.h)

######################################################
#build libhtopml
add_library(htopml SHARED ${HTOPML_SOURCES})
target_link_libraries(htopml mongoose htopml-server htopml-json htopml-http-nodes htopml-common)
target_link_libraries(htopml ${CMAKE_THREAD_LIBS_INIT})

######################################################
#install procedure
INSTALL(TARGETS htopml
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
        LIBRARY DESTINATION lib${LIB_SUFFIX})
INSTALL(FILES ${HTOPML_HEADERS} DESTINATION include/htopml)
