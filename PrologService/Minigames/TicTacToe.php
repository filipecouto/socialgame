<?php
	if(file_exists("PrologService/PrologService.php")){
		require_once("PrologService/PrologService.php");
	}
	else{
		require_once("PrologService.php");
	}

	// TIC TAC TOE GAME
	// Analysis the game status and makes the next move
	function tictactoe_Game($Game){
		$predicate = 
		":-include('Minigames/TicTacToe.pl').

		go :-
			tictactoe($Game,Return),
			write(Return).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}

	// Gets the first to play
	function tictactoe_First(){
		$predicate = 
		":-include('Minigames/TicTacToe.pl').

		go :-
			whoIsFirst(Return),
			write(Return).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}
?>