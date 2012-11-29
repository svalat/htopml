function requestData() {
	$.ajax({
		url: 'environ.json',
		contentType: 'application/json; charset=utf-8',
		success: function(point) {
			var table = document.getElementById('vartable');
			var content = "";
			for (v in point)
			{
				var tr = document.createElement('tr');
				var tdName = document.createElement('td');
				tdName.innerText = v;
				var tdValue = document.createElement('td');
				//tdValue.style.setProperty("word-wrap","break-word");
				tdValue.innerText = point[v];
				tr.appendChild(tdName);
				tr.appendChild(tdValue);
				table.appendChild(tr);
			}
			
		},
		type: "GET",
//         async: false,
		error:function (xhr, status, error){
		alert("Erreur de chargement du fichier '"+self.url+"' : "+xhr.responseText+" ("+status+" - "+error+")");
		},
	});
}

$(document).ready(function() {
	requestData();
});