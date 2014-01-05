<?php

require_once('DAL/DAL.php');
require_once('DAL/Tags.php');
require_once('DAL/Sessions.php');
//Insert User
    function insertUser($Username,$Password,$Email){
    	//If there's no one with this email then proceede
    	if(getUserIdByEmail($Email) == -1) {
    		try{
				$dal = new DAL();
		        $sqlUser = "INSERT INTO Users (Username, `type`) VALUES('$Username',1)";
				$dal->executeQuery($sqlUser);
				$userId = getUserId($Username);
				$sqlLogin = "INSERT INTO Logins (UserId,Password,Email) VALUES('$userId','$Password','$Email')";
				$dal->executeQuery($sqlLogin);
				return true;
    		} catch (Exception $e) {
				return $e;
    		}
    	}
    	else{
    		return "DuplicateEmail";
    	}
    }
	
	//Change User Name
	function changeUserName($token,$Username){
		$UserId = getUserBySession($token);
		$dal = new DAL();
		$sql = "UPDATE Users SET username = '$Username' WHERE id = '$UserId'";
		$dal->executeQuery($sql);
	}

	//Sets the user type to admin
	function administrator($token){
		$UserId = getUserBySession($token);
		$dal = new DAL();
		$sql = "UPDATE Users SET `type` = 100 WHERE id = '$UserId'";
		$dal->executeQuery($sql);
	}
	//Login a user
	//returns its ID or -1 if error
	function login($Email,$Password){
		$dal = new DAL();
		$encriptedPassword = sha1("$Password");
		$sqlFind = "SELECT UserId FROM Logins WHERE Email = '$Email' AND Password = '$encriptedPassword'";
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

	//Gets the user name using its email
	function getUserNameByEmail($Email){
		$id = getUserIdByEmail($Email);
		$dal = new DAL();
		$sqlFind = "SELECT username FROM Users WHERE id = '$id'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$user = $record["username"];
		}
		else{
			$user = -1;
		}
		return $user;
	}

	//Gets the user id using its username
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

	//Gets the user password using its id
	function getUserPassword($UserId){
		$dal = new DAL();
		$sqlFind = "SELECT password FROM Logins WHERE userID = '$UserId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$password = $record["password"];
		}
		else{
			$password = -1;
		}
		return $password;
	}

	//Gets the user type using its id
	function getUserType($UserId){
		$dal = new DAL();
		$sqlFind = "SELECT type FROM Users WHERE id = '$UserId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$type = $record["type"];
		}
		else{
			$type = false;
		}
		return $type;
	}

	//Deletes a user
	function deleteUser($userId){
		$dal = new DAL();
		$sql = "DELETE FROM Users WHERE id = '$userId'";
		$dal->executeQuery($sql);
	}
	
	//Insert new relation user and tag with TagId
    function addUserTag($UserId,$TagId){
		$dal = new DAL();
        $sql = "INSERT INTO UserTag (userID,tagID) VALUES('$UserId','$TagId')";
		$dal->executeQuery($sql);
    }
	
	//Insert new relation user and tag, with TagName
	function insertUserTag($UserId,$TagName,$TypeId){
		$dal = new DAL();
		$sqlFind = "Select id From Tags Where name = '$TagName'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$tagId = $record["id"];
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
		$dal->executeQuery($sql);
	}
	
	//Change User Mood
	function changeUserMood($UserId,$MoodId){
		$dal = new DAL();
		$sql = "UPDATE Users SET MoodId = '$MoodId' WHERE Id = '$UserId'";
		$dal->executeQuery($sql);
	}
	
	//Gets all the user information using its id
	function getUser($UserId){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Users WHERE id = '$UserId'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$user = $recordset;
		}
		else{
			$user = false;
		}
		return $user;
	}

	//Gets all the users information that have the given username
	function getUsersByName($Username){
		if($Username == '') return false;
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Users WHERE username LIKE '%$Username%' ORDER BY username";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$users = $recordset;
		}
		else{
			$users = false;
		}
		return $users;
	}
?>