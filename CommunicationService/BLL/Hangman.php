<?php
	require_once('DAL/Hangman.php');
	
	function addWord($word, $category){
		insertWord($word, $category);
	}
	
	function generateRandomWord(){
		return getWord();
	}
	
?>