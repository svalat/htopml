######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_library(htopml-web-nodes TopWebNode.cpp GnuplotWebNode.cpp GetRusageWebNode.cpp)
target_link_libraries(htopml-web-nodes htopml-json htopml-server)
SET_TARGET_PROPERTIES(htopml-web-nodes PROPERTIES COMPILE_FLAGS -fPIC)