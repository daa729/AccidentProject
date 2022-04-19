<?php
$lat = $_GET['lat'];
$long = $_GET['long'];
$amount = $_GET['amount'];
if(!is_numeric($lat) || !is_numeric($long) || !is_numeric($amount)){
	//no command injection plz
	return;
}
if($amount < 1){
	$amount = 1;
}
else if($amount > 2845342){
	$amount = 2845342;
}
$output = shell_exec("./AccidentGrabber '".$lat."' '".$long."' '".$amount."'");
echo $output;
?>
