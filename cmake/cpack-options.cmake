######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# This file provide the packaging options.

######################################################
#CPACK support
INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Provide a quick way to get a HTML tool like htop to survey application internals.")
SET(CPACK_PACKAGE_VENDOR "Sébastien Valat")
# SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING-EN.txt")
SET(CPACK_PACKAGE_VERSION "0.1.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_GENERATOR "TGZ;TBZ2;DEB")
SET(CPACK_PACKAGE_CONTACT "Sébastien Valat <sebastien.valat.dev@orange.fr>")
INCLUDE(CPack)
