<?php

require_once('../DAL/DAL.php');
require_once('../DAL/Tags.php');

//Insert User
    function insertUser($Username,$Password,$Email){
		$dal = new DAL();
        $sqlUser = "INSERT INTO Users (Username) VALUES('$Username')";
		$dal->executeQuery($sqlUser);
		$userId = getUserId($Username);
		$sqlLogin = "INSERT INTO Logins (UserId,Password,Email) VALUES('$userId','$Password','$Email')";
		$dal->executeQuery($sqlLogin);
    }
	
	//Change User Name
	function changeUserName($UserId,$Username){
		$dal = new DAL();
		$sql = "UPDATE Users SET username = '$Username' WHERE id = '$UserId'";
		print_r($sql);
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
		if($userId != -1){
			$sqlFind = "SELECT token FROM Session WHERE userId = '$userId'";
			$recordset = $dal->executeNonQuery($sqlFind);
			$length = mysql_num_rows($recordset);
			if($length != 0){
				$record = mysql_fetch_array($recordset);
				$token = $record["token"];
			}
			else{
				$token = -1;
			}
		}else
		{
			$token = -2;
		}
		
		return $token;
	}
	
	//Get a UserId using its email
	//returns its ID or -1 if error
	function getUserIdByEmail($Email){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Logins WHERE Email = '$Email'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$user = $record["userID"];
		}
		else{
			$user = -1;
		}
		return $user;
	}

	function getUserId($Username){
		$dal = new DAL();
		$sqlFind = "SELECT id FROM Users WHERE username = '$Username'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$user = $record["id"];
		}
		else{
			$user = -1;
		}
		return $user;
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
		$sql = "UPDATE Logins SET password = '$Password' WHERE userID = '$UserId'";
		print_r($sql);
		$dal->executeQuery($sql);
	}
	
	//Change User Mood
	function changeUserMood($UserId,$MoodId){
		$dal = new DAL();
		$sql = "UPDATE Users SET MoodId = '$MoodId' WHERE Id = '$UserId'";
		$dal->executeQuery($sql);
	}
	
?>