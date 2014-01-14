<?php
	require_once("../PrologService.php");

	function SolveMaze($start, $end, $maze) {
		$predicate =
		":-include('mazesolver.pl').
		go :- solve($maze, ($end), ($start), Path, []),
		write(Path).";
		
		$prolog = new Prolog;
		
		return $prolog->executePredicate($predicate);
	}
?>