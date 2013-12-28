<?php

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
?>