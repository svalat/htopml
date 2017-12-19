######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
set(JSON_SOURCES JsonState.cpp TypeToJson.cpp ConvertToJson.cpp)
set(JSON_HEADERS JsonState.h TypeToJson.h JsonState_impl.h TypeToJson_impl.h ConvertToJson.h ConvertToJson_impl.h FastBufferdStream.hpp)

######################################################
add_library(htopml-json ${JSON_SOURCES})
SET_TARGET_PROPERTIES(htopml-json PROPERTIES COMPILE_FLAGS -fPIC)

######################################################
#install procedure
INSTALL(FILES ${JSON_HEADERS} DESTINATION include/htopml)
