<?php
require_once('DAL/DAL.php');

//Insert new Notification Type
	function insertNotificationType($Description){
		$dal = new DAL();
		$sql = "INSERT INTO NotificationTypes (Description) VALUES('$Description')";
		print_r($sql);
		$dal->executeQuery($sql);
	}
	
	//Create new Notification
	function insertNotification($TypeId,$ToUserId,$ObjectId){
		$dal = new DAL();
		$sql = "INSERT INTO Notifications (`type`,`to`,`read`,`object`) VALUES('$TypeId','$ToUserId','0','$ObjectId')";
		print_r($sql);
		echo "\n";
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
		$sql = "UPDATE Notifications SET `read` = 1 WHERE id = '$Id'";
		$dal->executeQuery($sql);
	}
	
	//Get Users Notifications either Read (1) or To Be Read (0)
	function getNotificationsByUser($UserId,$ReadState){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Notifications WHERE `to` = '$UserId' AND `read` = '$ReadState'";
		$recordset = $dal->executeNonQuery($sqlFind);
		return $recordset;
	}
?>