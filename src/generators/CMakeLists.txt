######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
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
INSTALL(FILES graphs.js.template http-nodes.cpp.template http-nodes.h.template json.cpp.template json.h.template view.html.xsl Makefile.in main.cpp htopml-project.xsd
		DESTINATION share/htopml/templates/)