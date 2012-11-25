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
shift 1
FILTER="$*"

######################################################
#Find install dir to get access to lib scripts and templates
HTOPML_PREFIX="$(dirname "$0")/.."
TEMPLATES_DIR="${HTOPML_PREFIX}/share/htopml/templates/"
SCRIPT_LIB_DIR="${HTOPML_PREFIX}/share/htopml/scripts/"
BIN_DIR="${HTOPML_PREFIX}/bin"
FILE_PREFIX=$(basename ${FILE} | sed -e 's/\.txt//g' -e 's/\.xml//g')

######################################################
#enable exit on error
set -e
#set -x

######################################################
#check args
if [ -z "${FILE}" ]; then
	echo "Invalid argument." 1>&2
	echo "Usage : $0 {file.xml|file.txt} [list_of_files_to_generate]" 1>&2
	exit 1
fi

######################################################
#check for first phase conversion if we start from short txt format instead
#of full XML
case "${FILE}" in
	*.xml)
		fname="${FILE}"
		;;
	*.txt)
		#need convert step
		fname="$(basename "${FILE}" | sed -e 's/\.txt$/.xml/g')"
		echo "Generate XML file : ${fname}"
		"${SCRIPT_LIB_DIR}/htopml-txt2xml.sh" "${FILE}" > "${fname}"
		;;
	*)
		echo "Invalid file extension ${FILE}, expect .xml or .txt" 1>&2
		exit 1
		;;
esac

######################################################
#Params : {filename}
function check_if_want_to_gen()
{
	if [ -z "${FILTER}" ]; then
		return 0
	else
		case " ${FILTER} " in
			*" $1 "*)
				return 0;
				;;
			*)
				return 1;
				;;
		esac
	fi
}

######################################################
echo "==================== GENERATE ===================="

######################################################
#Generate all files from templates
for tmp in "${TEMPLATES_DIR}/"*.template
do
	#calc names
	outfname=$(basename "$tmp" | sed -e 's/\.template$//g')
	xslfile=$(tempfile -s '.xsl')

	#add prefix
	outfname="${FILE_PREFIX}-${outfname}"

	#Check if want to gen
	if check_if_want_to_gen "${outfname}"
	then
		#gen and display
		echo "${outfname}"
		echo "  + Generate ${xslfile}"
		"${SCRIPT_LIB_DIR}/htopml-template2xslt.sh" "${tmp}" > "${xslfile}"
		echo "  + Generate ${outfname}"
		xsltproc -o "${outfname}" "${xslfile}" "${fname}"
		sed -i "s/{{FILE_PREFIX}}/${FILE_PREFIX}/g" "${outfname}"
		echo "  + Remove temporaty ${xslfile}"
		rm -f "${xslfile}"
	else
		echo "${outfname} [SKIPED]"
	fi
done

######################################################
#Generate all files from XSLT
for tmp in "${TEMPLATES_DIR}/"*.xsl
do
	#calc names
	outfname=$(basename "$tmp" | sed -e 's/\.xsl$//g')
	xslfile=$tmp

	#add prefix
	outfname="${FILE_PREFIX}-${outfname}"

	#Check if want to gen
	if check_if_want_to_gen "${outfname}"
	then
		#display
		echo "${outfname}"
		echo "  + Generate ${outfname}"
		xsltproc -o "${outfname}" "${xslfile}" "${fname}"
		sed -e "s/{{FILE_PREFIX}}/${FILE_PREFIX}/g" -e "s/%7B%7BFILE_PREFIX%7D%7D/${FILE_PREFIX}/g" -i "${outfname}"
	else
		echo "${outfname} [SKIPED]"
	fi
done

######################################################
#setup makefile
if check_if_want_to_gen "Makefile"
then
	echo "Makefile"
	echo "  + Generate Makefile"
	sed -e "s/{{FILE_PREFIX}}/${FILE_PREFIX}/g" -e "s#{{HTOPML_PREFIX}}#${HTOPML_PREFIX}#g" "${TEMPLATES_DIR}/Makefile.in" > Makefile
else
	echo "Makefile [SKIPED]"
fi

######################################################
#copy main.cpp
#setup makefile
if check_if_want_to_gen "Makefile"
then
	echo "main.cpp"
	echo "  + Generate main.cpp"
	cp "${TEMPLATES_DIR}/main.cpp" 'main.cpp'
else
	echo "main.cpp [SKIPED]"
fi

######################################################
echo "=================================================="
echo "Done"
