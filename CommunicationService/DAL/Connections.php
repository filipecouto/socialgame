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
		$sql = "INSERT INTO ConnectionMinigames (connectionID,minigameID,`difficulty`,`score`) VALUES('$ConnectionId','$MinigameId','$Difficulty','$Score')";
		$dal->executeQuery($sql);
	}
	
	//Update a Connection Minigame relation
	//Be sure to call this first with the previous score being negative
	function updateConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		$dal = new DAL();
		$sql = "UPDATE ConnectionMinigames SET difficulty = '$Difficulty' AND score = '$Score' WHERE ConnectionId = '$ConnectionId' AND MinigameId = '$MinigameId'";
		$dal->executeQuery($sql);
		$sql = "UPDATE Connections SET totalScore = totalScore + '$Score' WHERE id = '$ConnectionId'";
		$dal->executeQuery($sql);

		$sqlFind = "SELECT user1 FROM Connections WHERE id = '$ConnectionId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$record = mysql_fetch_array($recordset);
		$firstUserId = $record["user1"];

		$sql = "UPDATE Users SET totalScore = totalScore + '$Score' WHERE id = '$firstUserId'";
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
		$sqlFind = "SELECT id FROM Connections WHERE (user1 = '$User1' AND user2 = '$User2') OR (user1 = '$User2' AND user2 = '$User1')";
		print_r($sqlFind);
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$connectionId = $record["id"];
		}
		else{
			$connectionId = -1;
		}
		return $connectionId;
	}
?>
	