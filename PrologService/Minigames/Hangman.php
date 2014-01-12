<?php
	require_once("PrologService.php");
	require_once("BLL/Hangman.php");
	
	function beginGame(){
		return generateRandomWord();
	}
	
	function move($letter, $wordString){
	 $word = str_split($wordString);
	$length = count($word);
	$list = '['.$word[0];
	for($i =1; $i<$length;$i++)
	{
		$list.=",".$word[$i];
	}
	$list.=']';
	$predicate = 
		"searchLetter(Letter,[Letter|_],Answer):-Answer is 0.
		searchLetter(_, [], Answer):-Answer is 1.
		searchLetter(Letter,[_|Word],Answer):-searchLetter(Letter, Word,Answer).
		doMove(Letter, Word, Answer):-searchLetter(Letter,Word, Answer).

		go :-
			doMove($letter,$list,Answer),
			write(Answer).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}
?>