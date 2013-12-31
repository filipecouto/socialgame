<?php
	require_once("PrologService.php");

	// Determines the size of a users network
	function networkSize($Friends){
		$predicate = 
		"networkSize(Friends,Size) :-
	    	length(Friends,Size).
	    go :-
	        networkSize($Friends,Size),
	        write(Size).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}

	// Gets friends with a list of tags in common
	function friendsWithTags($Friends,$Tags){
		$predicate =
		"friendsWithTags(Friends,Tags,FoundFriends) :- friendsWithTags(Friends,Tags,[],FoundFriends2), reverse(FoundFriends2,FoundFriends).
		friendsWithTags([],_,L,L).
		friendsWithTags([[_,[]]|T],Tags,L,FoundFriends) :- friendsWithTags(T,Tags,L,FoundFriends).
		friendsWithTags([[Id,[H2|T2]]|T],Tags,L,FoundFriends) :- member(H2,Tags),!,friendsWithTags(T,Tags,[Id|L],FoundFriends);
        friendsWithTags([[Id,T2]|T],Tags,L,FoundFriends).

	    go :-
	        friendsWithTags($Friends,$Tags,FoundFriends),
	        write(FoundFriends).";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}

	// For testing purposes
	function testService(){
		$predicate =
	    "test2(Num) :-
	    	Res is Num * 2,
	    	write(Res).
	    go :-
	        test2(2),
	        halt.";
        $prolog = new Prolog;
        return $prolog->executePredicate($predicate);
	}
?>