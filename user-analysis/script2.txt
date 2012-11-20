#!/bin/bash

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

#footer
echo "</htopml>"
