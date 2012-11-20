<?xml version="1.0"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text"/>

<xsl:template match="/htopml">
	<xsl:text>/*************** GENERATED FILE *****************/&#10;</xsl:text>
	<xsl:apply-templates match="graphs/graph"/>
<xsl:template>

<xsl:template match="graph">
<xsl:text>
$(function () {
var chart;
	function requestData() {
		$.ajax({
		url: '</xsl:text><xsl:value-of select='source'/><xsl:text>',
        contentType: 'application/json; charset=utf-8',
        success: function(data) {
            var series = chart.series[0],
                shift = series.data.length > 400; // shift if the series is longer than 20
//                 alert('ok');

            // add the point
            chart.series[0].addPoint(point.ru_nvcsw, true, shift);
			chart2.series[0].points[0].update(Math.round(point.memusage / 1024));
			chart3.series[0].addPoint(Math.round(point.memusage / 1024), true, shift);

            // call it again after one second
            setTimeout(requestData, 500);
        },
        type: "GET",
//         async: false,
        error:function (xhr, status, error){
		alert("Erreur de chargement du fichier '"+self.url+"' : "+xhr.responseText+" ("+status+" - "+error+")");
		},
    });
}
</xsl:text>
</xsl:template>

<xsl:template match="header">
	<xsl:value-of select="concat('#include &lt;',.,'&gt;&#10;')"/>
</xsl:template>

<xsl:template match="struct">
	<xsl:value-of select="concat('void typeToJson(htopml::JsonState&amp; json, std::ostream&amp; stream, const ',@typename,' &amp; value);&#10;')"/>
</xsl:template>

</xsl:stylesheet>