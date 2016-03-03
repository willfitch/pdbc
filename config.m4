dnl $Id$
dnl config.m4 for extension pdbc

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(pdbc, for pdbc support,
dnl Make sure that the comment is aligned:
dnl [  --with-pdbc             Include pdbc support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(pdbc, whether to enable pdbc support, [  --enable-pdbc           Enable pdbc support])

if test "$PHP_PDBC" != "no"; then

  PDBC_CLASSES="\
    pdbc_driver.c \
    pdbc_db_metadata.c \
    pdbc_resultset.c \
    pdbc_stmt.c \
    pdbc_exceptions.c \
    pdbc_connection.c \
  ";

  PDBC_CFLAGS="-Wall -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1"

  PHP_NEW_EXTENSION(pdbc, pdbc.c $PDBC_CLASSES, $ext_shared,, $PDBC_CFLAGS)
  PHP_INSTALL_HEADERS(ext/pdbc, [php_pdbc.h pdbc_types.h pdbc_exceptions.h])
fi
