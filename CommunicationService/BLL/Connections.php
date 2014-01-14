<?php
	require_once('DAL/Connections.php');
	require_once('DAL/Sessions.php');
	require_once('DAL/Tags.php');
	require_once('DAL/Notifications.php');
	require_once('DAL/Minigames.php');
	
	function addFriend($User1Token, $UserdId2, $Strength, $Tags){
		$UserId1 = getUserBySession($User1Token);
		if($UserId1 != -1)
		{
			$connId = addConnection($UserId1, $UserdId2, $Strength);
			if($connId != "False"){
				insertTagsConnection($connId, $Tags, 4);
			}
			else{
				return false;
			}
			//insert notification
			insertNotification(1,$UserdId2,$connId);
			return true;
		}else{
			return false;
		}
	}

	//Either accept or deny a friend request
	//$action will be 1 or -1
	//DEPRECATED please consider using the token-based methods
	function actionToFriend($notificationId,$action){
		try{
			//Accept or deny the request
			$connId = getConnectionIdByNotification($notificationId);
			changeConnectionState($connId,$action);
			//Notification was read
			changeNotificationRead($notificationId);
			return true;
		}catch(Exception $e){
			return false;
		}
	}
	
	// Accepts a friendship request
	function acceptFriendship($token, $connectionId){
		try {
			$userId = getUserBySession($token);
			
			changeConnectionStateByUser($connectionId, $userId, 1);
			
			return true;
		} catch(Exception $e) {
			return false;
		}
	}
	
	// Refuses a friendship request
	function refuseFriendship($token, $connectionId){
		try {
			$userId = getUserBySession($token);
			
			changeConnectionStateByUser($connectionId, $userId, -1);
			
			return true;
		} catch(Exception $e) {
			return false;
		}
	}
	
	function removeFriend($token, $otherUser) {
		$userId = getUserBySession($token);
		if($userID == -1) return false;
		
		return DAL_removeConnection($userId, $otherUser);
	}

	function returnConnectionState($User1Token, $UserId2){
		$UserId1 = getUserBySession($User1Token);
		if($UserId1 != -1)
		{
			$connId = getConnectionIdByUsers($UserId1, $UserId2);
			if($connId != -1){
				$state = getConnectionState($connId);
				if($state != "False"){
					return $state;
				}
			}
		}
		return false;
	}

	function returnUserConnectionsWithState($UserToken,$State){
		$UserId = getUserBySession($UserToken);
		if($UserId != -1)
		{
			$connections = getUserConnectionsWithState($UserId,$State);
			return $connections;
		}
		return false;
	}

	function returnUserConnectionsWithStateById($UserId,$State){
		$connections = getUserConnectionsWithState($UserId,$State);
		return $connections;
	}
	
	function returnConnection($ConnectionId){
		$connection = getConnection($ConnectionId);
		return $connection;
	}
	
	function acceptFriendshipWithChallenge($token, $connectionId, $minigame, $level) {
		try {
			$userId = getUserBySession($token);
			
			$minigame = getMinigameId($minigame);
			if($minigame == -1) return false;
			
			removeMinigamesFromConnection($connectionId);
			addConnectionMinigame($connectionId, $minigame, $level, -1);
			
			return true;
		} catch(Exception $e) {
			return false;
		}
	}

	function createConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		addConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score);
	}
	
	function modifyConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		updateConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score);
	}	
	
	function modifyConnectionStrength($Id,$Strength){
		updateConnectionStrength($Id,$Strength);
	}

	function modifyConnectionState($Id,$State){
		changeConnectionState($Id,$State);
	}
	
	function getConnectionsOfUser($userId) {
		return DAL_getConnectionsOfUser($userId);
	}
	
	function findConnectionIdByUsers($User1,$User2){
		return getConnectionIdByUsers($User1,$User2);
	}
?>