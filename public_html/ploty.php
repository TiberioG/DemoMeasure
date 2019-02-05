 <?php

	include("connect.php"); 	
	
	$link=Connection();
    mysql_query("SET time_zone = Europe/Rome ", $link);
    $query ="SELECT * FROM `tempLog`  ORDER BY `timeStamp` ASC";
	
 
?>
  <html>
  <head>
 
<body>
  
  <div id="divo"></div>

</body>
 

 
 <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
  <script src="https://cdn.plot.ly/plotly-latest.min.js"></script>
    <script type =text/javascript>
		var graphDiv = document.getElementById('divo');
		var trace1 = {
			x:[
				<?php
				$result=mysql_query($query,$link);
				if($result!==FALSE){
					while($row = mysql_fetch_array($result)) {
						echo "'".$row['timeStamp']."'" ;
						echo ", ";
					}
				}
				?>
			],
			
			y: [
				<?php 
				$result=mysql_query($query,$link);
				if($result!==FALSE){
					while($row = mysql_fetch_array($result)) {
						echo $row['temperature'] ;
						echo ",";
					}
				}
				?>
			],
			name: 'Temperature',
			type: 'scatter',
		};
		
		var trace2 = {
			x:[
				<?php
				$result=mysql_query($query,$link);
				if($result!==FALSE){
					while($row = mysql_fetch_array($result)) {
						echo "'".$row['timeStamp']."'" ;
						echo ", ";
					}
				}
				?>
			],
			
			y: [
				<?php 
				$result=mysql_query($query,$link);
				if($result!==FALSE){
					while($row = mysql_fetch_array($result)) {
						echo $row['humidity'] ;
						echo ",";
					}
				}
				?>
			],
			name: 'Humidity',
			yaxis: 'y2',
			type: 'scatter',
		};
		
		var layout = {
			title: 'Temperature & Humidity chart',
			yaxis: {title: 'Temperature °C'},
			yaxis2: {
				title: 'Humidity',
				titlefont: {color: 'rgb(148, 103, 189)'},
				tickfont: {color: 'rgb(148, 103, 189)'},
				overlaying: 'y',
				side: 'right'}
		};

		
		
		
var data = [trace1, trace2];

Plotly.newPlot(graphDiv, data, layout, {}, {showSendToCloud: true});
	  </script>
   
   
   
   
   
   
   
   
   
   
   
   
</html>