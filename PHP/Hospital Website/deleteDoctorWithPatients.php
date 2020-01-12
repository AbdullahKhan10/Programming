<!DOCTYPE html> 
<html> 
	<head> 
		<meta charset="utf-8"> 
		<title>CS3319 Assignment3</title> 
	</head> 
	<body>  
	<h1>Confirmed delete on Doctor with patients</h1> 
	<?php
		include 'connectdb.php'; //connect to the db library
		$license = $_POST["license"]; //get the license
     		$query = 'DELETE FROM doctor WHERE license_number = "' . $license . '"'; //this deletes the doctor with given license number this cascades the associations table
     		if (!mysqli_query($connection, $query)) { //incase of 
         		die('Error: Cannot delete a head doctor of a hospital.');
      		}
      		echo 'Doctor with patients was successfully deleted!'; //tell the user the delete happened successfully
   		mysqli_close($connection); 
	?> 
	</body>
</html>
