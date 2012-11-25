######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_subdirectory(server)
add_subdirectory(json)
add_subdirectory(http-nodes)
add_subdirectory(common)
add_subdirectory(htopml)
add_subdirectory(integration)
add_subdirectory(generators)

######################################################
#install procedure
INSTALL(DIRECTORY www DESTINATION share/htopml)
