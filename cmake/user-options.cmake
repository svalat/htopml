######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#User options
set(LIB_SUFFIX no CACHE STRING "Define the suffix to append to lib directory name to support lib64 exotic name on some distributions.")
set(ENABLE_JUNIT_OUTPUT no CACHE BOOL "Generate a JUnit XML file for each test while running svUnitTest test suite.")
set(ENABLE_VALGRIND no CACHE BOOL "Wrap all test execution with valgrind memcheck to generate XML report for each one.")
set(ENABLE_GCC_COVERAGE no CACHE BOOL "Compile htopml library with coverage GCC CFLAGS.")
set(DISABLE_TESTS no CACHE BOOL "Disable compilation of svUnitTest tests.")

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
        set(CMAKE_CXX_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_C_FLAGS "-O0 -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
ENDIF (ENABLE_GCC_COVERAGE)