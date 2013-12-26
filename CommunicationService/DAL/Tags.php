<?php
require_once('../DAL/DAL.php');

//Insert Tag
	function insertTag($Name,$TypeId){
		$dal = new DAL();
		$sql = "INSERT INTO Tags (Name,Type) VALUES('$Name','$TypeId')";
		$dal->executeQuery($sql);
	}
	
	//Insert new TagType
	function insertTagType($Description){
		$dal = new DAL();
		$sql = "INSERT INTO TagTypes (Description) VALUES('$Description)";
		$dal->executeQuery($sql);
	}
	
	//Add Tag to a Connection with TagId
	function addTagConnection($ConnectionId, $TagId){
		$dal = new DAL();
		$sql = "INSERT INTO TagConnection (ConnectionId,TagId) VALUES('$ConnectionId','$TagId')";
		$dal->executeQuery($sql);
	}
	
	//Insert new relation connection and tag, with TagName
	function insertTagConnection($ConnectionId,$TagName,$TypeId){
		$dal = new DAL();
		$sqlFind = "SELECT Id FROM Tags WHERE Name = '$TagName'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$tagId = $record["Id"];
		}
		else{
			insertTag($TagName,$TypeId);
			$tagId = mysql_insert_id();
		}
		addTagConnection($ConnectionId,$tagId);
	}
	
	//Update Tag Type
	function updateTagType($Id,$Description){
		$dal = new DAL();
		$sql = "UPDATE TagTypes SET Description = '$Description' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	function deleteTag($tagId)
	{
		$dal = new DAL();
		$sql = "DELETE FROM Tag WHERE id = '$tagId'";
		$dal->executeQuery($sql);
	}
	?>