######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
set(SERVER_SOURCES HttpResponse.cpp HttpRequest.cpp VirtualDirectoryHttpNode.cpp DirectoryHttpNode.cpp FileHttpNode.cpp ValidationHttpNode.cpp HttpServer.cpp HttpNode.cpp)
set(SERVER_HEADERS HttpResponse.h   HttpRequest.h   VirtualDirectoryHttpNode.h   DirectoryHttpNode.h   FileHttpNode.h   ValidationHttpNode.h   HttpServer.h   HttpNode.h JsonHttpNode.h)

######################################################
add_library(htopml-server ${SERVER_SOURCES})
target_link_libraries(htopml-server mongoose htopml-common)
SET_TARGET_PROPERTIES(htopml-server PROPERTIES COMPILE_FLAGS -fPIC)

######################################################
#install procedure
INSTALL(FILES ${SERVER_HEADERS} DESTINATION include/htopml)
