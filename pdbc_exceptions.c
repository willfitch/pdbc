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
#include "pdbc_exceptions.h"

zend_class_entry *pdbc_sql_exception;
zend_class_entry *pdbc_sql_feature_not_supported_exception_ce;
zend_class_entry *pdbc_sql_syntax_error_exception_ce;
zend_class_entry *pdbc_sql_timeout_exception_ce;
zend_class_entry *pdbc_sql_authorization_exception_ce;


void pdbc_define_exceptions(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_EXCEPTION, NULL);
	pdbc_sql_exception = zend_register_internal_class_ex(&ce, zend_ce_exception);
	
	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_FEATURE_EXCEPTION, NULL);
	pdbc_sql_feature_not_supported_exception_ce = zend_register_internal_class_ex(&ce, pdbc_sql_exception);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_SYNTAX_EXCEPTION, NULL);
	pdbc_sql_syntax_error_exception_ce = zend_register_internal_class_ex(&ce, pdbc_sql_exception);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_TIMEOUT_EXCEPTION, NULL);
	pdbc_sql_timeout_exception_ce = zend_register_internal_class_ex(&ce, pdbc_sql_exception);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_AUTH_EXCEPTION, NULL);
	pdbc_sql_authorization_exception_ce = zend_register_internal_class_ex(&ce, pdbc_sql_exception);
}

