######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

#Generate and install cmake module file
configure_file(FindHtopml.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/FindHtopml.cmake ESCAPE_QUOTES @ONLY)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/FindHtopml.cmake DESTINATION share/cmake/Modules/)
