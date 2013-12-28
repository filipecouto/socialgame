<?php
require_once('../DAL/DAL.php');

//Insert new Mood
	function insertMood($Description){
		$dal = new DAL();
		$sql = "INSERT INTO Moods (description) VALUES('$Description')";
		$dal->executeQuery($sql);
	}
	
	//Update Mood
	function updateMood($Id,$Description){
		$dal = new DAL();
		$sql = "UPDATE Moods SET description = '$Description' WHERE id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	function getMoods(){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Moods";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			for($i=0; $i<$length; $i++){
				$record[$i] = mysql_fetch_array($recordset);
				$moods[$i] = $record[$i];
				
			}
		}
		else{
			$moods = -1;
		}
		return $moods;
	}
	
	//Delete Mood
	function deleteMood($moodId){
		$dal = new DAL();
		$sql = "DELETE FROM Moods WHERE id = '$moodId'";
		$dal->executeQuery($sql);
	}
?>