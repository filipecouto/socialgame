<?php

	require_once('DAL/Notifications.php');
	require_once('DAL/Sessions.php');
	
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
	
	function findNotificationsByToken($Token,$ReadState){
		$userId = getUserBySession($Token);
		if($userId !=-1)
		{
			$notifications = findNotificationsByUser($userId,$ReadState);
			return $notifications;
		}else{
			return false;
		}
	}

	function findNotificationsByUser($UserId,$ReadState){
		return getNotificationsByUser($UserId,$ReadState);
	}
?>