<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/htopml">
	<xsl:text>/*************** GENERATED FILE *****************/&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#include "HtopmlAutoTypeToJson.h"&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:apply-templates select="structs/struct"/>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

<xsl:template match="header">
	<xsl:value-of select="concat('#include &lt;',.,'&gt;&#10;')"/>
</xsl:template>

<xsl:template match="struct">
	<xsl:value-of select="concat('void typeToJson(htopml::JsonState&amp; json, std::ostream&amp; stream, const ',@typename,' &amp; value)&#10;')"/>
	<xsl:text>{&#10;</xsl:text>
		<xsl:text>&#09;json.openStruct();&#10;</xsl:text>
		<xsl:apply-templates select="field|array"/>
		<xsl:text>&#09;json.closeStruct();&#10;</xsl:text>
	<xsl:text>}&#10;</xsl:text>
</xsl:template>

<xsl:template match="field">
	<xsl:value-of select="concat('&#09;json.printField(&quot;',.,'&quot;,value.',.,');&#10;')"/>
</xsl:template>

<xsl:template match="array">
	<xsl:value-of select="concat('&#09;json.printFieldArray(&quot;',.,'&quot;,value.',.,',',@size,');&#10;')"/>
</xsl:template>

</xsl:stylesheet>
