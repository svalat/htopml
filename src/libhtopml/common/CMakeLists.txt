######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
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
INSTALL(FILES ${COMMON_HEADERS} DESTINATION include/htopml)