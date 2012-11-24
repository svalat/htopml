#!/bin/bash

#check params
if [ -z "$1" ]; then
	echo "Invalid argument." 1>&2
	echo "Usage : $0 {file}" 1>&2
	exit 1
fi

#check file syntax
l=1
cat "$1" | while read line
do
	if [ ! -z "$line" ]; then
		case "$line" in
			'mountpoint '* | 'include '* | 'struct '* | 'export '* | 'graph-lines '* | 'typedef '*)
				;;
			*)
				echo "Invalid line format at line $l" 1>&2
				echo "$line" 1>&2
				exit 1
				;;
		esac
	fi
	l=$(($l+1))
done || exit 1

#header
echo "<?xml version='1.0'?>"
echo "<htopml>"

#gen mount point
mountpoint=$(cat "$1"  | grep '^mountpoint ' | awk '{print $2}' | tail -n 1)
echo "	<config>"
echo "		<root-mount-point>${mountpoint}</root-mount-point>"
echo "	</config>"

#setup include files
echo "	<headers>"
for tmp in $(cat quickdef.txt  | grep '^include ' | awk '{print $2}')
do
	echo "		<header>${tmp}</header>"
done
echo "	</headers>"

#typedefs
echo "	<typedefs>"
grep '^typedef ' quickdef.txt | while read tmp
do
	name=$(echo "$tmp" | awk '{print $2}')
	value=$(echo "$tmp" | cut -f 2 -d ':')
	echo "		<typedef name=\"${name}\">${value}</typedef>"
done
echo "	</typedefs>"

#structs
echo "	<structs>"
grep "^struct " "$1" | while read struct
do
	name=$(echo "$struct" | awk '{print $2}')
	echo "		<struct typename='${name}'>"
	for field in $(echo "$struct" | cut -f 2 -d ':')
	do
		if [ ! -z "$(echo "$field" | egrep '^[A-Za-z0-1_]+\[[0-9]+]$')" ]; then
				fname=$(echo "$field" | cut -f 1 -d '[')
				size=$(echo "$field" | cut -f 2 -d '[' | cut -f 1 -d ']')
				echo "			<array size='$size'>$fname</array>"
		else
				echo "			<field>$field</field>"
		fi
	done
	echo "		</struct>"
done
echo "	</structs>"

#exports
echo "	<exports>"
grep "^export " "$1" | while read exp
do
	name=$(echo "$exp" | awk '{print $2}')
	classname=$(echo "$name" |  perl -ne 'print ucfirst($_)')
	update=$(echo "$exp" | cut -f 2- -d ':' | sed -e 's/&/&amp;/g' -e 's/</&lt;/g' -e 's/>/&gt;/g')
	echo "		<export>"
	echo "			<name>$classname</name>"
	echo "			<mount>$name.json</mount>"
	echo "			<struct>$name</struct>"
	echo "			<update>$update</update>"
	echo "		</export>"
done
echo "	</exports>"

#graphs
echo "	<graphs>"
containerId=0
grep "^graph-lines " "$1" | while read graph
do
	struct=$(echo "$graph" | awk '{print $2}')
	source=$(echo "$graph" | awk '{print $2}')
	containerId=$(($containerId + 1))

	echo "		<graph-lines>"
	echo "			<container>container${containerId}</container>"
	echo "			<title>${struct}</title>"
	echo "			<xlabel>Time</xlabel>"
	echo "			<ylabel>Values from ${struct}</ylabel>"
	echo "			<maxpoints>400</maxpoints>"
	echo "			<refresh>500</refresh>"
	echo "			<source>${source}.json</source>"
	echo "			<series>"
	echo "$graph" | cut -f 2 -d ':' | sed -e 's/,/\n/g' | while read serie
	do
		case "$serie" in
			'delta('*)
				tmp=$(echo "$serie" | sed -e 's/delta\(.*\)/\1/g')
				echo "				<serie name=\"$tmp\" delta='true'>$tmp</serie>"
				;;
			*)
				echo "				<serie name=\"$serie\">$serie</serie>"
				;;
			esac
	done
	echo "			</series>"
	echo "		</graph-lines>"
done
echo "	</graphs>"

#footer
echo "</htopml>"
