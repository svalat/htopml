<?xml version='1.0'?>
<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="html" indent="yes" encoding="UTF-8" doctype-public="-//W3C//DTD HTML 4.01//EN" doctype-system="http://www.w3.org/TR/html4/strict.dtd"/>

<xsl:template match="/htopml">
	<html>
		<head>
			<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
			<title>Htopml - Automatic page</title>
			<script type="text/javascript" src="/ressources/jquery/jquery.min.js"></script>
		</head>
		<body>
			<script src="/ressources/highcharts/js/highcharts.js"></script>
			<script src="/ressources/highcharts/js/modules/exporting.js"></script>
			<script src="/ressources/highcharts/js/highcharts-more.js"></script>
			<!-- Additional files for the Highslide popup effect -->
			<!-- <script type="text/javascript" src="http://www.highcharts.com/highslide/highslide-full.min.js"></script> -->
			<!-- <script type="text/javascript" src="http://www.highcharts.com/highslide/highslide.config.js" charset="utf-8"></script> -->
			<!-- <link rel="stylesheet" type="text/css" href="http://www.highcharts.com/highslide/highslide.css" /> -->
			<!-- Import use graphs -->
			<script>
				<xsl:attribute name="src"><xsl:value-of select="config/root-mount-point"/>/HtopmlAutoGraphs.js</xsl:attribute>
			</script>
			<xsl:apply-templates select="graphs"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="graphs">
	<xsl:for-each select="graph-lines">
		<div style="min-width: 400px; height: 400px; margin: 0 auto">
			<xsl:attribute name="id"><xsl:value-of select="container"/></xsl:attribute>
		</div>
	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
