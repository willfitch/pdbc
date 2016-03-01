
#include "php_pdbc.h"

zend_class_entry *pdbc_ResultSet_ce = NULL;
zend_object_handlers pdbc_resultset_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_ResultSet_getColumnPrivileges, 0, 0, 3)
	ZEND_ARG_INFO(0, catalog)
	ZEND_ARG_INFO(0, schema)
	ZEND_ARG_INFO(0, table)
ZEND_END_ARG_INFO();

const zend_function_entry pdbc_resultset_methods[] = {
	PHP_FE_END
};

void pdbc_define_ResultSet(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, CLASS_NAME_RESULTSET, pdbc_resultset_methods);
	pdbc_ResultSet_ce = zend_register_internal_interface(&ce);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
