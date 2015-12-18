######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

# Base source copied from cmake usr/share/cmake/Modules/Findhtopml.cmake
# Thanks to them.

# Find the htopml library
#
#  This module defines the following variables:
#     HTOPML_FOUND       - True if HTOPML_INCLUDE_DIR & htopml_LIBRARY are found
#     HTOPML_LIBRARIES   - Set when HTOPML_LIBRARY is found
#     HTOPML_INCLUDE_DIRS - Set when HTOPML_INCLUDE_DIR is found
#
#     HTOPML_INCLUDE_DIR - where to find htopml/HtopmlHttpServer.h, etc.
#     HTOPML_LIBRARY     - the htopml library
#

find_path(HTOPML_INCLUDE_DIR
	NAMES htopml/HtopmlHttpServer.h
	PATHS ${HTOPML_PREFIX}/include /usr/local/include
	DOC "The htopml include directory"
)

find_library(HTOPML_LIBRARY
	NAMES htopml
	PATHS ${HTOPML_PREFIX}/lib /usr/local/lib
	DOC "The htopml library"
)

# handle the QUIETLY and REQUIRED arguments and set htopml_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(htopml DEFAULT_MSG HTOPML_LIBRARY HTOPML_INCLUDE_DIR)

if(HTOPML_FOUND)
  set( HTOPML_LIBRARIES ${HTOPML_LIBRARY} )
  set( HTOPML_INCLUDE_DIRS ${HTOPML_INCLUDE_DIR} )
endif()

mark_as_advanced(HTOPML_INCLUDE_DIR HTOPML_LIBRARY)
