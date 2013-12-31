<?php
	class Prolog{
		private $programLocation = "/usr/lib/swi-prolog/bin/i386/swipl";

		function executePredicate($Predicate,$FileLocation = "PrologSupportFile.pl"){
			$prologFile = fopen($FileLocation, w);
	        $predicates = <<<EOT
		    $Predicate
EOT;
		    fwrite($prologFile, $predicates);
			$cmd = "nice -n15 /usr/lib/swi-prolog/bin/i386/swipl -f '$FileLocation' -g go";
			$output = shell_exec($cmd);
			return $output;
		}
	}
?>