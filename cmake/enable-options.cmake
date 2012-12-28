######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# Final setup of flags to take in account availability
# of optional deps.
# Also display a final summary of global flags status.

######################################################
if (NOT SVUNITTEST_FOUND)
	set(SVUNITTEST_LIBRARY "")
	set(SVUNITTEST_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/extern-deps/svUnitTest_fake")
endif (NOT SVUNITTEST_FOUND)

######################################################
#Enable hwloc in sources
if (HWLOC_FOUND)
	include_directories(${HWLOC_INCLUDE_DIRS})
	add_definitions(-DHAVE_HWLOC)
endif (HWLOC_FOUND)

######################################################
print_variable_status("ENABLE_JUNIT_OUTPUT")
print_variable_status("ENABLE_VALGRIND")
print_variable_status("ENABLE_GCC_COVERAGE")
print_variable_status("ENABLE_LOCAL_PATHS")
print_variable_status("ENABLE_RPATH")
print_variable_status("DISABLE_TESTS")
print_variable_status("HWLOC_FOUND")