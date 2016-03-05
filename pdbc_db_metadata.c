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

zend_class_entry *pdbc_database_meta_data_ce = NULL;
zend_object_handlers pdbc_dbmetadata_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DatabaseMetaData_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DatabaseMetaData_getColumnPrivileges, 0, 0, 3)
	ZEND_ARG_INFO(0, catalog)
	ZEND_ARG_INFO(0, schema)
	ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_DatabaseMetaData_getColumns, 0, 0, 3)
	ZEND_ARG_INFO(0, catalog)
	ZEND_ARG_INFO(0, schema)
	ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO();

const zend_function_entry pdbc_dbmetadata_methods[] = {
	PDBC_ABSTRACT_ME(DatabaseMetaData, getCatalogs,					arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getCatalogSeparator,			arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getCatalogTerm,				arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getColumnPrivileges,			arginfo_pdbc_DatabaseMetaData_getColumnPrivileges)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getColumns,					arginfo_pdbc_DatabaseMetaData_getColumns)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getDatabaseMajorVersion,		arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getDatabaseMinorVersion,		arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getDriverName,				arginfo_pdbc_DatabaseMetaData_void)
	PDBC_ABSTRACT_ME(DatabaseMetaData, getDriverVersion,			arginfo_pdbc_DatabaseMetaData_void)
	PHP_FE_END
};

void pdbc_define_database_meta_data(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, CLASS_NAME_DATABASEMETADATA, pdbc_dbmetadata_methods);
	pdbc_database_meta_data_ce = zend_register_internal_interface(&ce);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
