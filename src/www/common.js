//global arrays to remember what to update and from which source
var chartsToUpdate = new Array();
var sourceToUpdate = new Array();
var graphUpdateTime = 500;

//function used to mark sources for update
function htopmlMarkForUpdate(chart,source,func) {
	chart.htopmlUpdateSource = source;
	chart.htopmlUpdateFunc = func;
	chartsToUpdate.push(chart);
	sourceToUpdate[source] = true;
}

//update function
function htopmlUpdateGraphs() {
	for (var source in sourceToUpdate)
	{
		$.ajax({
			url: source,
			contentType: 'application/json; charset=utf-8',
			success: function(data) {
				for (var i in chartsToUpdate)
				{
					if (chartsToUpdate[i].htopmlUpdateSource == source)
						chartsToUpdate[i].htopmlUpdateFunc(chartsToUpdate[i],data);
				}
			},
			type: "GET",
			//async: false,
			/*error:function (xhr, status, error){
				alert("Erreur de chargement du fichier '"+self.url+"' : "+xhr.responseText+" ("+status+" - "+error+")");
			},*/
		});
	}
	setTimeout(htopmlUpdateGraphs, graphUpdateTime);
}
