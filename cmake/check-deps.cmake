######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# File to check all extern package deps. If optional
# We must not fail here, only check.

######################################################
find_package(Threads REQUIRED)
find_package(svUnitTest QUIET)
find_package(Hwloc QUIET)