<?php
require_once('../DAL/DAL.php');

	//Add new Connection
	function addConnection($UserId1, $UserId2){
		$dal = new DAL();
		$sql = "INSERT INTO Connections (user1,user2,state) VALUES('$UserId1','$UserId2',0)";
		print_r($sql);
		$dal->executeQuery($sql);
	}
	
	//Add a relation between a connection and a minigame
	function addConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		$dal = new DAL();
		$sql = "INSERT INTO ConnectionMinigames (ConnectionId,MinigameId,Difficulty,Score) VALUES('$ConnectionId',$MinigameId','$Difficulty','$Score')";
		$dal->executeQuery($sql);
	}
	
	//Update a Connection Minigame relation
	//Be sure to call this first with the previous score being negative
	function updateConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		$dal = new DAL();
		$sql = "UPDATE ConnectionMinigames SET Difficulty = '$Difficulty' AND Score = '$Score' WHERE ConnectionId = '$ConnectionId' AND MinigameId = '$MinigameId'";
		$dal->executeQuery($sql);
		$sql = "UPDATE Connections SET TotalScore = TotalScore + '$Score' WHERE Id = '$ConnectionId'";
		$dal->executeQuery($sql);

		$sqlFind = "SELECT User1 FROM Connections WHERE Id = '$ConnectionId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$record = mysql_fetch_array($recordset);
		$firstUserId = $record["User1"];

		$sql = "UPDATE Users SET TotalScore = TotalScore + '$Score' WHERE Id = '$firstUserId'";
		$dal->executeQuery($sql);
	}	
	
	//Update a Connection Strength
	//Be sure to call this first with the previous strength being negative
	function updateConnectionStrength($Id,$Strength){
		$dal = new DAL();
		$sql = "UPDATE Connections SET Strength = '$Strength' WHERE Id = '$Id'";
		$dal->executeQuery($sql);

		$sqlFind = "SELECT User1 FROM Connections WHERE Id = '$ConnectionId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$record = mysql_fetch_array($recordset);
		$firstUserId = $record["User1"];

		$sql = "UPDATE Users SET TotalStrength = TotalStrength + '$Strength' WHERE Id = '$firstUserId'";
		$dal->executeQuery($sql);
	}

	//Change Connection State
	function changeConnectionState($Id,$State){
		$dal = new DAL();
		$sql = "UPDATE Connections SET State = '$State' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Get a ConnectionID using the 2 User Id's
	//returns its ID or -1 if error
	function getConnectionIdByUsers($User1,$User2){
		$dal = new DAL();
		$sqlFind = "SELECT Id FROM Connections WHERE (User1 = '$User1' AND User2 = '$User2') OR (User1 = '$User2' AND User2 = '$User1')";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$connectionId = $record["Id"];
		}
		else{
			$connectionId = -1;
		}
		return $connectionId;
	}
?>
	