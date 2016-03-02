
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
