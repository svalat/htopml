#!/bin/bash

for tmp in *.xsl
do
	outname=`echo $tmp | sed -e 's/\.xsl$//g'`
	echo "Generate $outname"
	xsltproc -o $outname $tmp quickdef.xml
done
