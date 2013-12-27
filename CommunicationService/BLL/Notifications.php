<?php

	require_once('../DAL/Notifications.php');
	
	function createNotificationType($Description){
		insertNotificationType($Description);
	}
	
	function createNotification($TypeId,$ToUserId,$ObjectId){
		insertNotification($TypeId,$ToUserId,$ObjectId);
	}
	
	function modifyNotificationType($Id,$Description){
		updateNotificationType($Id,$Description);
	}
	
	function modifyNotificationRead($Id){
		changeNotificationRead($Id);
	}
	
	function findNotificationsByUser($UserId,$ReadState){
		return getNotificationsByUser($UserId,$ReadState);
	}
?>