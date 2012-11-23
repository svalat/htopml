#!/bin/bash

#check args
if [ -z "$1" ]; then
	echo "Invalid argument." 1>&2
	echo "Usage : $0 {file.xml|file.txt}" 1>&2
	exit 1
fi

#enable exit on error
set -e

#check for first phase conversion if we start from short txt format instead
#of full XML
case "$1" in
	*.xml)
		fname="$1"
		;;
	*.txt)
		#need convert step
		fname=$(tempfile -s '.xml')
		echo "Generate XML file : $fname"
		./quickdef2xml.sh "$1" > "$fname"
		;;
	*)
		echo "Invalid file extension $1, expect .xml or .txt" 1>&2
		exit 1
		;;
esac

#Generate all files
echo "==================== GENERATE ===================="
for tmp in *.template
do
	basename=$(echo $tmp | sed -e 's/\.template$//g')
	xslfile=$(tempfile -s '.xsl')
	echo "${basename}"
	echo "  + Generate ${xslfile}.xsl"
	./template2xslt.sh "${tmp}" > "${xslfile}.xsl"
	echo "  + Generate ${basename}"
	xsltproc -o "${basename}" "${xslfile}.xsl" "${fname}"
	echo "  + Remove temporaty ${xslfile}.xsl"
	rm -f "${xslfile}.xsl"
done

echo "=================================================="
echo "Done"

