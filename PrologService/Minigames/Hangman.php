<?php
	if(file_exists("PrologService/PrologService.php")){
		require_once("PrologService/PrologService.php");
	}
	else{
		require_once("PrologService.php");
	}
	
	function move($letter, $word){
		$predicate = 
		"searchLetter(Letter,[Letter|_],Answer):-Answer is 0.
		searchLetter(_, [], Answer):-Answer is 1.
		searchLetter(Letter,[_|Word],Answer):-searchLetter(Letter, Word,Answer).
		doMove(Letter, Word, Answer):-searchLetter(Letter,Word, Answer).

		go :-
			doMove($letter,$word),
			write(Return).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}
?>