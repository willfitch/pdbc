--TEST--
Check for pdbc presence
--SKIPIF--
<?php if (!extension_loaded("pdbc")) print "skip"; ?>
--FILE--
<?php

// Check class/interface entries
var_dump(interface_exists('php\pdbc\Driver'));
var_dump(interface_exists('php\pdbc\Connection'));
var_dump(interface_exists('php\pdbc\ResultSet'));
var_dump(interface_exists('php\pdbc\DatabaseMetaData'));
var_dump(interface_exists('php\pdbc\Statement'));

var_dump(class_exists('php\pdbc\DriverManager'));

var_dump(class_exists('php\pdbc\SqlException'));
var_dump(class_exists('php\pdbc\SqlFeatureNotSupportedException'));
var_dump(class_exists('php\pdbc\SqlSyntaxErrorException'));
var_dump(class_exists('php\pdbc\SqlTimeoutException'));
var_dump(class_exists('php\pdbc\SqlAuthorizationException'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
bool(true)
