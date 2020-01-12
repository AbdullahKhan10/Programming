<!--This is the main file which calls on all the other files as helpers which has all the inputs and buttons in it-->
<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>cs3319 Assignment #3</title>
	</head>
	<body>
		<?php
			include 'connectdb.php'; //include the connection db file for all the code below
		?>
		<!--This is the first requirement which gets all the input for the listDoctors.php file and then that file lists all doctors-->
		<h2>List all the doctors according to specified ordering:</h2>
		<form action = "listDoctors.php" method = "post">
		Select which field you want the list to be sorted by: 
		<input type = "radio" name = "doctorName" value = "fName" required> First Name
		<input type = "radio" name = "doctorName" value = "lName" required> Last Name
		<br>
		Select how you want the list to be sorted:
		<input type = "radio" name = "listOrder" value = "ascending" required> Ascending
		<input type = "radio" name = "listOrder" value = "descending" required> Descending
		<br>
		<input type = "submit" value = "Submit">
		</form>
		<p>
		<hr>
		<p>
		<!--This gets the date of for the listDoctorsByDate.php file to use and query the table and print out all the doctors after a particular date-->
		<h2>List all the doctors who were licensed before a specified date:</h2>
		<form action = "listDoctorsByDate.php" method = "post">
		Please enter the date: 
		<input type = "date" name = "doctorDate" required>
		<br>
		<input type = "submit" value = "Submit">
		</form>
		<p>
		<hr>
		<p>
		<!--This inserts a new doctor into the table and gets all the doctor information from the user to put into the insertDoctor.php file-->
		<h2>Insert a new doctor to the database:</h2>
		<form action = "insertDoctor.php" method = "post">
		Enter doctor license number:
		<input type = "text" name = "license_number" required><br>
		Enter doctor first name: 
		<input type = "text" name = "first_name"> <br>
		Enter doctor last name:
		<input type = "text" name = "last_name"> <br>
		Enter doctor specialty:
		<input type = "text" name = "specialty"><br>
		Enter doctor date licensed:
		<input type = "date" name = "date_licensed" required><br>
		Select a hospital:<br>
                <?php	//this php code allows the usage of radio buttons to get the hospitals as names so the user is forced to pick an hopital
                        $query = 'SELECT hospital_id, name FROM hospital'; //query from the hospital table
                        $result = mysqli_query($connection, $query); //run the query
                        if (!$result) {
                                die("databases query failed."); //notify the user if error exists
                        }
                        while ($row = mysqli_fetch_assoc($result)) { //print all the buttons and set the input 
                                echo '<input type = "radio" name = "works_at" value = "' . $row["hospital_id"] . '" required>';
                                echo $row["hospital_id"] . ', ' . $row["name"] . '<br>';
                        }
                        mysqli_free_result($result);
                ?>
		<input type = "submit" name = "Submit"><br>
		</form>
		<p>
                <hr>
                <p>
		<!--This gets all the radio buttons to get all the doctors as inputs and then gives the option to delete them so that deleteDoctorIfNoPatients.php can delete the doctor-->
		<h2>Delete a doctor from the database:</h2>
		<form action = "deleteDoctorIfNoPatients.php" method = "post">
		<?php
                        $query = 'SELECT * FROM doctor'; //get all the doctors
                        $result = mysqli_query($connection, $query); //run the query
                        if (!$result) { //return an error if query fails
                                die("databases query failed.");
                        }
                        while ($row = mysqli_fetch_assoc($result)) { //prints all the radio buttons
                                echo '<input type = "radio" name = "license" value = "' . $row["license_number"] . '" required>';
                                echo $row["license_number"] . ', ' . $row["first_name"] . ', ' . $row["last_name"] . ', ' . $row["specialty"] . '<br>';
                        }
                        mysqli_free_result($result);
                ?>
		<input type = "submit" value = "Click to Delete Doctor">
		</form>
                <p>
                <hr>
                <p>
		<!--This updates a hospital name where all the hospitals are printed as radio button and be selected and a text input where you can tell the updateHospitalName.php file what to change the name to-->
		<h2>Update hospital's name in the database:</h2>
		<form action = "updateHospitalName.php" method = "post">
                Select a hospital and enter the new name of selected hospital:
                <input type = "text" name = "newName" required>
                <input type = "submit" value = "Update">
		<br>
		<?php
                       	$query = 'SELECT * FROM hospital'; //query to get all the hospitals in the db
                      	$result = mysqli_query($connection, $query); //run the query 
                        if (!$result) { //check if the query runs fine
                               	die("databases query failed.");
                       	}
                       	while ($row = mysqli_fetch_assoc($result)) { //print all the hospitals as radio buttons
                               	echo '<input type = "radio" name = "hospital_id" value = "' . $row["hospital_id"] . '" required>';
                               	echo $row["hospital_id"] . ', ' . $row["name"] . '<br>';
                       	}
                       	mysqli_free_result($result);
		 ?>
		</form>
                <p>
                <hr>
                <p>
		<!--This portion simply prints out all of the hospitals the name of the doctors who are heads of that hospital-->
		<h2>List all the hospital names and the first name and last name of the head doctor of each hospital and the doctor's start date as head, in alphabetical order by hospital name:</h2>
		<ol>
		<?php
        		$query = 'SELECT * FROM hospital, doctor WHERE doctor.license_number = hospital.head_doctor ORDER BY name'; //query the databases to get all the names
        		$result = mysqli_query($connection,$query); //run the query
        		if (!$result) { //check for errors 
                		die("databases query failed.");
        		}
        		while ($row = mysqli_fetch_assoc($result)) { //print all the information as an ordered list
                		echo '<li>';
				echo 'Hospital Name: ' . $row["name"] . ', Head Doctor: ' . $row["first_name"] . ' ' . $row["last_name"] . ', Start Date: ' . $row["head_doctor_start_date"] . '<br>';
        		}
 	 	      	mysqli_free_result($result);
		?>
		</ol>
                <p>
                <hr>
                <p>
		<!--This gets an input of which patient OHIP the user wants to query and get all their doctor assication and this takes the input to getPatientInformation.php file to print out the list-->
		<h2>Select a patient (by entering the OHIP number) and then output all that patient's first and last name and the doctors (first and last name) who treat that patient:</h2>
		<form action = "getPatientInformation.php" method = "post"> 
		Please enter the patient's OHIP number: 
		<input type = "text" name = "patient_id" required> 
		<input type = "submit" value = "Submit">
		</form>
                <p>
                <hr>
                <p>
		<!--This creates and removes assocations between doctors and patienets and takes input on which patient and which doctor the user wants either assign or unassign to and these inputs go to the assignorUnassignPatient.php file-->
		<h2>Either assign a doctor to treat a patient or stop a doctor from treating a patient:</h2>
		<form action = "assignOrUnassignPatient.php" method="post"> 
	        	Please enter a valid doctor license number:
                        <input type = "text" name = "license_number" required> 
			<br>
                        Select whether you want to assign or unassign that doctor to a patient below:
                        <input type = "radio" name = "status" value = "assign" required> Assign
                        <input type = "radio" name = "status" value = "remove" required> Unassign
                        <br>
			<?php
				//this forces the user to pick from an existing patient
				$query = "SELECT * FROM patient"; //create a query which finds all the patients
   				$result = mysqli_query($connection,$query);
   				if (!$result) { //check if the query works fine
        				die("databases query failed.");
    				}
   				while ($row = mysqli_fetch_assoc($result)) { //prints all the patients as radio buttons and allows the user to choose 
        				echo '<input type = "radio" name = "ohip" value = "' . $row["ohip_number"] . '" required>';
        				echo $row["first_name"] . ' ' . $row["last_name"] . '<br>';
				}
				mysqli_free_result($result);
			?>
			<input type = "submit" value = "Submit">
		</form>
		<p>
                <hr>
                <p>
		<!--This portion simply queries the table to find all the doctors who have no patient assocations-->
		<h2>Lists of any doctor who has no patients:</h2>
		<?php
			$query = 'SELECT first_name, last_name FROM doctor WHERE doctor.license_number NOT IN (SELECT DISTINCT doctor_id FROM patients_assigned_to_doctor)'; //query the table to find all the doctors who have no patients
                        $result = mysqli_query($connection, $query); //run the query
                        if (!$result) { //checks if the query works fine
                                die("databases query failed.");
                        }
                        while ($row = mysqli_fetch_assoc($result)) { //print the doctors as a list
                        	echo $row["first_name"] . ' ' . $row["last_name"] . '<br>';
                        }
                        mysqli_free_result($result);
		?>
	</body> 
</html>
