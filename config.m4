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
  dnl Write more examples of tests here...

  dnl # --with-pdbc -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pdbc.h"  # you most likely want to change this
  dnl if test -r $PHP_PDBC/$SEARCH_FOR; then # path given as parameter
  dnl   PDBC_DIR=$PHP_PDBC
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pdbc files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PDBC_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PDBC_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pdbc distribution])
  dnl fi

  dnl # --with-pdbc -> add include path
  dnl PHP_ADD_INCLUDE($PDBC_DIR/include)

  dnl # --with-pdbc -> check for lib and symbol presence
  dnl LIBNAME=pdbc # you may want to change this
  dnl LIBSYMBOL=pdbc # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PDBC_DIR/$PHP_LIBDIR, PDBC_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PDBCLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pdbc lib version or lib not found])
  dnl ],[
  dnl   -L$PDBC_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PDBC_SHARED_LIBADD)

  PDBC_CLASSES="\
    pdbc_driver.c \
    pdbc_connection.c \
  ";

  PHP_NEW_EXTENSION(pdbc, pdbc.c $PDBC_CLASSES, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
