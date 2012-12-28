#!/bin/bash
######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# Compile and run all tests in coverage mode to generate
# test coverage report

######################################################
#check current location
if [ ! -d 'tests' ] || [ ! -e 'Makefile' ]; then
	echo "You must run this from a subdirectory after doing ../configure --enable-gcc-coverage" 1>&2
	exit 1
fi

######################################################
# setup test list
TEST_LIST="./tests/testCommon ./tests/testJson ./tests/testHttpNode"

######################################################
#enable debug
set -x
#set -e

######################################################
# Remove old file
rm -f out.info || exit 1

######################################################
#run all tests
for t in ${TEST_LIST}
do
	find ./ -iname '*.gcda' -delete
	$t
	lcov -o out.info -c -d .  || exit 1
done

######################################################
genhtml -o html out.info || exit 1
