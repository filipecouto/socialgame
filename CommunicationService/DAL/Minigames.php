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
	
	// Returns the ID of the minigame, given its internal name (ex: "crosswebenterprise.maze")
	function getMinigameId($internalName) {
		$dal = new DAL();
		$sql = sprintf("SELECT id FROM Minigames WHERE name='%s'", mysql_real_escape_string($internalName));
		
		$resultSet = $dal->executeNonQuery($sql);
		
		if($row = mysql_fetch_array($resultSet)) {
			$result = $row[0];
		} else {
			$result = -1;
		}
		
		mysql_free_result($resultSet);
		
		return $result;
	}
	
	function getPendingMinigamesByUser($userId) {
		$dal = new DAL();
		$sql = sprintf("SELECT cm.connectionID connectionId, cm.minigameID gameId, m.name gameName, cm.difficulty level FROM ConnectionMinigames cm, Connections c, Minigames m WHERE m.id=cm.minigameID AND c.id=cm.connectionID AND cm.score=-1 AND c.user1=%d", mysql_real_escape_string($userId));
		
		return $dal->executeNonQuery($sql);
	}
	
	function setMinigameScoreForChallenge($userId, $connectionId, $minigameId, $score) {
		$dal = new DAL();
		$sql = sprintf("UPDATE ConnectionMinigames SET score=%d WHERE connectionID=%d AND minigameID=%d",
					   mysql_real_escape_string($score),
					   mysql_real_escape_string($connectionId),
					   mysql_real_escape_string($minigameId)):
		
		return $dal->executeQuery($sql);
	}
?>