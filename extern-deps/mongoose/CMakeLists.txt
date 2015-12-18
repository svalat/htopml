######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_definitions(-DNO_SSL)
add_library(mongoose mongoose.c)
SET_TARGET_PROPERTIES(mongoose PROPERTIES COMPILE_FLAGS -fPIC)

######################################################
#install procedure
INSTALL(FILES mongoose.h DESTINATION include/htopml)