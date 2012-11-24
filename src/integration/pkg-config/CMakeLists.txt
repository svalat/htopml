######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#Generate and install pkg-config file
configure_file(htopml.pc.in ${CMAKE_CURRENT_BINARY_DIR}/htopml.pc ESCAPE_QUOTES @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/htopml.pc DESTINATION share/pkgconfig)
