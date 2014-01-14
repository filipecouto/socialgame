<?php
	require_once('DAL/Sessions.php');
	require_once('DAL/Minigames.php');
	
	function createMinigame($Name){
		insertMinigame($Name);
	}
	
	function modifyMinigame($Id,$Name){
		updateMinigame($Id,$Name);
	}
	
	function findMinigames(){
		return getMinigames();
	}
	
	function removeMinigames($minigameId){
		deleteMinigames($minigameId);
	}
	
	function getPendingMinigames($token) {
		$userId = getUserBySession($token);
		if($userId != -1) {
			return getPendingMinigamesByUser($userId);
		} else {
			return false;
		}
	}
	
	function setMinigameScore($token, $connectionId, $minigameId, $score) {
		$userId = getUserBySession($token);
		if($userId != -1) {
			return setMinigameScoreForChallenge($userId, $connectionId, $minigameId, $score);
		} else {
			return false;
		}
	}
?>