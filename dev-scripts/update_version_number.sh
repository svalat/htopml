#!/bin/bash
######################################################
#            PROJECT  : htmltop                      #
#            VERSION  : 0.1.0                        #
#            DATE     : 12/2015                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
# Script to quicly update de version numbers in sources.

######################################################
old_version="$1"
new_version="$2"

######################################################
#check parameter
if [ -z "$old_version" ] || [ -z "$new_version" ]; then
	echo "Usage : $0 {old_version} {new_version}"
	echo
	echo "Version format : major.minor.release[-dev|-rc1]"
	echo
	exit 1
fi

######################################################
#check format
#params :
#  - $1 : version value to check
function check_version_format()
{
	if [ -z "`echo \"$1\" | egrep '^[0-9]+\.[0-9]+\.[0-9]+(-dev|-rc[0-9]+)?$'`" ]
	then
		echo "Error : Invalid version format : $1"
		echo "        Must be major.minor.release[-dev|-rc1]"
		exit 1
	fi
}

######################################################
#check exec dir to force execution from project root dir
function check_exec_dir()
{
	if [ ! -f dev-scripts/update_version_number.sh ] || [ ! -f DEPENDENCIES.txt ] || [ ! -f COPYING-FR.txt ] ; then
		echo "Error: this script must be executed from project root dir as ./dev-scripts/update_version_number.sh"
		exit 1
	fi
}

######################################################
#get list of source files in which to update version
#params :
function get_file_list()
{
	git ls-files
}

######################################################
#update version in cpp headers
#params :
#   -$1 : old version
#   -$2 : new version
function update_version_cpp_headers()
{
	for file in `get_file_list`
	do
		sed -i "s/^             VERSION  : $1\$/             VERSION  : $2/g" "$file"
	done
}

######################################################
#update date in cpp headers
#params :
function update_date_cpp_headers()
{
	new_date=`date +%m/%Y`
	for file in `get_file_list`
	do
		sed -i -r "s@^             DATE     : [0-9]{2}/[0-9]{4}\$@             DATE     : ${new_date}@g" "$file"
	done
}

######################################################
#update version in script headers
#params :
#   -$1 : old version
#   -$2 : new version
function update_version_script_headers()
{
	orig=`printf "#            VERSION  : %-20s         #" "$1"`
	dest=`printf "#            VERSION  : %-20s         #" "$2"`
	for file in `get_file_list`
	do
		sed -i "s/^${orig}\$/${dest}/g" "$file"
	done
}

######################################################
#update date in scripts headers
#params :
function update_date_script_headers()
{
	new_date=`date +%m/%Y`
	for file in `get_file_list`
	do
		sed -i -r "s@^#            DATE     : [0-9]{2}/[0-9]{4}                      #\$@#            DATE     : ${new_date}                      #@g" "$file"
	done
}

######################################################
#update version in root CMakeLists.txt
#params :
#   -$1 : old version
#   -$2 : new version
function update_version_exotic_files()
{
	#root CMakeLists.txt (to define version of project)
	sed -i "s/^set(HTOPML_VERSION \"$1\")\$/set(HTOPML_VERSION \"$2\")/g" CMakeLists.txt
	sed -i "s/SET(CPACK_PACKAGE_VERSION \"$1\")/SET(CPACK_PACKAGE_VERSION \"$2\")/g" CMakeLists.txt
	#Doxyfile
	#sed -i "s/^PROJECT_NUMBER         = $1\$/PROJECT_NUMBER         = $2/g" Doxyfile
	#pkg-config template
	#sed -i "s/Version: $1/Version: $2/g" src/integration/pkg-config/svUnitTest.pc.in
	#packaging README
	#sed -i "s/svUnitTest-$1/svUnitTest-$2/g" packaging/README.txt
	#sed -i "s/svUnitTest_$1/svUnitTest_$2/g" packaging/README.txt
	#sed -i "s/v$1/v$2/g" packaging/README.txt
}

######################################################
#update date in exotic files
#params:
function update_date_exotic_files()
{
	new_date=`date +%m/%Y`
	#gollum update script
	#sed -i -r "s@echo \"             DATE     : [0-9]{2}/[0-9]{4}\"@echo \"             DATE     : ${new_date}\"@g" src/doxygen/update_from_gollum.sh
}

######################################################
#Display version not update in case of new files not supported by the script
#params :
#  - $1 : old version
function display_version_not_updated()
{
	echo "--------------------- Not updated : -------------------------"
	grep --color -R -I "$1" `git ls-files`
	echo "-------------------------------------------------------------"
}

######################################################
#check
check_version_format "$old_version"
check_version_format "$new_version"
check_exec_dir
#update headers
update_version_cpp_headers "$old_version" "$new_version"
update_version_script_headers "$old_version" "$new_version"
update_version_exotic_files "$old_version" "$new_version"
update_date_cpp_headers
update_date_script_headers
update_date_exotic_files
display_version_not_updated "$old_version"
