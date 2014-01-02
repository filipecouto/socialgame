<?php
	require_once("DataParser/DataParser.php");

	echo testService()."<br>";
	echo networkSize("[[1,[olamundo,csharp]],[2,[lol,sgrai]]]")."<br>";
	echo friendsWithTags("[[1,[olamundo,csharp]],[2,[lol,sgrai]],[3,[dolls,guns]]]","[lol,dolls,guns]")."<br>";

	require_once("Minigames/TicTacToe.php");

	echo tictactoe_Game("[o,z,x,x,x,z,o,z,z]")."<br>";
	echo tictactoe_First()."<br>";
?>