######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
INSTALL(PROGRAMS htopml-generate.sh
        DESTINATION bin RENAME htopml-generate)

######################################################
INSTALL(PROGRAMS htopml-txt2xml.sh
        DESTINATION share/htopml/scripts)

######################################################
INSTALL(PROGRAMS htopml-template2xslt.sh
        DESTINATION share/htopml/scripts)

######################################################
INSTALL(FILES graphs.js.template http-nodes.cpp.template http-nodes.h.template json.cpp.template json.h.template view.html.xsl Makefile.in main.cpp
		DESTINATION share/htopml/templates/)