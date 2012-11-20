<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/htopml">
	<xsl:text>/*************** GENERATED FILE *****************/&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#include "HtopmlAutoHttpNodes.h"&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:apply-templates select="exports/export"/>
	<xsl:call-template name="gen-user-pages-function"/>
</xsl:template>

<xsl:template match="export">
	<xsl:value-of select="concat(name,'HttpNode::',name,'HttpNode(const std::string &amp; addr)&#10;')"/>
	<xsl:value-of select="concat('&#09;:htopml::JsonHttpNode&lt;',struct,'&gt;(addr,&amp;data)&#10;')"/>
	<xsl:text>{&#10;</xsl:text>
	<xsl:text>};&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>

	<xsl:value-of select="concat('void ',name,'HttpNode::',name,'HttpNode(const htopml::HttpRequest &amp; request)&#10;')"/>
	<xsl:text>{&#10;</xsl:text>
	<xsl:value-of select="concat('&#09;',update,'&#10;')"/>
	<xsl:text>};&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

<xsl:template name='gen-user-pages-function'>
	<xsl:text>void register_user_pages(htopml::HttpServer &amp; server)&#10;</xsl:text>
	<xsl:text>{&#10;</xsl:text>
	<xsl:for-each select="exports/export">
		<xsl:value-of select="concat('&#09;server.registerHttpNode(new ',name,'HttpNode(&quot;',/htopml/config/root-mount-point,'/',mount,'&quot;),true);&#10;')"/>
	</xsl:for-each>
	<xsl:text>};&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

</xsl:stylesheet>
