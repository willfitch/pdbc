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

zend_class_entry *pdbc_SqlException_ce;
zend_class_entry *pdbc_SqlFeatureNotSupportedException_ce;
zend_class_entry *pdbc_SqlSyntaxErrorException_ce;
zend_class_entry *pdbc_SqlTimeoutException_ce;
zend_class_entry *pdbc_SqlAuthorizationException_ce;


void pdbc_define_Exceptions(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_EXCEPTION, NULL);
	pdbc_SqlException_ce = zend_register_internal_class_ex(&ce, zend_ce_exception);
	
	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_FEATURE_EXCEPTION, NULL);
	pdbc_SqlFeatureNotSupportedException_ce = zend_register_internal_class_ex(&ce, pdbc_SqlException_ce);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_SYNTAX_EXCEPTION, NULL);
	pdbc_SqlSyntaxErrorException_ce = zend_register_internal_class_ex(&ce, pdbc_SqlException_ce);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_TIMEOUT_EXCEPTION, NULL);
	pdbc_SqlTimeoutException_ce = zend_register_internal_class_ex(&ce, pdbc_SqlException_ce);

	INIT_CLASS_ENTRY(ce, CLASS_NAME_SQL_AUTH_EXCEPTION, NULL);
	pdbc_SqlAuthorizationException_ce = zend_register_internal_class_ex(&ce, pdbc_SqlException_ce);
}

