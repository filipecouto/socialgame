<?php
	if (isset($_POST["Theme"])	and isset($_POST["Function"])){
		$theme = $_POST["Theme"];
		$function = $_POST["Function"];

		$theme = strtolower($theme);
		$theme = ucfirst($theme);

		$bllFile = "BLL" + $theme + ".php";
		require_once($bllFile);

		if(function_exists($function)){
			$result = $_GET[$function]();
			$array = get_object_vars($result);
			var_dump(json_encode($array));
		}
	}
?>