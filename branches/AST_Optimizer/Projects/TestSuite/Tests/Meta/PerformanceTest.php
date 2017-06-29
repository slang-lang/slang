#!/usr/bin/php

<?php

$lowerbound = 1;
$upperbound = 100000;

print("Starting performance test (by counting from " . $lowerbound . " to " . $upperbound . ")...\n");

while ( $lowerbound < $upperbound ) {
	//print("lowerbound = " . $lowerbound);
	//$lowerbound = $lowerbound + 1;
	$lowerbound++;
}

print("Finished performance test.\n");

?>
