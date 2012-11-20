<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/htopml">
	<xsl:text>/*************** GENERATED FILE *****************/&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#ifndef HTOPML_AUTO_HTTP_NODE_H&#10;</xsl:text>
	<xsl:text>#define HTOPML_AUTO_HTTP_NODE_H&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>#include "../src/server/HttpServer.h"&#10;</xsl:text>
	<xsl:text>#include "../src/server/JsonHttpNode.h"&#10;</xsl:text>
	<xsl:text>#include "HtopmlAutoTypeToJson.h"&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:text>void register_user_pages(htopml::HttpServer &amp;server);&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
	<xsl:apply-templates select="exports/export"/>
	<xsl:text>#endif //HTOPML_AUTO_HTTP_NODE_H&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

<xsl:template match="export">
	<xsl:value-of select="concat('class ',name,'HttpNode : public htopml::JsonHttpNode&lt;',struct,'&gt;&#10;')"/>
	<xsl:text>{&#10;</xsl:text>
	<xsl:text>&#09;public:&#10;</xsl:text>
	<xsl:value-of select="concat('&#09;&#09;',name,'HttpNode(const std::string &amp; addr);&#10;')"/>
	<xsl:text>&#09;&#09;virtual void onRequest(const htopml::HttpRequest &amp; request);&#10;</xsl:text>
	<xsl:text>&#09;private:&#10;</xsl:text>
	<xsl:value-of select="concat('&#09;&#09;',struct,' data;&#10;')"/>
	<xsl:text>};&#10;</xsl:text>
	<xsl:text>&#10;</xsl:text>
</xsl:template>

</xsl:stylesheet>
