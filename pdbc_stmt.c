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

zend_class_entry *pdbc_Statement_ce = NULL;
zend_object_handlers pdbc_Statement_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Statement_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Statement_execute, 0, 0, 1)
	ZEND_ARG_INFO(0, sqlStatement)
ZEND_END_ARG_INFO();

const zend_function_entry pdbc_statement_methods[] = {
	PDBC_ABSTRACT_ME(Statement, cancel, arginfo_pdbc_Statement_void)
	PDBC_ABSTRACT_ME(Statement, close, arginfo_pdbc_Statement_void)
	PDBC_ABSTRACT_ME(Statement, execute, arginfo_pdbc_Statement_execute)
	PHP_FE_END
};

void pdbc_define_Statement(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_STATEMENT, pdbc_statement_methods);
	pdbc_Statement_ce = zend_register_internal_interface(&ce);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
