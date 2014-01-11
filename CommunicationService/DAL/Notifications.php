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
		return DAL_getNotificationsByUserAndState($UserId,$ReadState);
	}
	
	function getNotificationBasesForUser($token) {
		$userId = getUserBySession($token);
		return DAL_getNotificationIdsByUser($userId);
	}
	
	function getNotification($token, $id) {
		$userId = getUserBySession($token);
		return DAL_getNotificationByUser($userId, $id);
	}
	
	function markNotificationRead($token, $id, $read) {
		$userId = getUserBySession($token);
		changeNotificationOfUserRead($id, $userId, $read);
		return true;
	}
?>