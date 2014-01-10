<?php
	require_once('DAL/DAL.php');
	
	function insertWord($word, $category){
		$id = findCategory($category);
		if($id == false)
		{
			insertCategory($category);
			$id = findCategory($category);
		}
		
		$dal = new DAL();
		$sql = "INSERT INTO Hangman (word, category) VALUES('$word', $category)";
		$dal->executeQuery($sql);
	}
	
	function findCategory($category)
	{
		%sqlFind = "SELECT id FROM Category WHERE name = $category";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$id = $recordset;
		}
		else{
			$id = false;
		}
		return $id;
	}
	
	function insertCategory($category){
		$dal = new DAL();
		$sql = "INSERT INTO Category (name VALUES('$category')";
		$dal->executeQuery($sql);
	}
	
	function getWord()
	{
		$categoryId = getRandomCategory();
		return getRandomWord($categoryId);
	}
	function getRandomWord($categoryId)
	{
		
	}
	
	function getRandomCategory()
	{
		
	}
?>