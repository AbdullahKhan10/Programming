<!DOCTYPE html> 
<html> 
	<head> 
		<meta charset="utf-8"> 
		<title>Deleting Doctor</title> 
	</head> 
	<body>
	
	<h2>Deleting doctor from the database!</h2> 
	<?php
		if ($_POST["license"] != "") {
			include 'connectdb.php'; //include the connection lib
			$license = $_POST["license"]; //get the license of the license of the doctor
			$query1 = 'SELECT * FROM doctor, patients_assigned_to_doctor WHERE doctor.license_number = patients_assigned_to_doctor.doctor_id AND doctor.license_number = "' . $license . '"'; //checks if any doctors who have patient assocations
  			$result1 = mysqli_query($connection, $query1);
               		if(!$result1) { //incase of error with query
    	        		die("database query failed.");
               		}
			if (mysqli_num_rows($result1) == 0) { //checks if query returns 0 rows
      				$query2 = 'DELETE FROM doctor WHERE license_number = "' . $license . '"'; //if so, then make a delete query
				$result2 = mysqli_query($connection, $query2); //run the query
      				if(!$result2) { //checks for errors in running query
					die("database query failed.");
      				}
				echo 'Doctor has no patients and was successfully deleted!' . '<br>'; //prompt the user for successful delete
				mysqli_close($connection); //close the connection
    			}
		}
		else {
			echo 'Error! No doctor selected.'; //in case no doctor was selected
		}
	?> 
	<form action = "deleteDoctorWithPatients.php" method = "post">
		<?php 
			if ($_POST["license"] != "" && mysqli_num_rows($result1) != 0) { //if the rows is greater than one by the first query 
				echo 'This doctor has patients! If you delete this doctor, all the patient assignments will be deleted as well.' . '<br>'; //prompt the user
				echo 'Please confirm if you would like to delete doctor with license: '; //prompt the user to confirm
				echo '<input type = "text" name = license value = "' . $license . '"' . '<br>'; //sets the text input to license
				echo '<input type = "submit" value = "Delete Doctor">'; //submit button
			}
		?> 
	</form> 
</body> 
</html>
