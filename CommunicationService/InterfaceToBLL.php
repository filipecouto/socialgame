<?php
	if(isset($_GET["Theme"]) && isset($_GET["Function"])){
		$theme = $_GET["Theme"];
		$function = $_GET["Function"];
		if(isset($_GET["Params"])){
			$params = explode("^", $_GET["Params"]);
		}

		$theme = strtolower($theme);
		$theme = ucfirst($theme);

		$bllFile = "BLL/".$theme.".php";
		require_once($bllFile);

		if(function_exists($function)){
			if(isset($_GET["Params"])){
				$result = call_user_func_array($function, $params);
			}
			else{
				$result = $function();
			}
			if(is_resource($result)){
				$array_tmp = array();
				while ($row = mysql_fetch_array($result)) {
				   $array_tmp[] = get_object_vars((object)$row);
				}
			}
			else{
				$array_tmp = $result;
			}
				$array = array("data" => $array_tmp);
			print_r(json_encode($array));
		}
	}
?>