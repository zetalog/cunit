#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(cunit, 0.8)
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
if test x$GCC = xyes ; then
    CFLAGS="$CFLAGS -fms-extensions"
fi
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([malloc.h stdlib.h stdarg.h time.h sys/types.h errno.h string.h sys/timeb.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([ftime memset malloc vsnprintf strdup strerror])

AC_PROG_RANLIB
AC_PROG_INSTALL
AC_OUTPUT(Makefile include/Makefile lib/Makefile src/Makefile src/sample/Makefile)
