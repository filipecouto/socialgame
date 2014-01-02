<?php
require_once('DAL/DAL.php');

	function insertSession($userId,$token){
		$dal = new DAL();
        $sql = "INSERT INTO Session (userId, token) VALUES('$userId', '$token')";
		echo $sql;
		$dal->executeQuery($sql);
    }
	
	function changeSession($UserId,$token){
		$dal = new DAL();
		$sql = "  Session SET userId = '$userId' WHERE  token = '$token'";
		$dal->executeQuery($sql);
	}
	
	function getSession($token){
		$dal = new DAL();
		$sqlFind = "SELECT * FROM Session WHERE token = '$token'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$session = $record;
		}
		else{
			$session = -1;
		}
		return $session;
	}
	
	function getUserBySession($token){
		$dal = new DAL();
		$sqlFind = "SELECT userId FROM Session WHERE token = '$token'";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$record = mysql_fetch_array($recordset);
			$userId = $record["userId"];
		}
		else{
			$userId = -1;
		}
		return $userId;
	}

	function isToken($token){
		if (isset($token) && $token) {
			$dal = new DAL();
			$query = "SELECT * FROM Session WHERE token='$token'";
			$recordset = $dal->executeNonQuery($query);
			$length = mysql_num_rows($recordset);
			if ($length > 0) {
				return true;
			} else {
				return false;
			}
		}
	}

	function generateUniqueToken($number){
		$arr = array('a', 'b', 'c', 'd', 'e', 'f',
					 'g', 'h', 'i', 'j', 'k', 'l',
					 'm', 'n', 'o', 'p', 'r', 's',
					 't', 'u', 'v', 'x', 'y', 'z',
					 'A', 'B', 'C', 'D', 'E', 'F',
					 'G', 'H', 'I', 'J', 'K', 'L',
					 'M', 'N', 'O', 'P', 'R', 'S',
					 'T', 'U', 'V', 'X', 'Y', 'Z',
					 '1', '2', '3', '4', '5', '6',
					 '7', '8', '9', '0');
		$token = "";
		for ($i = 0; $i < $number; $i++) {
			$index = rand(0, count($arr) - 1);
			$token .= $arr[$index];
		}

		if (isToken($token)) {
			return generateUniqueToken($number);
		} else {
			return $token;
		}
	}

	function token(){
		return generateUniqueToken(64);
	}
	
	function deleteSession($token){
		$dal = new DAL();
        $sql = "DELETE FROM Session WHERE token = '$token'";
		$dal->executeQuery($sql);
	}
?>