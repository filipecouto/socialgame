<?php
	require_once('DAL/Users.php');
	require_once('DAL/Sessions.php');
	
	function createUser($userName, $password, $email){
		$encriptedPassword = sha1($password);
		$state = insertUser($userName, $encriptedPassword, $email);
		if($state != "True"){
			return $state; 
		}
		else{
			$userId = getUserIdByEmail($email);
			if($userId !=-1)
			{
				$token = token();
				insertSession($userId,$token);
				return true;
			}else{
				return false;
			}
		}
	}
	
	function modifyUserName($token,$Username){
		$userId = getUserBySession($token);
		if($userId !=-1)
		{
			changeUserName($userId,$Username);
			return true;
		}else{
			return false;
		}
	}

	function modifyUserPassword($token,$oldpassword,$newpassword){
		$userId = getUserBySession($token);
		if($userId != -1)
		{
			$encriptedOldPassword = sha1($oldpassword);
			if($encriptedOldPassword == getUserPassword($userId)){
				$encriptedPassword = sha1($newpassword);
				changeUserPassword($userId,$encriptedPassword);
				return true;
			}
			else{
				return false;
			}
		}else{
			return false;
		}
	}
	
	//Token = -1 -> token doesn't exist -> create session
	//Token = -2 -> user doesn't exist
	function doLogin($Email,$Password){
		$token = login($Email,$Password);
		if($token == -1){
			$userId = getUserIdByEmail($Email);
			$newToken = token();
			insertSession($userId, $newToken);
			//$session = getSession($newToken);
			return $newToken;
		}elseif ($token != -2 && $token != -1) {
			return $token;
		}
		/*}else{
			if($token == -2){
				$session = false;
			}else{
				$session = getSession($newToken);
			}
		}*/
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

	function findUserNameByEmail($email){
		$user = getUserNameByEmail($email);
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
	
	function createUserTag($UserId,$TagName,$TypeId){
		insertUserTag($UserId,$TagName,$TypeId);
	}
	
	function modifyUserMood($UserId,$MoodId){
		changeUserMood($UserId,$MoodId);
	}

	//Returns if the user has a specified type
	function isUserAuthorized($token,$Type){
		$userId = getUserBySession($token);
		$userType = getUserType($userId);
		if($userType != false && $userType == $Type){
			return true;
		}
		else{
			return false;
		}
	}

	function isTokenValid($token){
		return isToken($token);
	}

	//Returns the user information using its session token
	function returnUser($token){
		$userId = getUserBySession($token);
		return returnUserById($userId);
	}

	//Returns the user information using its id
	function returnUserById($userId){
		return getUser($userId);
	}

	//Returns information of users with the sent username
	function returnUsers($username){
		return getUsersByName($username);
	}

	//Return the users friends
	function returnUsersFriends($token){
		$userId = getUserBySession($token);

	}
?>