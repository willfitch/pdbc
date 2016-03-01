--TEST--
Check for pdbc presence
--SKIPIF--
<?php if (!extension_loaded("pdbc")) print "skip"; ?>
--FILE--
<?php

// Check class/interface entries
var_dump(interface_exists('php\sql\Driver'));
var_dump(interface_exists('php\sql\Connection'));
var_dump(interface_exists('php\sql\ResultSet'));
var_dump(interface_exists('php\sql\DatabaseMetaData'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
