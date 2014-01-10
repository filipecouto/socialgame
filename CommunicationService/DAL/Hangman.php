<?php
	require_once('DAL/DAL.php');
	
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
        if(!mysql_close($conn)) {
            die('Could not close BD:' . mysql_error());
        }
		return $recordset;
	}
	function insertWord($word, $category){
		$id = findCategory($category);
		if($id == false)
		{
			insertCategory($category);
			$id = findCategory($category);
		}
		
		$dal = new DAL();
		$sql = "INSERT INTO Hangman (word, category) VALUES('$word', $category)";
		$dal->executeQuery($sql);
	}
	
	function findCategory($category)
	{
		%sqlFind = "SELECT id FROM Category WHERE name = $category";
		$recordset = $dal->executeNonQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$id = $recordset;
		}
		else{
			$id = false;
		}
		return $id;
	}
	
	function insertCategory($category){
		$dal = new DAL();
		$sql = "INSERT INTO Category (name VALUES('$category')";
		executeNonQuery($sql);
	}
	
	function getWord()
	{
		return getRandomWord();
		
	}
	function getRandomWord()
	{
		$result = null;
		%sqlFind = "SELECT COUNT(1) FROM Hangman";
		$recordset = executeQuery($sqlFind);
		$length = mysql_num_rows($recordset);
		if($length != 0){
			$wordsNumber = $recordset;
			$id = rand(0,$wordsNumber);
			$sql = "SELECT h.word, c.name FROM Hangman h, Categories c WHERE h.category=c.id LIMIT $id, $id+1";
			$recordset = executeQuery($sql);
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