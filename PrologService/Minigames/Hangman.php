<?php
	if(file_exists("PrologService/PrologService.php")){
		require_once("PrologService/PrologService.php");
	}
	else{
		require_once("PrologService.php");
	}
	require_once("BLL/Hangman.php");
	
	function beginGame(){
		return getWord();
	}
	
	function move($letter, $word){
	
	$length = count($word);
	$list = '['.$word[0];
	
	for($i =1; $i<$length;$i++)
	{
		$list.=",".$word[$i];
	}
	$list.=']';
	print_r($list);
	$predicate = 
		"searchLetter(Letter,[Letter|_],Answer):-Answer is 0.
		searchLetter(_, [], Answer):-Answer is 1.
		searchLetter(Letter,[_|Word],Answer):-searchLetter(Letter, Word,Answer).
		doMove(Letter, Word, Answer):-searchLetter(Letter,Word, Answer).

		go :-
			doMove($letter,$list,Answer),
			write(Answer).";
			print_r($predicate);
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}
?>