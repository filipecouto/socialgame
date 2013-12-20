<?php
	class Prolog{
		private $programLocation = "/usr/lib/swi-prolog/bin/i386/swipl";

		function executePredicate($Predicate){
			$prologFile = fopen("/var/www/SocialGameCommunicationService/test.pl", w);
	        $predicates = <<<EOT
		    $Predicate
EOT;
		    fwrite($prologFile, $predicates);
			$cmd = "nice -n15 /usr/lib/swi-prolog/bin/i386/swipl -f /var/www/SocialGameCommunicationService/test.pl -g go";
			$output = shell_exec($cmd);
			echo $output;
			return $output;
		}

		function networkSize($Friends){
			$predicate = 
			"networkSize(Friends,Size) :-
		    	length(Friends,Size).
		    go :-
		        networkSize($Friends,Size),
		        write(Size).";
	        $this->executePredicate($predicate);
		}

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
	        $this->executePredicate($predicate);
		}

		function testService(){
			$predicate =
		    "test2(Num) :-
		    	Res is Num * 2,
		    	write(Res).
		    go :-
		        test2(2),
		        halt.";
	        $this->executePredicate($predicate);
		}
	}
?>