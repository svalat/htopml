<?xml version='1.0'?>
<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="html" indent="yes" encoding="UTF-8" doctype-public="-//W3C//DTD HTML 4.01//EN" doctype-system="http://www.w3.org/TR/html4/strict.dtd"/>

<xsl:template match="/htopml">
	<html>
		<head>
			<title>Htopml - Automatic page</title>
			<script>
				<xsl:attribute name="src"><xsl:value-of select="config/root-mount-point"/>/{{FILE_PREFIX}}-graphs.js</xsl:attribute>
			</script>
		</head>
		<body>
			<xsl:apply-templates select="graphs"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="graphs">
	<xsl:apply-templates select="graph-lines|hash-table"/>
</xsl:template>

<xsl:template match="graph-lines">
	<div class='section'>
		<div style="min-width: 400px; height: 400px; margin: 0 auto">
			<xsl:attribute name="id"><xsl:value-of select="container"/></xsl:attribute>
		</div>
	</div>
</xsl:template>

<xsl:template match="hash-table">
	<div class='section'>
		<h1><xsl:value-of select='title'/></h1>
		<table class='data-table'>
			<xsl:attribute name='id'><xsl:value-of select='container'/></xsl:attribute>
			<tr>
				<th color='yellow'><xsl:value-of select='key-label'/></th>
				<th color='yellow'><xsl:value-of select='value-label'/></th>
			</tr>
		</table>
	</div>
</xsl:template>

</xsl:stylesheet>
