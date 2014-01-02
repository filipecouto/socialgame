<?php
class DAL{

	/*
	* DATABASE COMMUNICATION
	*/

    private $servername="localhost";
    private $dbname="SocialGame";
    
    function db_connect(){
        $conn=mysql_connect($this->servername, "root", "nao sei"); 
        if (!$conn)
        {
            die('Could not connect: ' . mysql_error());
        }
        return $conn;
    }
	
	function executeQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
        if (!mysql_query($SQL,$conn))
        {
            die('Could not execute query insert:' . mysql_error());
        } else {
            //Only remove the comment for testing purposes, place it after!
            //echo "<br>Query well executed<br>";
        }
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
	}
	
	function executeNonQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
		$recordset = mysql_query($SQL,$conn);
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
		return $recordset;
	}
}
?>
