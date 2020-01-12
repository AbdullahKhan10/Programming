<!--This file either assigns or unassigns doctors to their patients-->
<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>List of all the doctors</title> <!--Title-->
	</head>
	<body>
	<?php
		include 'connectdb.php'; //get the connection library
	?>
	<h1>Here are your doctors in your specified order:</h1>
	<?php
   		$license_number = $_POST["license_number"]; //get the selected doctor license number
		$status  = $_POST["status"]; //get whether the user wants to assign or unassign
		$ohip = $_POST["ohip"]; //get the ohip number of the patient
		if ($status == "assign") { //do this if the user picked assign
   			$query = 'INSERT INTO patients_assigned_to_doctor VALUES("' . $license_number . '", "' . $ohip . '")'; //query to insert the ohip number and license number into the association table
			$result = mysqli_query($connection, $query); //run the query
        	        if (!$result) { //incase of query error
                        	die("Error! Either you have entered an invalid license number or you have tried to assign an association that already exists.");
                	}
			echo 'Your doctor is now assigned to the specified patient!'; //the doctor was successfully assigned
		}
		else if ($status == "remove") { //do this if the user picked unassign
			$query = 'DELETE FROM patients_assigned_to_doctor WHERE patient_id  = "' . $ohip . '" AND doctor_id = "' . $license_number . '"'; //query to delete the assocation from the table
			$result = mysqli_query($connection, $query); //incase of errors
                	if (!$result) {
        	                die("database query failed.");
	                }
			echo 'Your doctor is now unassigned to the specified patient!'; //success message of deletion
		}
		else {
			echo 'Error'; //error message if nothing is entered
		}
		mysqli_close($connection); //close the connection
	?>
	</body> 
</html>
