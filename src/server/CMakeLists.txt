######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_library(htopml-server MenuHttpNode.cpp TemplatePageHttpNode.cpp HttpResponse.cpp HttpRequest.cpp VirtualDirectoryHttpNode.cpp DirectoryHttpNode.cpp FileHttpNode.cpp ValidationHttpNode.cpp HttpServer.cpp HttpNode.cpp)
target_link_libraries(htopml-server mongoose htopml-common)
SET_TARGET_PROPERTIES(htopml-server PROPERTIES COMPILE_FLAGS -fPIC)
