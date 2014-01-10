<?php
	
class DAL{
	private $servername="localhost";
    private $dbname="HangmanMinigame";
    
    function db_connect(){
        $conn=mysql_connect($this->servername, "root", "nao sei"); 
        if (!$conn)
        {
            die('Could not connect: ' . mysql_error());
        }
        return $conn;
    }
	
	function executeNonQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
        if (!mysql_query($SQL,$conn))
        {
            die('Could not execute query insert:' . mysql_error());
        } else {
            return mysql_insert_id();
        }
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
	}
	
	function executeQuery($SQL){
		$conn = $this->db_connect();
        if (!mysql_select_db($this->dbname,$conn))
        {
            die('Could not select BD: ' . mysql_error());
        }
		$recordset = mysql_query($SQL,$conn);
    //    if(!mysql_close($conn)) {
      //      die('Could not close BD:' . mysql_error());
        //}
		return $recordset;
	}
}
	function insertWord($word, $category){
		$id = findCategory($category);
		if($id == false)
		{
			insertCategory($category);
			$id= findCategory($category);
		}
		print_r($id);
		$dal = new DAL();
		$sql = "INSERT INTO Words (word, category) VALUES('$word', $id)";
		$dal->executeNonQuery($sql);
	}
	
	function findCategory($category)
	{
		$dal = new DAL();
		$sqlFind = sprintf("SELECT id FROM Categories WHERE name = '%s'", mysql_real_escape_string($category));
		print_r($sqlFind);
		$recordset = $dal->executeQuery($sqlFind);
		$array = mysql_fetch_array($recordset);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$id = $array["id"];
		}
		else{
			$id = false;
		}
		return $id;
	}
	
	function insertCategory($category){
		$dal = new DAL();
		$sql = "INSERT INTO Categories (name) VALUES('$category')";
		$dal->executeNonQuery($sql);
	}
	
	function getWord()
	{
		return getRandomWord();
		
	}
	function getRandomWord()
	{
		$dal = new DAL();
		$result = null;
		$sqlFind = "SELECT COUNT(1) FROM Words";
		$recordset = $dal->executeQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$wordsNumber = $recordset;
			print_r($wordsNumber);
			$id = rand(0,$wordsNumber);
			$sql = "SELECT h.word, c.name FROM Words h, Categories c WHERE h.category=c.id LIMIT $id, $id+1";
			$recordset = $dal->executeQuery($sql);
			$length = mysql_num_rows($recordset);
			if($length != 0){
				$result = array("word" => $recordset[0], "category" => $recordset[1]);
			}
			mysql_free_result($resultset);
		}
		else{
		}
		return $result;
	}
?>