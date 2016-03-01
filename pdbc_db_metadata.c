
#include "php_pdbc.h"

zend_class_entry *pdbc_DatabaseMetaData_ce = NULL;
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

void pdbc_define_DatabaseMetaData(TSRMLS_D)
{
	zend_class_entry ce;
	INIT_CLASS_ENTRY(ce, CLASS_NAME_DATABASEMETADATA, pdbc_dbmetadata_methods);
	pdbc_DatabaseMetaData_ce = zend_register_internal_interface(&ce);
	/*
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_DATABASEMETADATA, pdbc_dbmetadata_methods);
	pdbc_DatabaseMetaData_ce = zend_register_internal_class(&ce);
	pdbc_Connection_ce->create_object = pdbc_dbmetadata_create_object;
	
	memcpy(&pdbc_dbmetadata_handlers, zend_get_std_object_handlers(), sizeof(pdbc_dbmetadata_handlers));
	pdbc_dbmetadata_handlers.free_obj = pdbc_dbmetadata_free_object;
	pdbc_dbmetadata_handlers.dtor_obj = pdbc_dbmetadata_destroy_object;
	pdbc_dbmetadata_handlers.offset = XtOffsetOf(pdbc_dbmetadata_object_t, zo);
	*/
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */