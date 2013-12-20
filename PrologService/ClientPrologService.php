<?php
	require_once("PrologService.php");

	$prolog = new Prolog;
	$prolog->testService();
	$prolog->networkSize("[[1,[olamundo,csharp]],[2,[lol,sgrai]]]");
	$prolog->friendsWithTags("[[1,[olamundo,csharp]],[2,[lol,sgrai]],[3,[dolls,guns]]]","[lol,dolls,guns]");
?>