<?php
	require_once('DAL/Connection.php');
	
	function createConnection($UserId1, $UserdId2){
		addConnection($UserId1, $UserdId2);
	}
	
	function createConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		addConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score);
	}
	
	function modifyConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score){
		updateConnectionMinigame($ConnectionId,$MinigameId,$Difficulty,$Score)
	}	
	
	function modifyConnectionStrength($Id,$Strength){
		updateConnectionStrength($Id,$Strength);
	}

	function modifyConnectionState($Id,$State){
		changeConnectionState($Id,$State);
	}
	
	function getConnectionIdByUsers($User1,$User2){
		getConnectionIdByUsers($User1,$User2);
	}
?>