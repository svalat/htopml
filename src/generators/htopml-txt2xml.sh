#!/bin/bash
######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#Extract params
FILE="$1"

######################################################
#set debug mode
set -e
#set -x

######################################################
#check params
if [ -z "${FILE}" ]; then
	echo "Invalid argument." 1>&2
	echo "Usage : $0 {file.txt}" 1>&2
	exit 1
fi

######################################################
#Check file syntax
# Params : {file}
function check_file_syntax()
{
	#vars
	local file="$1"
	local count=1
	local line=''

	#loop on all lines to check
	cat "${file}" | while read line
	do
		if [ ! -z "${line}" ]; then
			case "${line}" in
				'mountpoint '* | 'include '* | 'struct '* | 'export '* | 'graph-lines '* | 'typedef '*)
					;;
				*)
					echo "Invalid line format at line ${count}" 1>&2
					echo "${line}" 1>&2
					exit 1
					;;
			esac
		fi
		count=$(( ${count} + 1 ))
	done || exit 1
}

######################################################
#header
function print_header()
{
	echo "<?xml version='1.0'?>"
	echo "<htopml>"
}

######################################################
#gen mount point
#Params : {file}
function print_mount_point()
{
	#vars
	local file="$1"
	local mountpoint=$(cat "${file}"  | grep '^mountpoint ' | awk '{print $2}' | tail -n 1)

	#gen xml
	echo "	<config>"
	echo "		<root-mount-point>${mountpoint}</root-mount-point>"
	echo "	</config>"
}

######################################################
#setup include files
#Params : {file}
function print_include_files()
{
	#vars
	local file="$1"
	local header=''

	#open balis
	echo "	<headers>"

	#loop on headers
	for header in $(cat "${file}"  | grep '^include ' | awk '{print $2}')
	do
		echo "		<header>${header}</header>"
	done

	#close balis
	echo "	</headers>"
}

######################################################
#typedefs
#Parms ; {file}
function print_typedefs()
{
	#vars
	local file="$1"
	local name=''
	local value=''
	local line=''

	#open balis
	echo "	<typedefs>"

	#loop on all typedef lines
	grep '^typedef ' "${file}" | while read line
	do
		name=$(echo "$line" | awk '{print $2}')
		value=$(echo "$line" | cut -f 2 -d ':')
		echo "		<typedef name=\"${name}\">${value}</typedef>"
	done

	#close balis
	echo "	</typedefs>"
}

######################################################
#struct
#Params : "${struct_line}"
function print_struct()
{
	#vars
	local line="$1"
	local name=$(echo "$line" | awk '{print $2}')
	local field=''
	local fname=''
	local size=''

	#open balis
	echo "		<struct typename='${name}'>"
	
	for field in $(echo "${line}" | cut -f 2 -d ':')
	do
		if [ ! -z "$(echo "${field}" | egrep '^[A-Za-z0-1_]+\[[0-9]+]$')" ]; then
			fname=$(echo "${field}" | cut -f 1 -d '[')
			size=$(echo "${field}" | cut -f 2 -d '[' | cut -f 1 -d ']')
			echo "			<array size='${size}'>${fname}</array>"
		else
			echo "			<field>${field}</field>"
		fi
	done

	#close balis
	echo "		</struct>"
}

######################################################
#structs
#Prams : {file}
function print_structs()
{
	#vars
	local file="$1"
	local line=''

	#open balis
	echo "	<structs>"
	grep "^struct " "${file}" | while read line
	do
		print_struct "${line}"
	done
	echo "	</structs>"
}

######################################################
#exports
#Params : {file}
function print_exports()
{
	#vars
	local file="$1"
	local line=''
	local name=''
	local classname=''
	local update=''

	#open balis
	echo "	<exports>"

	#loop on exports
	grep "^export " "${file}" | while read line
	do
		name=$(echo "${line}" | awk '{print $2}')
		classname=$(echo "${name}" |  perl -ne 'print ucfirst($_)')
		update=$(echo "${line}" | cut -f 2- -d ':' | sed -e 's/&/&amp;/g' -e 's/</&lt;/g' -e 's/>/&gt;/g')
		echo "		<export>"
		echo "			<name>${classname}</name>"
		echo "			<mount>${name}.json</mount>"
		echo "			<struct>${name}</struct>"
		echo "			<update>${update}</update>"
		echo "		</export>"
	done

	#close balis
	echo "	</exports>"
}

######################################################
#graph series
#params : {txt series}
function print_graph_series()
{
	local series="$1"
	local serie=''

	echo "${series}" | sed -e 's/,/\n/g' | while read serie
	do
		case "${serie}" in
			'delta('*)
				tmp=$(echo "${serie}" | sed -e 's/delta\(.*\)/\1/g')
				echo "				<serie name=\"${tmp}\" delta='true'>${tmp}</serie>"
				;;
			*)
				echo "				<serie name=\"${serie}\">${serie}</serie>"
				;;
			esac
	done
}

######################################################
#graphs
#params : {file}
function print_graphs()
{
	#vars
	local file="$1"
	local containerId=0
	local line=''
	local struct=''
	local source=''
	local series=''

	#open balis
	echo "	<graphs>"

	#loop on graph lines
	grep "^graph-lines " "${file}" | while read line
	do
		#extract info
		struct=$(echo "${line}" | awk '{print $2}')
		source=$(echo "${line}" | awk '{print $2}')
		containerId=$(( ${containerId} + 1 ))

		#gen output
		echo "		<graph-lines>"
		echo "			<container>container${containerId}</container>"
		echo "			<title>${struct}</title>"
		echo "			<xlabel>Time</xlabel>"
		echo "			<ylabel>Values from ${struct}</ylabel>"
		echo "			<maxpoints>400</maxpoints>"
		echo "			<refresh>500</refresh>"
		echo "			<source>${source}.json</source>"

		#gen series
		echo "			<series>"
		series="$(echo "${line}" | cut -f 2 -d ':')"
		print_graph_series "${series}"
		echo "			</series>"
		
		echo "		</graph-lines>"
	done

	#close balis
	echo "	</graphs>"
}

######################################################
#footer
#Params : {file}
function print_footer()
{
	echo "</htopml>"
}

######################################################
#Main code
check_file_syntax "${FILE}"
print_header
print_mount_point "${FILE}"
print_include_files "${FILE}"
print_typedefs "${FILE}"
print_structs "${FILE}"
print_exports "${FILE}"
print_graphs "${FILE}"
print_footer
