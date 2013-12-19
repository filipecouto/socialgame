<?php
require_once "nusoap.php";
require('DAL.php');

function getShippingPrice($PublicationPrice,$WeightList) {
   $weights = explode(",",$WeightList);
   $shipmentPrice = 0;
   for($i = 0;$i < sizeof($weights);$i++){
       if(doubleval($weights[$i]) > 1){
           $shipmentPrice+=1;
       }
       else{
           $shipmentPrice+=0.3;
       }
   }
   if($shipmentPrice >= $PublicationPrice){
       $shipmentPrice = 0;
   }
   
   return $shipmentPrice;
}

$namespace = "http://localhost/ShippingALL";
// create a new soap server
$server = new soap_server();
// configure our WSDL
$server->configureWSDL("ShippingAllService");
// set our namespace
$server->wsdl->schemaTargetNamespace = $namespace;
// register our WebMethod
$server->register(
               // method name:
               'getShippingPrice',
               // parameter list:
               array('PublicationPrice'=>'xsd:string','WeightList'=>'xsd:string'),
               // return value(s):
               array('return'=>'xsd:string'),
               // namespace:
               $namespace,
               // soapaction: (use default)
               false,
               // style: rpc or document
               'rpc',
               // use: encoded or literal
               'encoded',
               // description: documentation for the method
               'ShippingAll Web Service');
               
// Get our posted data if the service is being consumed
// otherwise leave this data blank.                
$POST_DATA = isset($GLOBALS['HTTP_RAW_POST_DATA'])
               ? $GLOBALS['HTTP_RAW_POST_DATA'] : '';

// pass our posted data (or nothing) to the soap service                    
$server->service($POST_DATA);                
exit();
?>