######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
add_subdirectory(mongoose)

######################################################
#install procedure
INSTALL(DIRECTORY highcharts DESTINATION share/htopml/www)
INSTALL(DIRECTORY jquery DESTINATION share/htopml/www)
INSTALL(DIRECTORY d3js DESTINATION share/htopml/www)
