######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_library(htopml-http-nodes TopHttpNode.cpp GnuplotHttpNode.cpp GetRusageHttpNode.cpp MenuHttpNode.cpp TemplatePageHttpNode.cpp)
target_link_libraries(htopml-http-nodes htopml-json htopml-server)
SET_TARGET_PROPERTIES(htopml-http-nodes PROPERTIES COMPILE_FLAGS -fPIC)