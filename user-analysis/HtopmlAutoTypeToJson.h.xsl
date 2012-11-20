<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/htopml">
	<xsl:text>/*************** GENERATED FILE *****************/&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#ifndef HTOPML_AUTO_JSON_TO_TYPE_H&#10;</xsl:text>
	<xsl:text>#define HTOPML_AUTO_JSON_TO_TYPE_H&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#include "../src/json/TypeToJson.h"&#10;</xsl:text>
	<xsl:apply-templates select="headers/header"/>
	<xsl:text>&#10;</xsl:text>
	<xsl:apply-templates select="structs/struct"/>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#endif //HTOPML_AUTO_JSON_TO_TYPE_H&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

<xsl:template match="header">
	<xsl:value-of select="concat('#include &lt;',.,'&gt;&#10;')"/>
</xsl:template>

<xsl:template match="struct">
	<xsl:value-of select="concat('void typeToJson(htopml::JsonState&amp; json, std::ostream&amp; stream, const ',@typename,' &amp; value);&#10;')"/>
</xsl:template>

</xsl:stylesheet>
