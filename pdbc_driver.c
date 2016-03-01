
#include "php_pdbc.h"

zend_class_entry *pdbc_Driver_ce = NULL;
zend_object_handlers pdbc_Driver_handlers;

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Driver_void, 0, 0, 0)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Driver_acceptsUrl, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO();

ZEND_BEGIN_ARG_INFO_EX(arginfo_pdbc_Driver_connect, 0, 0, 1)
	ZEND_ARG_INFO(0, url)
ZEND_END_ARG_INFO();

const zend_function_entry pdbc_driver_methods[] = {
	PDBC_ABSTRACT_ME(Driver, acceptsUrl,		arginfo_pdbc_Driver_acceptsUrl)
	PDBC_ABSTRACT_ME(Driver, connect,			arginfo_pdbc_Driver_connect)
	PDBC_ABSTRACT_ME(Driver, getMajorVersion,	arginfo_pdbc_Driver_void)
	PDBC_ABSTRACT_ME(Driver, getMinorVersion,	arginfo_pdbc_Driver_void)
	PHP_FE_END
};

static zend_object *pdbc_driver_create_object(zend_class_entry *ce)
{
	pdbc_driver_object_t *driver;
	driver = ecalloc(1, sizeof(pdbc_driver_object_t) + zend_object_properties_size(ce));

	zend_object_std_init(&driver->zo, ce);
	object_properties_init(&driver->zo, ce);

	driver->zo.handlers = &pdbc_Driver_handlers;
	return &driver->zo;
}

void pdbc_define_Driver(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, CLASS_NAME_DRIVER, pdbc_driver_methods);
	pdbc_Driver_ce = zend_register_internal_interface(&ce);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: noet sw=4 ts=4
 */
