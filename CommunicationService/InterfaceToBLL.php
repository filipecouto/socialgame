<?php
	if (isset($_GET["Theme"]) && isset($_GET["Function"])){
		$theme = $_GET["Theme"];
		$function = $_GET["Function"];

		$theme = strtolower($theme);
		$theme = ucfirst($theme);

		$bllFile = "BLL/".$theme.".php";
		require_once($bllFile);

		if(function_exists($function)){
			$result = $function();
			if(is_resource($result)){
				$array = array();
				while ($row = mysql_fetch_array($result)) {
				   $array[] = get_object_vars((object)$row);
				}
			}
			else{
				$array = get_object_vars((object)$result);
			}
			return(json_encode($array));
		}
	}
?>