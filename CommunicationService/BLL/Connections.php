<?php
	require_once('DAL/Connections.php');
	require_once('DAL/Sessions.php');
	require_once('DAL/Tags.php');
	require_once('DAL/Notifications.php');

	
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
	
	function findConnectionIdByUsers($User1,$User2){
		return getConnectionIdByUsers($User1,$User2);
	}
?>