 <?php 
  require_once("Hangman.php");

  $method = $_GET["method"]; 
  $params = explode(",",$_GET["params"]);
  if($method == "beginGame"){
    $array = beginGame();
    $result = $array["category"].','.$array["word"];
   
  }if ($method == "move") {
    $letter= $params[0];
    $word = $params[1];
    $result=  move($letter, $word);
  }
  
  print_r(json_encode($result)); 
  ?>