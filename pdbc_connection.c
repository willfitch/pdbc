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

#include "zend_interfaces.h"
#include "php_pdbc.h"

zend_class_entry *pdbc_connection_ce;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_clientInfo, 0, 0, 0)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_prepareCall, 0, 0, 0)
	ZEND_ARG_INFO(0, sql)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_prepareStatement, 0, 0, 0)
	ZEND_ARG_INFO(0, sql)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_setAutoCommit, 0, 0, 0)
	ZEND_ARG_INFO(0, autoCommit)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_setNetworkTimeout, 0, 0, 0)
	ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection_setTransactionIsolation, 0, 0, 0)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Connection___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
	ZEND_ARG_INFO(0, user)
	ZEND_ARG_INFO(0, password)
ZEND_END_ARG_INFO();

const zend_function_entry pdbc_connection_methods[] = {
	PDBC_ABSTRACT_ME(Connection, __construct,				arginfo_pdbc_Connection___construct)
	PDBC_ABSTRACT_ME(Connection, close,						arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, commit,					arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, createStatement,			arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getAutoCommit,				arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getCatalog,				arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getClientInfo,				arginfo_pdbc_Connection_clientInfo)
	PDBC_ABSTRACT_ME(Connection, getMetaData,				arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getNetworkTimeout,			arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getSchema,					arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, getTransactionIsolation,	arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, isClosed,					arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, prepareCall,				arginfo_pdbc_Connection_prepareCall)
	PDBC_ABSTRACT_ME(Connection, prepareStatement,			arginfo_pdbc_Connection_prepareStatement)
	PDBC_ABSTRACT_ME(Connection, rollback,					arginfo_pdbc_Connection_void)
	PDBC_ABSTRACT_ME(Connection, setAutoCommit,				arginfo_pdbc_Connection_setAutoCommit)
	PDBC_ABSTRACT_ME(Connection, setNetworkTimeout,			arginfo_pdbc_Connection_setNetworkTimeout)
	PDBC_ABSTRACT_ME(Connection, setTransactionIsolation,	arginfo_pdbc_Connection_setTransactionIsolation)
	PHP_FE_END
};

void pdbc_define_connection(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_CONNECTION, pdbc_connection_methods);
	pdbc_connection_ce = zend_register_internal_interface(&ce);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
