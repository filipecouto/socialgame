<?php
class DAL{

	/*
	* DATABASE COMMUNICATION
	*/

    private $servername="localhost";
    private $dbname="SocialGame";
    
    function db_connect(){
        $conn=mysql_connect($this->servername, "root", "nao sei"); 
        if (!$conn)
        {
            die('Could not connect: ' . mysql_error());
        }
        return $conn;
    }
	
	function executeQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
        if (!mysql_query($SQL,$conn))
        {
            die('Could not execute query insert:' . mysql_error());
        } else {
            echo "<br>1 registo colocado<br>";
        }
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
	}
	
	function executeNonQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
		$recordset = mysql_query($SQL,$conn);
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
		return $recordset;
	}
    
	/*
	* INSERTS
	*/

	//Insert User
    function insertUser($Username,$Password,$Email){
        $sqlUser = "INSERT INTO Users (Username) VALUES('$Username')";
		executeQuery($sqlUser);
		$userId = mysql_insert_id();
		$sqlLogin = "INSERT INTO Logins (UserId,Password,Email) VALUES('$userId','$Password','$Email')";
		executeQuery($sqlLogin);
    }
	
	//Insert Tag
	function insertTag($Name,$TypeId){
		$sql = "INSERT INTO Tags (Name,Type) VALUES('$Name','$TypeId')";
		executeQuery($sql);
	}
    
	//Insert new relation user and tag with TagId
    function addUserTag($UserId,$TagId){
        $sql = "INSERT INTO UserTag (UserId,TagId) VALUES('$UserId','$TagId')";
		executeQuery($sql);
    }
	
	//Insert new relation user and tag, with TagName
	function insertUserTag($UserId,$TagName,$TypeId){
		$sqlFind = "Select Id From Tags Where Name = '$TagName'";
		$recordset = executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$tagId = $record["Id"];
		}
		else{
			insertTag($TagName,$TypeId);
			$tagId = mysql_insert_id();
		}
		addUserTag($UserId,$tagId);
	}
	
	//Insert new Mood
	function insertMood($Description){
		$sql = "INSERT INTO Mood (Description) VALUES('$Description')";
		executeQuery($sql);
	}
	
	//Insert new TagType
	function insertTagType($Description){
		$sql = "INSERT INTO TagTypes (Description) VALUES('$Description)";
		executeQuery($sql);
	}
	
	//Insert new Minigame
	function insertMinigame($Name){
		$sql = "INSERT INTO Minigames (Name) VALUES('$Name')";
		executeQuery($sql);
	}
	
	//Insert new Notification Type
	function insertNotificationType($Desctiption){
		$sql = "INSERT INTO NotificationTypes (Description) VALUES('$Description')";
		executeQuery($sql);
	}
	
	//Add new Connection
	function addConnection($UserId1, $UserdId2)[
		$sql = "INSERT INTO Connections (User1,User2,State) VALUES('$UserId1','$UserId2',0)";
		executeQuery($sql);
	}
	
	//Add Tag to a Connection with TagId
	function addTagConnection($ConnectionId, $TagId){
		$sql = "INSERT INTO TagConnection (ConnectionId,TagId) VALUES('$ConnectionId','$TagId')";
		executeQuery($sql);
	}

	//Insert new relation connection and tag, with TagName
	function insertTagConnection($ConnectionId,$TagName,$TypeId){
		$sqlFind = "SELECT Id FROM Tags WHERE Name = '$TagName'";
		$recordset = executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$tagId = $record["Id"];
		}
		else{
			insertTag($TagName,$TypeId);
			$tagId = mysql_insert_id();
		}
		addTagConnection($ConnectionId,$tagId);
	}
	
	//Add a relation between a connection and a minigame
	function addConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		$sql = "INSERT INTO ConnectionMinigames (ConnectionId,MinigameId,Difficulty,Score) VALUES('$ConnectionId',$MinigameId','$Difficulty','$Score')";
		executeQuery($sql);
	}
	
	//Create new Notification
	function createNotification($TypeId,$ToUserId,$ObjectId){
		$sql = "INSERT INTO Notifications (Type,To,Read,Object) VALUES('$TypeId','$ToUserId',0,'$ObjectId')";
		executeQuery($sql);
	}

	/*
	* UPDATES
	*/
	
	//Update Mood
	function updateMood($Id,$Description){
		$sql = "UPDATE Mood SET Description = '$Description' WHERE Id = '$Id'";
		executeQuery($sql);
	}
	
	//Change User Password
	function changeUserPassword($UserId,$Password){
		$sql = "UPDATE Logins SET Password = '$Password' WHERE UserId = '$UserId'";
		executeQuery($sql);
	}
	
	//Change User Mood
	function changeUserMood($UserId,$MoodId){
		$sql = "UPDATE Users SET MoodId = '$MoodId' WHERE Id = '$UserId'";
		executeQuery($sql);
	}

	//Change User Name
	function changeUserName($UserId,$Username){
		$sql = "UPDATE Users SET Username = '$Username' WHERE Id = '$UserId'";
		executeQuery($sql);
	}

	//Update Tag Type
	function updateTagType($Id,$Description){
		$sql = "UPDATE TagTypes SET Description = '$Description' WHERE Id = '$Id'";
		executeQuery($sql);
	}

	//Update Minigame
	function updateMinigame($Id,$Name){
		$sql = "UPDATE Minigames SET Name = '$Name' WHERE Id = '$Id'";
		executeQuery($sql);
	}

	//Update a Connection Minigame relation
	//Be sure to call this first with the previous score being negative
	function updateConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		$sql = "UPDATE ConnectionMinigames SET Difficulty = '$Difficulty' AND Score = '$Score' WHERE ConnectionId = '$ConnectionId' AND MinigameId = '$MinigameId'";
		executeQuery($sql);
		$sql = "UPDATE Connections SET TotalScore = TotalScore + '$Score' WHERE Id = '$ConnectionId'";
		executeQuery($sql);

		$sqlFind = "SELECT User1 FROM Connections WHERE Id = '$ConnectionId'";
		$recordset = executeNonQuery($sqlFind);
		$record = mysql_fetch_array($recordset);
		$firstUserId = $record["User1"];

		$sql = "UPDATE Users SET TotalScore = TotalScore + '$Score' WHERE Id = '$firstUserId'";
		executeQuery($sql);
	}	
	
	//Update a Connection Strength
	//Be sure to call this first with the previous strength being negative
	function updateConnectionStrength($Id,$Strength){
		$sql = "UPDATE Connections SET Strength = '$Strength' WHERE Id = '$Id'";
		executeQuery($sql);

		$sqlFind = "SELECT User1 FROM Connections WHERE Id = '$ConnectionId'";
		$recordset = executeNonQuery($sqlFind);
		$record = mysql_fetch_array($recordset);
		$firstUserId = $record["User1"];

		$sql = "UPDATE Users SET TotalStrength = TotalStrength + '$Strength' WHERE Id = '$firstUserId'";
	}

	//Change Connection State
	function changeConnectionState($Id,$State){
		$sql = "UPDATE Connections SET State = '$State' WHERE Id = '$Id'";
		executeQuery($sql);
	}

	//Update Notification Type
	function updateNotificationType($Id,$Description){
		$sql = "UPDATE NotificationTypes SET Description = '$Description' WHERE Id = '$Id'";
		executeQuery($sql);
	}

	//Change Notification Read Status
	function changeNotificationRead($Id){
		$sql = "UPDATE Notifications SET Read = 1 WHERE Id = '$Id'";
		executeQuery($sql);
	}

	/*
	* SELECTS
	*/

	//Login a user
	//returns its ID or -1 if error
	function login($Email,$Password){
		$sqlFind = "SELECT UserId FROM Logins WHERE Email = '$Email' AND Password = '$Password'";
		$recordset = executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$userId = $record["UserId"];
		}
		else{
			$userId = -1;
		}
		return $userId;
	}

	//Get a ConnectionID using the 2 User Id's
	//returns its ID or -1 if error
	function getConnectionIdByUsers($User1,$User2){
		$sqlFind = "SELECT Id FROM Connections WHERE (User1 = '$User1' AND User2 = '$User2') OR (User1 = '$User2' AND User2 = '$User1')";
		$recordset = executeNonQuery($sqlFind);
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

	//Get a UserId using its email
	//returns its ID or -1 if error
	function getUserIdByEmail($Email){
		$sqlFind = "SELECT UserId FROM Logins WHERE Email = '$Email'";
		$recordset = executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$userId = $record["UserId"];
		}
		else{
			$userId = -1;
		}
		return $userId;
	}

	//Get Users Notifications either Read (1) or To Be Read (0)
	function getNotificationsByUser($UserId,$ReadState){
		$sqlFind = "SELECT * FROM Notifications WHERE To = '$UserId' AND Read = '$ReadState'";
		$recordset = executeNonQuery($sqlFind);
		return $recordset;
	}

	//Get Existing Minigames
	function getMinigames(){
		$sqlFind = "SELECT * FROM Minigames";
		$recordset = executeNonQuery($sqlFind);
		return $recordset;
	}
}
?>
