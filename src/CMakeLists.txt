######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_subdirectory(integration)
add_subdirectory(generators)
add_subdirectory(examples)
add_subdirectory(proxy)
add_subdirectory(passwd)
add_subdirectory(libhtopml)
add_subdirectory(htopmld)

######################################################
#install procedure
INSTALL(DIRECTORY www DESTINATION share/htopml)
