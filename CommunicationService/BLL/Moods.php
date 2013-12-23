<?php
require_once('../DAL/Moods.php');
	
	function createMood($description){
		insertMood($description);
	}
	
	function getAllMoods(){
		return getMoods();
	}
?>