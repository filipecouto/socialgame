<?php
	require_once("PrologService/Minigames/TicTacToe.php");

	function Game($Game){
		return tictactoe_Game($Game);
	}

	function First(){
		return tictactoe_First();
	}
?>