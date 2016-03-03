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

/* $Id$ */

#include "php_pdbc.h"
#include <php_ini.h>

/* If you declare any globals in php_pdbc.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(pdbc)
*/

static PHP_PDBC_API pdbc_conn_info_t *pdbc_parse_url(zend_string *url);
static PHP_PDBC_API void pdbc_free_url(pdbc_conn_info_t *conn);

/* True global resources - no need for thread safety here */
/*static int le_pdbc;*/

zend_class_entry *pdbc_driver_manager_ce = NULL;
static zend_object_handlers pdbc_driver_manager_handlers;

zend_class_entry *pdbc_types_ce = NULL;

HashTable drivers;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("pdbc.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_pdbc_globals, pdbc_globals)
    STD_PHP_INI_ENTRY("pdbc.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_pdbc_globals, pdbc_globals)
PHP_INI_END()
*/


/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_pdbc_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_pdbc_init_globals(zend_pdbc_globals *pdbc_globals)
{
	pdbc_globals->global_value = 0;
	pdbc_globals->global_string = NULL;
}
*/
/* }}} */


zend_class_entry *pdbc_DriverManager_ce = NULL;
zend_object_handlers pdbc_DriverManager_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DriverManager_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DriverManager_getConnection, 0, 0, 0)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, user)
	ZEND_ARG_INFO(0, password)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DriverManager_getDriver, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO();

/* Purposely defined as private
 */
PDBC_METHOD(DriverManager, __construct)
{
}

/* {{{ proto Connection DriverManager::getConnection(string url[, string user[, string password]])
 */
PDBC_METHOD(DriverManager, getConnection)
{
	zend_string *url;
	zend_string *user;
	zend_string *password;
	pdbc_conn_info_t *conn;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S|SS", &url, &user, &password) == FAILURE) {
		return;
	}

	if ((conn = pdbc_parse_url(url)) == NULL) {
		return;
	}

	pdbc_free_url(conn);

	RETURN_FALSE;
}
/* }}} */

/* {{{ proto Driver DriverManager::getDriver(string url)
 */
PDBC_METHOD(DriverManager, getDriver)
{
	zend_string *str;
	pdbc_driver_t *tmp;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "S", &str) == FAILURE) {
		return;
	}

	if ((tmp = zend_hash_find_ptr(&drivers, str)) == NULL) {
		RETURN_NULL();
	}

	ZVAL_OBJ(return_value, tmp->get_driver_instance());
}
/* }}} */

/* {{{ proto array DriverManager::getDrivers(void)
 */
PDBC_METHOD(DriverManager, getDrivers)
{
	zend_string *key;
	array_init(return_value);

	ZEND_HASH_FOREACH_STR_KEY(&drivers, key) {
		if (key) {
			add_next_index_string(return_value, key->val);
		}
	} ZEND_HASH_FOREACH_END();
}
/* }}} */

static PHP_PDBC_API pdbc_conn_info_t *pdbc_parse_url(zend_string *url)
{
	pdbc_conn_info_t *conn;
	char *colon;
	char *urlval = url->val;
	int increment = 0;
	char tmp[1024];

	if (!url || url->len < 1) {
		return NULL;
	}

	conn = (pdbc_conn_info_t *) emalloc(sizeof(pdbc_conn_info_t));
	conn->driver = conn->host = conn->database = conn->user = conn->password = NULL;

	colon = strchr(url->val, ':');

	if (!colon) {
		pdbc_free_url(conn);
		return NULL;
	}

	increment = colon - url->val;
	strncpy(tmp, url->val, increment);

	/* Parse the driver
	 */

	if (!zend_hash_str_exists(&drivers, tmp, sizeof(tmp) - 1)) {
		/*
		throw_new_SqlException("Unknown or invalid driver supplied", 0);
		pdbc_free_url(conn);
		return NULL;*/
	}

	conn->driver = zend_string_init(tmp, sizeof(tmp) - 1, 0);
	memset(tmp, 0, sizeof(tmp));

	urlval = url->val + increment;

	if (*colon == ':') {
		/* We have a username
		 */
		urlval++;
		colon = strchr(urlval, '/');
		increment += (colon - urlval) + 1;
		strncpy(tmp, urlval, (colon - urlval));

		conn->user = zend_string_init(tmp, sizeof(tmp) - 1, 0);
		memset(tmp, 0, sizeof(tmp));
		urlval = url->val + increment;
	}

	if (!(*colon == '/')) {
		throw_new_SqlException("Invalid URL format provided", 0);
		pdbc_free_url(conn);
		return NULL;
	}

	/* Continue parsing password/host
	 */
	if (*++colon != '/') {
		/* Invalid format
		 */
		throw_new_SqlException("Invalid URL format provided", 0);
		pdbc_free_url(conn);
		return NULL;
	}

	colon++;
	increment += 2;
	urlval = url->val + increment;

	if ((colon = strchr(urlval, '@'))) {
		/* We have a password
		 */
		increment += (colon - urlval) + 1;
		strncpy(tmp, urlval, (colon - urlval));

		conn->password = zend_string_init(tmp, sizeof(tmp) - 1, 0);
		memset(tmp, 0, sizeof(tmp));
	}

	if (!(colon = strchr(urlval, ':')) && !(colon = strchr(urlval, '/'))) {
		throw_new_SqlException("No hostname provided in URL", 0);
		pdbc_free_url(conn);
		return NULL;
	}

	urlval = url->val + increment;
	strncpy(tmp, urlval, (colon - urlval));

	if (tmp[0] < 48) {
		throw_new_SqlException("Invalid hostname provided", 0);
		pdbc_free_url(conn);
		return NULL;
	}

	conn->host = zend_string_init(tmp, sizeof(tmp) - 1, 0);
	memset(tmp, 0, sizeof(tmp));

	if ((colon = strchr(urlval, ':'))) {
		/* We have a port
		 */
		increment += (colon - urlval) + 1;
		urlval = url->val + increment;

		if (!(colon = strchr(colon, '/'))) {
			pdbc_free_url(conn);
			return NULL;
		}

		increment += (colon - urlval);
		strncpy(tmp, urlval, (colon - urlval));

		conn->port = (zend_long) atol(tmp);

		if (conn->port < 1) {
			throw_new_SqlException("Invalid port provided. Port must be > 0", 0);
			pdbc_free_url(conn);
			return NULL;
		}

		memset(tmp, 0, sizeof(tmp));
		colon++;
	}

	if (!(colon = strchr(urlval, '/'))) {
		pdbc_free_url(conn);
		return NULL;
	}


	if (!urlval) {
		pdbc_free_url(conn);
		return NULL;
	}

	colon++;

	if (!colon || ((int) *colon < 1)) {
		pdbc_free_url(conn);
		return NULL;
	}

	conn->database = zend_string_init(colon, sizeof(colon) - 1, 0);
	return conn;
}

static PHP_PDBC_API void pdbc_free_url(pdbc_conn_info_t *conn)
{
	if (conn) {
		if (conn->driver) {
			zend_string_release(conn->driver);
		}

		if (conn->host) {
			zend_string_release(conn->host);
		}

		if (conn->database) {
			zend_string_release(conn->database);
		}

		if (conn->user) {
			zend_string_release(conn->user);
		}

		if (conn->password) {
			zend_string_release(conn->password);
		}

		efree(conn);
	}
}

PHP_PDBC_API int pdbc_register_driver(pdbc_driver_t *driver)
{
	return zend_hash_str_add_ptr(&drivers, driver->name->val, driver->name->len, driver) != NULL;
}

PHP_PDBC_API void pdbc_deregister_driver(pdbc_driver_t *driver)
{
	zend_hash_str_del(&drivers, driver->name->val, driver->name->len);
}

const zend_function_entry pdbc_driver_manager_methods[] = {
	PDBC_ME(DriverManager, __construct, arginfo_pdbc_DriverManager_void, ZEND_ACC_PRIVATE | ZEND_ACC_CTOR)
	PDBC_ME(DriverManager, getConnection, arginfo_pdbc_DriverManager_getConnection, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PDBC_ME(DriverManager, getDriver, arginfo_pdbc_DriverManager_getDriver, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PDBC_ME(DriverManager, getDrivers, arginfo_pdbc_DriverManager_void, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_FE_END
};

static zend_object *pdbc_driver_manager_create_object(zend_class_entry *ce)
{
	pdbc_driver_manager_t *intern;
	intern = ecalloc(1, sizeof(pdbc_driver_manager_t) + zend_object_properties_size(ce));

	zend_object_std_init(&intern->zo, ce);
	object_properties_init(&intern->zo, ce);

	intern->zo.handlers = &pdbc_driver_manager_handlers;
	return &intern->zo;
}

static void pdbc_driver_manager_free_object(zend_object *obj)
{
	zend_object_std_dtor(obj);
}

static void pdbc_driver_manager_destroy_object(zend_object *obj)
{
	zend_objects_destroy_object(obj);
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pdbc)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	zend_class_entry ce;

	zend_hash_init(&drivers, 0, NULL, NULL, 1);

	/* Call the individual class inits
	 */
	pdbc_define_Driver(TSRMLS_C);
	pdbc_define_Connection(TSRMLS_C);
	pdbc_define_ResultSet(TSRMLS_C);
	pdbc_define_DatabaseMetaData(TSRMLS_C);
	pdbc_define_Exceptions(TSRMLS_C);
	pdbc_define_Statement(TSRMLS_C);

	/* Register DriverManager
	 */
	INIT_CLASS_ENTRY(ce, CLASS_NAME_DRIVER_MANAGER, pdbc_driver_manager_methods);

	pdbc_driver_manager_ce = zend_register_internal_class(&ce);
	pdbc_driver_manager_ce->create_object = pdbc_driver_manager_create_object;

	memcpy(&pdbc_driver_manager_handlers, zend_get_std_object_handlers(), sizeof(pdbc_driver_manager_handlers));
	pdbc_driver_manager_handlers.free_obj = pdbc_driver_manager_free_object;
	pdbc_driver_manager_handlers.dtor_obj = pdbc_driver_manager_destroy_object;
	pdbc_driver_manager_handlers.offset = XtOffsetOf(pdbc_driver_manager_t, zo);

	/* Register Types
	 */
	INIT_CLASS_ENTRY(ce, CLASS_NAME_TYPES, NULL);
	pdbc_types_ce = zend_register_internal_class(&ce);

	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "ARRAY", PDBC_TYPE_ARRAY);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "BIGINT", PDBC_TYPE_BIGINT);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "BINARY", PDBC_TYPE_BINARY);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "BIT", PDBC_TYPE_BIT);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "BLOB", PDBC_TYPE_BLOB);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "BOOLEAN", PDBC_TYPE_BOOLEAN);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "CHAR", PDBC_TYPE_CHAR);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "DATE", PDBC_TYPE_DATE);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "DECIMAL", PDBC_TYPE_DECIMAL);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "DOUBLE", PDBC_TYPE_DOUBLE);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "FLOAT", PDBC_TYPE_FLOAT);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "INTEGER", PDBC_TYPE_INTEGER);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "NULL", PDBC_TYPE_NULL);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "REAL", PDBC_TYPE_REAL);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "TIME", PDBC_TYPE_TIME);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "TIMESTAMP", PDBC_TYPE_TIMESTAMP);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "TINYINT", PDBC_TYPE_TINYINT);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "VARBINARY", PDBC_TYPE_VARBINARY);
	REGISTER_PDBC_CLASS_CONST_LONG(pdbc_types_ce, "VARCHAR", PDBC_TYPE_VARCHAR);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pdbc)
{
	zend_hash_destroy(&drivers);

	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(pdbc)
{
#if defined(COMPILE_DL_PDBC) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(pdbc)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdbc)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "pdbc support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

const zend_function_entry pdbc_functions[] = {
  PHP_FE_END /* Must be the last line in cassandra_functions[] */
};

/* {{{ pdbc_module_entry
 */
zend_module_entry pdbc_module_entry = {
	STANDARD_MODULE_HEADER,
	"pdbc",
	pdbc_functions,
	PHP_MINIT(pdbc),
	PHP_MSHUTDOWN(pdbc),
	PHP_RINIT(pdbc),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pdbc),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pdbc),
	PHP_PDBC_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PDBC
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(pdbc)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
