<?php
	require_once('DAL/Users.php');
	require_once('DAL/Session.php');
	
	function createUser($userName, $password, $email){
		$encriptedPassword = sha256($password);
		insertUser($userName, $encriptedPassword, $email);
		$userId =getUserIdByEmail($email);
		if($userId !=-1)
		{
			$token = token();
			insertSession($userId,$token);
			return true;
		}else{
			return false;
		}
	}
	
	function modifyUserName($token,$Username){
		$userId = getUserBySession($token);
		if($userId !=-1)
		{
			changeUserName($UserId,$Username);
			return true;
		}else{
			return false;
		}
	}

	function modifyUserPassword($token,$password){
		$userId = getUserBySession($token);
		if($userId !=-1)
		{
			$encriptedPassword = sha256($password);
			changeUserPassword($UserId,$encriptedPassword);
			return true;
		}else{
			return false;
		}
	}
	
	//Token = -1 -> token doesn't exist -> create session
	//Token =-2 -> user doesn't exist
	function login($Email,$Password){
		$token = login($Email,$Password);
		if($token == -1){
			$userId = getUserIdByEmail($Email);
			$newToken = token();
			insertSession($userId, $newToken);
			$session = getSession($newToken);
		}else{
			if($token == -2){
				$session = false;
			}else{
				$session = getSession($newToken);
			}
		}
	}
		
	function findUserIdByEmail($email){
		$user = getUserIdByEmail($email);
		if($user!=-1)
		{
				return $user;
		}else{
			return false;
		}
	}
	
	function removeUser($userId){
		deleteUser($userId);
	}
	
	function createUserTag($UserId,$TagId){
		insertUserTag($UserId,$TagName,$TypeId);
	}
	
	function modifyUserMood($UserId,$MoodId){
		changeUserMood($UserId,$MoodId);
	}
?>