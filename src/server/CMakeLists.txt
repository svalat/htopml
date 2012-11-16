######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_library(htopml-server DirectoryWebNode.cpp FileWebNode.cpp ValidationWebNode.cpp Server.cpp WebNode.cpp)
target_link_libraries(htopml-server mongoose)
SET_TARGET_PROPERTIES(htopml-server PROPERTIES COMPILE_FLAGS -fPIC)
