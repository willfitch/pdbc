--TEST--
Check for pdbc presence
--SKIPIF--
<?php if (!extension_loaded("pdbc")) print "skip"; ?>
--FILE--
<?php

// Check class/interface entries
var_dump(interface_exists('php\sql\Driver'));

?>
--EXPECT--
bool(true)
