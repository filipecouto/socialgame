<?php
	if (isset($_GET["Theme"]) and isset($_GET["Function"])){
		$theme = $_GET["Theme"];
		$function = $_GET["Function"];

		$theme = strtolower($theme);
		$theme = ucfirst($theme);

		$bllFile = "DAL" + $theme + ".php";
		require_once($bllFile);

		if(function_exists($function)){
			$result = $_GET[$function]();
			$array = get_object_vars($result);
			var_dump(json_encode($array));
		}
	}
?>