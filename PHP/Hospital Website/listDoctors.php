<!DOCTYPE html>
<html>
	<head>
		<meta charset = "utf-8">
		<title>List of all the doctors</title>
	</head>
	<body>
	<h1>Here are your doctors in your specified order:</h1>
	<?php
		include 'connectdb.php'; //get the db connection file
   		$nameO  = $_POST["doctorName"]; //variable for whether you want fname or lname as ordering
		$listO  = $_POST["listOrder"]; //variable for whether you want asc or des
		
		if ($nameO == "" || $listO == "") { //if  these fields are left empty print a error message
			echo 'Error! Please make sure you checked both criteria for sorting.';
		}
		else {		//otherwise it should be good
				//check all the conditions for that specified query
			if ($nameO == "fName" && $listO == "ascending") {
   				$query = 'SELECT * FROM doctor ORDER BY first_name ASC';
			}
			if ($nameO == "fName" && $listO == "descending") {
				$query = 'SELECT * FROM doctor ORDER BY first_name DESC';
			}
			if ($nameO == "lName" && $listO == "ascending") {
				$query = 'SELECT * FROM doctor ORDER BY last_name ASC';
			}
			if ($nameO == "lName" && $listO == "descending") {
				$query = 'SELECT * FROM doctor ORDER BY last_name DESC';
			}
   		
			$result = mysqli_query($connection, $query);
    			if (!$result) {//run the query and check if it failed
         			die("database query failed.");
     			}
		}
	?>
	<form action = "getDoctorInformation.php" method = "post">
		<?php
			if ($nameO != "" || $listO != "") { //this gets the doctors information after you query all the doctors
                		while ($row = mysqli_fetch_assoc($result)) { //check the results
               				echo '<input type = "radio" name = "doctorName" value = "';
                               		echo $row["license_number"] . '" required>'; //print all the doctors as radio button
                                	echo $row["first_name"] . ' ' . $row["last_name"] . '<br>';
                        	}
                        	mysqli_close($connection);
				echo '<input type = "submit" value = "Submit">'; //submit at the end
                	}
		?>
	</form>
	</body>
</html>
