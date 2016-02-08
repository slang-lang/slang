#!/usr/bin/php

<?php

$count = 1;
$upperbound = 100000;

print("Starting performance test (by counting from " . $count . " to " . $upperbound . ")...");

while ( $count < $upperbound ) {
	//print("count = " + $count);
	$count = $count + 1;
}

print("Finished performance test.");

?>
