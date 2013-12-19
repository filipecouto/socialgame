<?php
require_once('DAL.php');

//Insert new Mood
	function insertMood($Description){
		$dal = new DAL();
		$sql = "INSERT INTO Mood (Description) VALUES('$Description')";
		$dal->executeQuery($sql);
	}
	
	//Update Mood
	function updateMood($Id,$Description){
		$dal = new DAL();
		$sql = "UPDATE Mood SET Description = '$Description' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Delete Mood
	function deleteMood($moodId){
		$dal = new DAL();
		$sql = "DELETE FROM Mood WHERE id = '$moodId'");
		$dal->executeQuery($sql);
	}
	?>