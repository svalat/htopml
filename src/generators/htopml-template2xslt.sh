#!/bin/bash
######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sébastien              #
#            LICENSE  : CeCILL-C                     #
######################################################

######################################################
#extract args
FILE="$1"

######################################################
#exit with error on command failure
set -e
#set -x

######################################################
#check args
if [ -z "${FILE}" ]; then
	echo "Invalid arguments" 1>&2
	echo "Usage : $0 {file.template}" 1>&2
	exit 1
fi

######################################################
#header
echo "<?xml version='1.0'?>"
echo "<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>"
echo "<xsl:output method='text'/>"
echo "<xsl:template match='/'>"
printf "<xsl:text>"

######################################################
#This is a tweak to keep indent tabs with 'read line'
IFS=''

######################################################
#replace standard XML marks
sed -e 's/&/&amp;/g' -e 's/>/\&gt;/g' -e 's/</\&lt;/g' -e 's/"/\&quot;/g' \
	-e 's#$XSL{{\([@/A-Za-z0-9_\.\-]*\)}}#</xsl:text><xsl:value-of select="\1"/><xsl:text>#g' \
	"$1" | while read line
do
	case "$line" in
		*'//XSL-FOREACH '*)
			xpath=$(echo "$line" | awk '{print $2}')
			echo "</xsl:text>"
			echo "<xsl:for-each select=\"${xpath}\">"
			printf "<xsl:text>"
			;;
		*'//XSL-END-FOREACH')
			echo "</xsl:text>"
			echo "</xsl:for-each>"
			printf "<xsl:text>"
			;;
		*'//XSL-IF '*)
			xpath="$(echo "$line" | cut -f 2- -d ' ')"
			echo "</xsl:text>"
			echo "<xsl:if test=\"${xpath}\">"
			printf "<xsl:text>"
			;;
		*'//XSL-END-IF')
			echo "</xsl:text>"
			echo "</xsl:if>"
			printf "<xsl:text>"
			;;
		*)
			echo "$line"
			;;
	esac
done

######################################################
#footer
echo "</xsl:text>"
echo "</xsl:template>"
echo "</xsl:stylesheet>"
