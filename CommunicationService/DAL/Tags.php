<?php
require_once('DAL/DAL.php');

//Insert Tag
	function insertTag($Name,$TypeId){
		$dal = new DAL();
		$sql = "INSERT INTO Tags (name,type) VALUES('$Name',$TypeId)";
		$tagId = $dal->executeQuery($sql);
		return $tagId;
	}
	
	//Insert new TagType
	function insertTagType($Description){
		$dal = new DAL();
		$sql = "INSERT INTO TagTypes (Description) VALUES('$Description')";
		$tagTypeId = $dal->executeQuery($sql);
		return $tagTypeId;
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
			$tagId = insertTag($TagName,$TypeId);
		}
		addTagConnection($ConnectionId,$tagId);
	}

	//Insert multiple tags into a connection
	function insertTagsConnection($ConnectionId,$Tags,$TypeId){
		$tagsArray = explode(";", $Tags);
		foreach($tagsArray as $tag){
			insertTagConnection($ConnectionId,$tag,$TypeId);
		}
	}
	
	//Update Tag Type
	function updateTagType($Id,$Description){
		$dal = new DAL();
		$sql = "UPDATE TagTypes SET Description = '$Description' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Delete Tag
	function deleteTag($tagId)
	{
		$dal = new DAL();
		$sql = "DELETE FROM Tags WHERE id = '$tagId'";
		$dal->executeQuery($sql);
	}
	
	function makePublicTagStats($type) {
		$dal = new DAL();
		
		$sql = sprintf("SELECT t.id id, t.name name, count(tc.tagID) count FROM Tags t, TagConnection tc WHERE t.id=tc.tagID AND t.type=%d GROUP BY t.id", mysql_real_escape_string($type));
		
		return $dal->executeNonQuery($sql);
	}
?>