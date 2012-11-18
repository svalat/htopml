######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_library(htopml-json JsonObject.cpp JsonState.cpp TypeToJson.cpp)
SET_TARGET_PROPERTIES(htopml-json PROPERTIES COMPILE_FLAGS -fPIC)