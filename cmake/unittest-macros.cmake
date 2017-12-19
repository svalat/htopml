######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.2.0                        #
#            DATE     : 12/2017                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# Define some macro for unit test execution and definition
# It's better to use this wrapper to get good integration
# in jenkins infrastructure.

######################################################
find_package (Threads)

######################################################
#For integration of tests in jenkins, but only in self-test mode
macro (htopml_add_test test_name)
	#steup wrapper
	if (ENABLE_VALGRIND)
			set(tmp_test_wrapper valgrind --xml=yes --xml-file=${CMAKE_CURRENT_BINARY_DIR}/${test_name}.memcheck.xml --tool=memcheck --leak-check=full --show-reachable=yes)
	else(ENABLE_VALGRIND)
			set(tmp_test_wrapper "")
	endif(ENABLE_VALGRIND)

	#setup output options
	if (ENABLE_JUNIT_OUTPUT)
		set(tmp_test_run_option -m junit_xml -o ${CMAKE_CURRENT_BINARY_DIR}/${test_name}.junit.xml)
	endif (ENABLE_JUNIT_OUTPUT)

	#gen text command and register
	add_test(${test_name} ${tmp_test_wrapper} ${CMAKE_CURRENT_BINARY_DIR}/${test_name} ${tmp_test_run_option})
	target_link_libraries (${test_name} ${CMAKE_THREAD_LIBS_INIT})
endmacro (htopml_add_test)
