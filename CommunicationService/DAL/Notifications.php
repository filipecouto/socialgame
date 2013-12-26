<?php
require_once('../DAL/DAL.php');

//Insert new Notification Type
	function insertNotificationType($Desctiption){
		$dal = new DAL();
		$sql = "INSERT INTO NotificationTypes (Description) VALUES('$Description')";
		$dal->executeQuery($sql);
	}
	
	//Create new Notification
	function createNotification($TypeId,$ToUserId,$ObjectId){
		$dal = new DAL();
		$sql = "INSERT INTO Notifications (Type,To,Read,Object) VALUES('$TypeId','$ToUserId',0,'$ObjectId')";
		$dal->executeQuery($sql);
	}
	
	//Update Notification Type
	function updateNotificationType($Id,$Description){
		$dal = new DAL();
		$sql = "UPDATE NotificationTypes SET Description = '$Description' WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}

	//Change Notification Read Status
	function changeNotificationRead($Id){
		$dal = new DAL();
		$sql = "UPDATE Notifications SET Read = 1 WHERE Id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Get Users Notifications either Read (1) or To Be Read (0)
	function getNotificationsByUser($UserId,$ReadState){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Notifications WHERE To = '$UserId' AND Read = '$ReadState'";
		$recordset = $dal->executeNonQuery($sqlFind);
		return $recordset;
	}
?>