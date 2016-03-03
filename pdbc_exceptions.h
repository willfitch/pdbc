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

#ifndef HAVE_PDBC_EXCEPTIONS_H
#define HAVE_PDBC_EXCEPTIONS_H

#include "zend_exceptions.h"

extern PHP_PDBC_API zend_class_entry *pdbc_SqlException_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_SqlFeatureNotSupportedException_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_SqlSyntaxErrorException_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_SqlTimeoutException_ce;
extern PHP_PDBC_API zend_class_entry *pdbc_SqlAuthorizationException_ce;

/* {{{ void throw_new_SqlException
 */
static inline void throw_new_SqlException(const char *message, zend_long code)
{
	zend_throw_exception(pdbc_SqlException_ce, message, code);
}
/* }}} */

/* {{{ void throw_new_FeatureException
 */
static inline void throw_new_FeatureException(const char *message, zend_long code)
{
	zend_throw_exception(pdbc_SqlFeatureNotSupportedException_ce, message, code);
}
/* }}} */

/* {{{ void throw_new_SyntaxException
 */
static inline void throw_new_SyntaxException(const char *message, zend_long code)
{
	zend_throw_exception(pdbc_SqlSyntaxErrorException_ce, message, code);
}
/* }}} */

/* {{{ void throw_new_TimeoutException
 */
static inline void throw_new_TimeoutException(const char *message, zend_long code)
{
	zend_throw_exception(pdbc_SqlTimeoutException_ce, message, code);
}
/* }}} */

/* {{{ void throw_new_AuthException
 */
static inline void throw_new_AuthException(const char *message, zend_long code)
{
	zend_throw_exception(pdbc_SqlAuthorizationException_ce, message, code);
}
/* }}} */

#endif
