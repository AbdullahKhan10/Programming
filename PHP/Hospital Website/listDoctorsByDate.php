<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>Doctor Information</title>
	</head>
	<body>
	<?php
		include 'connectdb.php';
	?>
	<h1>Here is the information of your specified doctor:</h1>
	<ol>
	<?php
   		$doctorDate = $_POST["doctorDate"]; //get the date that the user specifed to get the doctor after that date
		if ($doctorDate == "") { //check if a date was selected for sure
			echo 'No date selected!' . '<br>';
		} 
		$query = 'SELECT first_name, last_name, specialty, date_licensed FROM doctor WHERE date_licensed < "' . $doctorDate . '"'; //gets all the doctors after a particular day which they got their license
		$result = mysqli_query($connection, $query); //run the query
	        if (mysqli_num_rows($result) == 0) { //check if it works
                        echo 'No matching results!'; //otherwise tell user there are no matching results
                }

    		if (!$result) { //checks for errors
         		die("database query failed."); //tell user the query failed
     		}
    		while ($row = mysqli_fetch_assoc($result)) { //print all the doctors according to the query above
        		echo '<li>';
			echo $row["first_name"] . ' ' . $row["last_name"] . ', ' . $row["specialty"] . ', ' . $row["date_licensed"];
			echo "<br>"; 
     		}
     		mysqli_free_result($result); //free the results
	?>
	</ol>
	<?php
   		mysqli_close($connection); //close the connection
	?>
	</body>
</html>
