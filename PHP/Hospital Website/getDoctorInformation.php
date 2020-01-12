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
	<?php
   		$doctorName  = $_POST["doctorName"]; //get the doctor's name from input 
		if ($doctorName == "") { //check if it empty
			echo 'No doctors selected!'; //tell user it is empty
		}
		//the query below gets all the information of the doctor and even the name of the hospital rather than the code
		$query = 'SELECT doctor.license_number, doctor.first_name, doctor.last_name, doctor.specialty, doctor.date_licensed, hospital.name AS works_at FROM doctor JOIN hospital ON doctor.works_at = hospital.hospital_id WHERE doctor.license_number = "' . $doctorName . '"';
		$result = mysqli_query($connection, $query); //run the query
    		if (!$result) { //incase of fail
         		die("database query failed.");
     		}
	?>
	<ol>
	<?php
    		while ($row = mysqli_fetch_assoc($result)) { //print the names out to the screen
        		echo 'Name: ' . $row["first_name"] . ' ' . $row["last_name"]; //prints the name
			echo "<br>"; 
			echo 'License: ' . $row["license_number"]; //prints the license number
			echo "<br>";
			echo 'Specialty: ' . $row["specialty"]; //prints specialty
			echo "<br>";
			echo 'Date Licensed: ' . $row["date_licensed"]; //prints date licensed
			echo "<br>";
			echo 'Works at: ' . $row["works_at"]; //prints the hospital the doctor works at
     		}
     		mysqli_free_result($result);
	?>
	</ol>
	<?php
   		mysqli_close($connection); //close the connection
	?>
	</body>
</html>
