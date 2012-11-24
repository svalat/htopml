######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
set(COMMON_SOURCES Common.cpp)
set(COMMON_HEADERS Common.h)

######################################################
add_library(htopml-common ${COMMON_SOURCES})
SET_TARGET_PROPERTIES(htopml-common PROPERTIES COMPILE_FLAGS -fPIC)

######################################################
#install procedure
INSTALL(FILES ${COMMON_HEADERS} DESTINATION include/htopml/common)