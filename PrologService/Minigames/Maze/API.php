<?php
	require_once("Maze.php");

	echo(solveMaze($_GET["currentPos"], $_GET["finalPos"], $_POST["maze"]));
?>