######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# Define all user options and also apply them if their
# is no link with optional extern deps.

######################################################
#User options
set(LIB_SUFFIX          no CACHE STRING "Define the suffix to append to lib directory name to support lib64 exotic name on some distributions.")
set(ENABLE_JUNIT_OUTPUT no CACHE BOOL   "Generate a JUnit XML file for each test while running svUnitTest test suite.")
set(ENABLE_VALGRIND     no CACHE BOOL   "Wrap all test execution with valgrind memcheck to generate XML report for each one.")
set(ENABLE_GCC_COVERAGE no CACHE BOOL   "Compile htopml library with coverage GCC CFLAGS.")
set(DISABLE_TESTS       no CACHE BOOL   "Disable compilation of svUnitTest tests.")
set(ENABLE_LOCAL_PATHS  no CACHE BOOL   "Setup absolute path to run in build directory, not for installation.")
set(ENABLE_RPATH        no CACHE BOOL   "Force to use rpath for all libs when installing.")
set(ENABLE_LISTEN_ALL   no CACHE BOOL   "Enable listening of all interface instead of 127.0.0.1.")

######################################################
#Take care of lib suffix for lib64 directory on some distributions
if (NOT LIB_SUFFIX)
	set(LIB_SUFFIX "")
endif (NOT LIB_SUFFIX)
message(STATUS "LIB_SUFFIX : ${LIB_SUFFIX}")

######################################################
#Display info on current configuration
macro (print_variable_status var_name)
	if (${var_name})
		message(STATUS "${var_name} : yes")
	else (${var_value})
		message(STATUS "${var_name} : no")
	endif (${var_name})
endmacro (print_variable_status)

######################################################
#enable coverage profiling
IF (ENABLE_GCC_COVERAGE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fprofile-arcs -ftest-coverage")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -fprofile-arcs -ftest-coverage")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
ENDIF (ENABLE_GCC_COVERAGE)

######################################################
IF (ENABLE_LOCAL_PATHS)
	add_definitions(-DHTOPML_EXTDEPS_PATH="${CMAKE_SOURCE_DIR}/extern-deps")
	add_definitions(-DHTOPML_WWW_PATH="${CMAKE_SOURCE_DIR}/src/www")
ELSE (ENABLE_LOCAL_PATHS)
	add_definitions(-DHTOPML_EXTDEPS_PATH="${CMAKE_INSTALL_PREFIX}/share/htopml/www")
	add_definitions(-DHTOPML_WWW_PATH="${CMAKE_INSTALL_PREFIX}/share/htopml/www")
ENDIF (ENABLE_LOCAL_PATHS)

######################################################
IF (ENABLE_RPATH)
	SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
	SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
ENDIF(ENABLE_RPATH)

######################################################
IF (ENABLE_LISTEN_ALL)
	add_definitions(-DENABLE_LISTEN_ALL)
ENDIF (ENABLE_LISTEN_ALL)
