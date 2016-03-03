/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Will Fitch <willfitch@php.net>                               |
  +----------------------------------------------------------------------+
*/

#ifndef HAVE_PDBC_H
#define HAVE_PDBC_H

#define CLASS_NAME_DRIVER "php\\pdbc\\Driver"
#define CLASS_NAME_CONNECTION "php\\pdbc\\Connection"
#define CLASS_NAME_DATABASEMETADATA "php\\pdbc\\DatabaseMetaData"
#define CLASS_NAME_RESULTSET "php\\pdbc\\ResultSet"
#define CLASS_NAME_STATEMENT "php\\pdbc\\Statement"
#define CLASS_NAME_DRIVER_MANAGER "php\\pdbc\\DriverManager"
#define CLASS_NAME_TYPES "php\\pdbc\\Types"
#define CLASS_NAME_SQL_EXCEPTION "php\\pdbc\\SqlException"
#define CLASS_NAME_SQL_FEATURE_EXCEPTION "php\\pdbc\\SqlFeatureNotSupportedException"
#define CLASS_NAME_SQL_SYNTAX_EXCEPTION "php\\pdbc\\SqlSyntaxErrorException"
#define CLASS_NAME_SQL_TIMEOUT_EXCEPTION "php\\pdbc\\SqlTimeoutException"
#define CLASS_NAME_SQL_AUTH_EXCEPTION "php\\pdbc\\SqlAuthorizationException"

#define PDBC_TYPE_ARRAY (1 << 1)
#define PDBC_TYPE_BIGINT (1 << 20)
#define PDBC_TYPE_BINARY (1 << 3)
#define PDBC_TYPE_BIT (1 << 17)
#define PDBC_TYPE_BLOB (1 << 4)
#define PDBC_TYPE_BOOLEAN (1 << 5)
#define PDBC_TYPE_CHAR (1 << 6)
#define PDBC_TYPE_DATE (1 << 7)
#define PDBC_TYPE_DECIMAL (1 << 18)
#define PDBC_TYPE_DOUBLE (1 << 19)
#define PDBC_TYPE_FLOAT (1 << 8)
#define PDBC_TYPE_INTEGER (1 << 9)
#define PDBC_TYPE_NULL (1 << 10)
#define PDBC_TYPE_REAL (1 << 21)
#define PDBC_TYPE_SMALLINT (1 << 11)
#define PDBC_TYPE_TIME (1 << 12)
#define PDBC_TYPE_TIMESTAMP (1 << 13)
#define PDBC_TYPE_TINYINT (1 << 14)
#define PDBC_TYPE_VARBINARY (1 << 15)
#define PDBC_TYPE_VARCHAR (1 << 16)

typedef struct _pdbc_driver_t pdbc_driver_t;

typedef struct {
	zend_string *driver;
	zend_string *host;
	zend_string *database;
	zend_string *user;
	zend_string *password;
	zend_long	port;
} pdbc_conn_info_t;

typedef struct {
	pdbc_conn_info_t *conn;
} pdbc_handle_t;

typedef zend_object *(*pdbc_driver_create_connection)(pdbc_handle_t *);
typedef zend_object *(*pdbc_get_connection_instance)();
typedef zend_object *(*pdbc_get_driver_instance)();

struct _pdbc_driver_t {
	zend_string						*name;

	pdbc_driver_create_connection	create_connection;
	pdbc_get_driver_instance		get_driver_instance;
};


typedef struct {
	zend_object zo;
} pdbc_driver_manager_t;


extern PHP_PDBC_API zend_class_entry *pdbc_Connection_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_DatabaseMetaData_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_Driver_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_ResultSet_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_Statement_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_DriverManager_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_Types_ce;

#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
