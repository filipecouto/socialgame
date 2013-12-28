<?php

require_once('DAL/DAL.php');

	
		//Insert new Minigame
	function insertMinigame($Name){
		$dal = new DAL();
		$sql = "INSERT INTO Minigames (Name) VALUES('$Name')";
		$dal->executeQuery($sql);
	}
	
	//Update Minigame
	function updateMinigame($Id,$Name){
		$dal = new DAL();
		$sql = "UPDATE Minigames SET Name = '$Name' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Get Existing Minigames
	function getMinigames(){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Minigames";
		$recordset = $dal->executeNonQuery($sqlFind);
		return $recordset;
	}
	
	//Delete minigames
	function deleteMinigames($minigameId){
		$dal = new DAL();
		$sql = "DELETE FROM Minigames WHERE id = '$minigameId'";
		$dal->executeQuery($sql);
	}
?>