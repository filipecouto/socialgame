<?php

	require_once('DAL/Notification.php');
	
	function createNotificationType($Desctiption){
		insertNotificationType($Desctiption);
	}
	
	function createNotification($TypeId,$ToUserId,$ObjectId){
		createNotification($TypeId,$ToUserId,$ObjectId);
	}
	
	function modifyNotificationType($Id,$Description){
		updateNotificationType($Id,$Description);
	}
	
	function changeNotificationRead($Id){
		changeNotificationRead($Id);
	}
	
	function findNotificationsByUser($UserId,$ReadState){
		getNotificationsByUser($UserId,$ReadState)
	}
?>