<!DOCTYPE html> 
<html> 
	<head> 
		<meta charset="utf-8"> 
		<title>Patient Information</title> 
	</head> 
	<body>
	<h2>Specified Patient Information:</h2> 
	<?php
		include 'connectdb.php'; //get the connection file to connect to db
   		$patient_id = $_POST["patient_id"]; //get the id of the patient from input
		$query1 = 'SELECT * FROM patient WHERE ohip_number = "' . $patient_id . '"'; //query gets all the patients
   		$result1 = mysqli_query($connection, $query1); //run the query
   		if (mysqli_num_rows($result1) == 0){ //check for errors
     			echo 'The OHIP number you have entered does not exist!'; //tell the user that ohip number doesnt exist
   		}
		else {
				//the query below gets the name of the patient and name of doctor
     			$query2 = 'SELECT patient.first_name AS pfn, patient.last_name AS pln, doctor.first_name AS dfn, doctor.last_name AS dln FROM patient, doctor, patients_assigned_to_doctor WHERE patients_assigned_to_doctor.patient_id = patient.ohip_number AND patients_assigned_to_doctor.doctor_id = doctor.license_number AND patient.ohip_number = "' . $patient_id . '"';
    			$result2 = mysqli_query($connection, $query2); //run the query
 	                if (mysqli_num_rows($result2) == 0){ //check if any results
        	        	echo 'This patient is not being treated by anyone!'; //prompt the user that there are no results for the input
			}

    			if (!$result2) {
        	 		die("Error! database query failed"); //incase the query fails
			}
    			while ($row = mysqli_fetch_assoc($result2)) { //print the names of the doctor and patient
        			echo '<li>';
        			echo 'Patient Name: ' . $row["pfn"] . ' ' . $row["pln"] . ', Doctor Name: ' . $row["dfn"] . ' ' . $row["dln"] . '<br>';
     			}
     		}
	?> 
	<?php 
		mysqli_close($connection); //close the db connenction 
	?> 
	</body> 
</html>
