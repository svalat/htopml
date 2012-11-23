#!/bin/bash

echo "==================== GENERATE ===================="
for tmp in *.template
do
	basename=`echo $tmp | sed -e 's/\.template$//g'`
	echo "${basename}"
	echo "  + Generate ${basename}.xsl"
	./template2xslt.sh "${tmp}" > "${basename}.xsl"
	echo "  + Generate ${basename}"
	xsltproc -o "${basename}" "${basename}.xsl" quickdef.xml
	echo "  + Remove temporaty ${basename}.xsl"
	rm -f "${basename}.xsl"
done

echo "=================================================="
echo "Done"

