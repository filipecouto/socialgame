<?php
	require_once('DAL/Sessions.php');

	function check(){
		$dal = new DAL();
		if($dal->db_connect()) {
			return true;
		}
		return false;
	}
?>