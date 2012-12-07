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

/* Function to quickly fill an array with a key => value representation */
function htopmlFillVarArray(tableId,data)
{
	var table = document.getElementById(tableId);
	var content = "";
	for (v in data)
	{
		var tr = document.createElement('tr');
		var tdName = document.createElement('td');
		var pre = document.createElement('pre');
		pre.innerHTML = v;
		tdName.appendChild(pre);
		var tdValue = document.createElement('td');
		//tdValue.style.setProperty("word-wrap","break-word");
		pre = document.createElement('pre');
		pre.innerHTML = data[v];
		tdValue.appendChild(pre);
		tr.appendChild(tdName);
		tr.appendChild(tdValue);
		table.appendChild(tr);
	}
}

/* Load a table value (with key => value format) from a fiven URL and fill an html table with it. */
function htopmlFillVarArrayFromUrl(tableId,updateUrl) {
	$.ajax({
		url: updateUrl,
		contentType: 'application/json; charset=utf-8',
		success: function(point) {
			htopmlFillVarArray(tableId,point);
		},
		type: "GET",
		//async: false,
		//error:function (xhr, status, error){
		//alert("Erreur de chargement du fichier '"+self.url+"' : "+xhr.responseText+" ("+status+" - "+error+")");
		//},
	});
}
