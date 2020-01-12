<?php
//this files connects php code to the database
$dbhost = "localhost";
$dbuser= "root";
$dbpass = "cs3319";
$dbname = "250907213assign2db";
//set all the variables for the database connection
//then connect to the database
$connection = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
if (mysqli_connect_errno()) { //incase of error connecting to the database
     die("database connection failed :" .
     mysqli_connect_error() .
     "(" . mysqli_connect_errno() . ")"
         );
    }
?>
