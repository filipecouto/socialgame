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
	
	function getTagById($tagId) {
		$dal = new DAL();
		
		$sql = sprintf("SELECT id, name, type FROM Tags WHERE id=%d", mysql_real_escape_string($tagId));
		
		$result = null;
		$resultSet = $dal->executeNonQuery($sql);
		
		if($row = mysql_fetch_array($resultSet)) {
			$result = array("id" => $row[0], "name" => $row[1], "type" => $row[2]);
		}
		
		mysql_free_result($resultSet);
		
		return $result;
	}
	
	function getUserTagIdsByUserId($userId) {
		$dal = new DAL();
		$sql = sprintf("SELECT t.id FROM Tags t, UserTag ut WHERE t.id=ut.tagID AND ut.userID=%d",
					   mysql_real_escape_string($userId));
		
		$result = array();
		$resultSet = $dal->executeNonQuery($sql);
		
		while($row = mysql_fetch_array($resultSet)) {
			$result[] = $row[0];
		}
		
		mysql_free_result($resultSet);
		
		return $result;
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
		$type = mysql_real_escape_string($type);
		
		if($type == "3") {
		
		} else if($type == "4") {
			$sql = sprintf("SELECT t.id id, t.name name, count(tc.tagID) count FROM Tags t, TagConnection tc WHERE t.id=tc.tagID AND t.type=%d GROUP BY t.id", $type);
			return $dal->executeNonQuery($sql);
		}
		
		return null;
	}
	
	function getTypeId($description) {
		$dal = new DAL();
		$description = mysql_real_escape_string($description);
		$sql = "SELECT id FROM TagTypes WHERE description = '$description'";
		$recordset = $dal->executeNonQuery($sql);
		$array = mysql_fetch_array($recordset);
		return $array["id"];
	}
	
	function deleteUserTags($userid) {
		$dal = new DAL();
		$userid = mysql_real_escape_string($userid);
		$sql = "DELETE FROM UserTag where userID = $userid";
		$dal->executeQuery($sql);
	}
	
	function checkTag($tag, $typeid) {
		$dal = new DAL();
		$tag = mysql_real_escape_string($tag);
		$typeid = mysql_real_escape_string($typeid);
		$sql = "SELECT id FROM Tags WHERE name = '$tag' AND type = $typeid";
		$recordset = $dal->executeNonQuery($sql);
		$tagid = -1;
		if(mysql_num_rows($recordset)>0) {
		  $array = mysql_fetch_array($recordset);
		  $tagid = $array["id"];
		}
		return $tagid;
	}
?>