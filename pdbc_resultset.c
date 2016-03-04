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

zend_class_entry *pdbc_result_set_ce = NULL;
zend_object_handlers pdbc_resultset_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_indexOrLabel, 0, 0, 1)
	ZEND_ARG_INFO(0, indexOrLabel)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_getDate, 0, 0, 1)
	ZEND_ARG_INFO(0, indexOrLabel)
	ZEND_ARG_INFO(0, dateTime)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_updateRep, 0, 0, 2)
	ZEND_ARG_INFO(0, indexOrLabel)
	ZEND_ARG_INFO(0, updateValue)
ZEND_END_ARG_INFO();


const zend_function_entry pdbc_resultset_methods[] = {
	PDBC_ABSTRACT_ME(ResultSet, deleteRow, arginfo_pdbc_ResultSet_void)
	PDBC_ABSTRACT_ME(ResultSet, getArray, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, getBlob, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, getBoolean, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, getDate, arginfo_pdbc_ResultSet_getDate)
	PDBC_ABSTRACT_ME(ResultSet, getFloat, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, getInt, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, getObject, arginfo_pdbc_ResultSet_indexOrLabel)
	PDBC_ABSTRACT_ME(ResultSet, refreshRow, arginfo_pdbc_ResultSet_void)
	PDBC_ABSTRACT_ME(ResultSet, updateArray, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateBoolean, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateBlob, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateFloat, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateInt, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateObject, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateDate, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateString, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateTime, arginfo_pdbc_ResultSet_updateRep)
	PDBC_ABSTRACT_ME(ResultSet, updateTimestamp, arginfo_pdbc_ResultSet_updateRep)
	PHP_FE_END
};

void pdbc_define_result_set(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, CLASS_NAME_RESULTSET, pdbc_resultset_methods);
	pdbc_result_set_ce = zend_register_internal_interface(&ce);

	zend_class_implements(pdbc_result_set_ce, 3, zend_ce_iterator, spl_ce_Countable, zend_ce_arrayaccess);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
