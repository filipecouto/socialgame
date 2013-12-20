<?php

require_once('DAL.php');
require_once('DALTag.php');

//Insert User
    function insertUser($Username,$Password,$Email){
		$dal = new DAL();
        $sqlUser = "INSERT INTO Users (Username) VALUES('$Username')";
		$dal->executeQuery($sqlUser);
		$userId = mysql_insert_id();
		$sqlLogin = "INSERT INTO Logins (UserId,Password,Email) VALUES('$userId','$Password','$Email')";
		$dal->executeQuery($sqlLogin);
    }
	
	//Change User Name
	function changeUserName($UserId,$Username){
		$dal = new DAL();
		$sql = "UPDATE Users SET Username = '$Username' WHERE Id = '$UserId'";
		$dal->executeQuery($sql);
	}
	
	//Login a user
	//returns its ID or -1 if error
	function login($Email,$Password){
		$dal = new DAL();
		$sqlFind = "SELECT UserId FROM Logins WHERE Email = '$Email' AND Password = '$Password'";
		$recordset = $dal->executeNonQuery($sqlFind);
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
		$dal = new DAL();
		$sqlFind = "SELECT UserId FROM Logins WHERE Email = '$Email'";
		$recordset = $dal->executeNonQuery($sqlFind);
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

	function deleteUser($userId){
		$dal = new DAL();
		$sql = "DELETE FROM Users WHERE id = ?$userId'";
		$dal->executeQuery($sql);
	}
	
	//Insert new relation user and tag with TagId
    function addUserTag($UserId,$TagId){
		$dal = new DAL();
        $sql = "INSERT INTO UserTag (UserId,TagId) VALUES('$UserId','$TagId')";
		$dal->executeQuery($sql);
    }
	
	//Insert new relation user and tag, with TagName
	function insertUserTag($UserId,$TagName,$TypeId){
		$dal = new DAL();
		$sqlFind = "Select Id From Tags Where Name = '$TagName'";
		$recordset = $dal->executeNonQuery($sqlFind);
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
	
	//Change User Password
	function changeUserPassword($UserId,$Password){
		$dal = new DAL();
		$sql = "UPDATE Logins SET Password = '$Password' WHERE UserId = '$UserId'";
		$dal->executeQuery($sql);
	}
	
	//Change User Mood
	function changeUserMood($UserId,$MoodId){
		$dal = new DAL();
		$sql = "UPDATE Users SET MoodId = '$MoodId' WHERE Id = '$UserId'";
		$dal->executeQuery($sql);
	}
	
?>