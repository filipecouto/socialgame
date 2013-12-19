<?php

require_once('DAL.php');

//Insert User
    function insertUser($Username,$Password,$Email){
        $sqlUser = "INSERT INTO Users (Username) VALUES('$Username')";
		executeQuery($sqlUser);
		$userId = mysql_insert_id();
		$sqlLogin = "INSERT INTO Logins (UserId,Password,Email) VALUES('$userId','$Password','$Email')";
		executeQuery($sqlLogin);
    }
	
	//Change User Name
	function changeUserName($UserId,$Username){
		$sql = "UPDATE Users SET Username = '$Username' WHERE Id = '$UserId'";
		executeQuery($sql);
	}
	
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

	
	function deleteUser($userId)
	{
		$sql = "DELETE FROM Users WHERE id = ?$userId'";
		executeQuery($sql);
	}
?>