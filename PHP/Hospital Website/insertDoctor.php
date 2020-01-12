<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>Insert Doctor</title>
	</head>
	<body>
	<?php
		include 'connectdb.php';
	?>
	<h1>Trying to inserted the doctor into the database!</h1>
	<?php
		if ($_POST["license_number"] != "") { //if there is a license number
			//get all the doctor information given in from input
   			$license_number = $_POST["license_number"];
			$first_name = $_POST["first_name"];
			$last_name = $_POST["last_name"];
			$specialty = $_POST["specialty"];
			$date_licensed = $_POST["date_licensed"];	
			$works_at = $_POST["works_at"];
			//create a query below to insert the given doctor into the doctor table
			$query = 'INSERT INTO doctor (license_number, first_name, last_name, specialty, date_licensed, works_at) VALUES("' . $license_number . '", "' . $first_name . '", "' . $last_name . '", "' . $specialty . '", "' . $date_licensed . '", "' . $works_at . '")';
			$result = mysqli_query($connection, $query);
    			if (!$result) { //incase the query fails
         			die("Error! Please enter a unique license.");
     			}
    			echo 'Your doctor was added successfully!';
			mysqli_close($connection);
		}
		else {
			echo 'Error! The license number cannot be empty.'; //the license is empty causes an error
		}
	?>
	</body>
</html>
