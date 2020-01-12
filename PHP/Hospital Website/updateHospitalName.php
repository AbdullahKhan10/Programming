<!DOCTYPE html> 
<html> 
	<head> 
		<meta charset="utf-8"> 
		<title>Update Hospital Name</title> 
	</head> 
	<body> 
		<h1>Updating hospital's name in the database!</h1> 
		<?php
			include 'connectdb.php'; //get the db connection file
   			$hospital_id = $_POST["hospital_id"]; //get the hospital id of the one we want to change
   			$newName = $_POST["newName"]; //get the new name that we want it changed to
   			$query = 'UPDATE hospital SET name = "' . $newName . '" WHERE hospital_id = "' . $hospital_id . '"'; //query to update the name
   			if (!mysqli_query($connection, $query)) { //run the query
        			die(mysqli_error($connection)); //sends the error message if there are errors
    			}
   			echo "Hospital name was updated successfully!"; //prompts the user that the hospital was updated successfully
   			mysqli_close($connection); //close the connection
		?> 
	</body>
</html>
