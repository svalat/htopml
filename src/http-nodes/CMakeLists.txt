######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
set(HTTP_NODES_SOURCES ProcessHttpNode.cpp TopHttpNode.cpp GnuplotHttpNode.cpp GetRusageHttpNode.cpp MenuHttpNode.cpp TemplatePageHttpNode.cpp)
set(HTTP_NODES_HEADERS ProcessHttpNode.h   TopHttpNode.h   GnuplotHttpNode.h   GetRusageHttpNode.h   MenuHttpNode.h   TemplatePageHttpNode.h)

######################################################
#Optional
if (HWLOC_FOUND)
	set(HTTP_NODES_SOURCES ${HTTP_NODES_SOURCES} HwlocThreadBindingHttpNode.cpp)
	set(${HTTP_NODES_HEADERS} ${HTTP_NODES_SOURCES} HwlocThreadBindingHttpNode.h)
endif (HWLOC_FOUND)

######################################################
add_library(htopml-http-nodes ${HTTP_NODES_SOURCES})
target_link_libraries(htopml-http-nodes htopml-json htopml-server)
SET_TARGET_PROPERTIES(htopml-http-nodes PROPERTIES COMPILE_FLAGS -fPIC)
if (HWLOC_FOUND)
	target_link_libraries(htopml-http-nodes ${HWLOC_LIBRARIES})
endif (HWLOC_FOUND)

######################################################
#install procedure
INSTALL(FILES ${HTTP_NODES_HEADERS} DESTINATION include/htopml)
