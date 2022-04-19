<?php
$lat = $_GET['lat'];
$long = $_GET['long'];
if(!is_numeric($lat) || !is_numeric($long)){
	//no command injection plz
	return;
}
$output = shell_exec("./AccidentGrabber '".$lat."' '".$long."' 1000");
echo $output;
?>
