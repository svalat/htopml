<?xml version='1.0'?>
<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="html" indent="yes" encoding="UTF-8" doctype-public="-//W3C//DTD HTML 4.01//EN" doctype-system="http://www.w3.org/TR/html4/strict.dtd"/>

<xsl:template match="/htopml">
	<html>
		<head>
			<title>Htopml - Automatic page</title>
			<script>
				<xsl:attribute name="src"><xsl:value-of select="config/root-mount-point"/>/HtopmlAutoGraphs.js</xsl:attribute>
			</script>
		</head>
		<body>
			<xsl:apply-templates select="graphs"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="graphs">
	<xsl:for-each select="graph-lines">
		<div class='section'>
			<div style="min-width: 400px; height: 400px; margin: 0 auto">
				<xsl:attribute name="id"><xsl:value-of select="container"/></xsl:attribute>
			</div>
		</div>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
