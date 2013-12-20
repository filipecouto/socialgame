<?php

	require_once('DAL/Minigames.php');
	
	function createMinigame($Name){
		insertMinigame($Name);
	}
	
	function modifyMinigame($Id,$Name){
		updateMinigame($Id,$Name);
	}
	
	function getMinigames(){
		getMinigames();
	}
	
	function removeMinigames($minigameId){
		deleteMinigames($minigameId);
	}
?>