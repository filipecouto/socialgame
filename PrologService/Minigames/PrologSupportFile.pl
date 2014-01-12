		    searchLetter(Letter,[Letter|_],Answer):-Answer is 0.
		searchLetter(_, [], Answer):-Answer is 1.
		searchLetter(Letter,[_|Word],Answer):-searchLetter(Letter, Word,Answer).
		doMove(Letter, Word, Answer):-searchLetter(Letter,Word, Answer).

		go :-
			doMove(r,[a,z,u,l],Answer),
			write(Answer).