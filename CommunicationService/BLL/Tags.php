<?php
	require_once('DAL/Sessions.php');
	require_once('DAL/Tags.php');

	function createTag($name,$typeId){
		insertTag($name,$typeId);
	}
	
	function createTagType($description){
		insertTagType($description);
	}
		
	function createTagConnection($ConnectionId,$TagName,$TypeId){
		insertTagConnection($ConnectionId,$TagName,$TypeId);
	}
	
	function modifyTagType($Id,$Description){
		updateTagType($Id,$Description);
	}
	
	function removeTagType($tagId){
		deleteTagType($tagId);
	}
	
	function removeTag($tagId){
		deleteTag($tagId);
	}
	
	function getTag($tagId) {
		return getTagById($tagId);
	}
	
	function getUserTags($userId) {
		return getUserTagIdsByUserId($userId);
	}

	function getUserTagsByToken($token){
		$userId = getUserBySession($token);
		if($userId != -1)
		{
			return returnUserTags($userId);
		}else{
			return false;
		}
	}
	
	/**
	 * Gets a {tag name, %} set reflecting the occurrence of tags of a certain type
	 */
	function getTagStats($token, $type) {
		$userId = getUserBySession($token);
		if($userId == -1) {
			$result = array();
			
			$resultSet = makePublicTagStats($type);
			while($row = mysql_fetch_array($resultSet)) {
				$result[] = array("id" => $row[0], "name" => $row[1], "occurrences" => $row[2]);
			}
			mysql_free_result($resultSet);
			
			return $result;
		} else {
			$result = array();
			
			$resultSet = makeUserTagStats($userId, $type);
			while($row = mysql_fetch_array($resultSet)) {
				$result[] = array("id" => $row[0], "name" => $row[1], "occurrences" => $row[2]);
			}
			mysql_free_result($resultSet);
			
			return $result;
		}
	}
?>