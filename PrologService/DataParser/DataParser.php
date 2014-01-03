<?php
	if(file_exists("PrologService/PrologService.php")){
		require_once("PrologService/PrologService.php");
	}
	else{
		require_once("PrologService.php");
	}

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

	function StrongestPath($Origin,$Destiny,$connections){
		foreach($connections as $connection)
		{
			$origin = $connection["origin"]; 
			$destiny = $connection["destiny"];
			$strength = $connection["strength"];
			$predicate.="liga($origin,$destiny,$strength).\n";
		}
	
		$predicate.= "
			caminhoMaisForte(Origem, Destino, Caminho,P):-
			caminho([(0,[Origem])],Destino,C,P),
			reverse(C,Caminho).

			caminho([(P,Prim)|_],Dest,Prim,P):- Prim=[Dest|_].

			caminho([(_,[Dest|_])|Resto],Dest,Perc,P):- !,
				caminho(Resto,Dest,Perc,P).

			caminho([(C,[Ult|T])|Outros],Dest,Perc,P):-
				findall((NC,[Z,Ult|T]),
				(proximo_no(Ult,T,Z,C1),NC is C+C1),Lista),
				append(Outros,Lista,NPerc),
				sort(NPerc,NPerc1),
				reverse(NPerc1,NPerc2),
				caminho(NPerc2,Dest,Perc,P).

			proximo_no(X,T,Z,C):- liga(X,Z,C), \+ member(Z,T).

			go :-
				caminhoMaisForte($Origin, $Destiny, Path,P),write(Path),nl,write(P).";
					
					
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