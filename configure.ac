AC_PREREQ([2.71])
AC_INIT([badml], [0.1], [jonas.brandstoetter@gmx.at])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_LANG([C])

AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PATH_PROG([CLANG_TIDY], [clang-tidy], [true])
AS_IF([test "x$CLANG_TIDY" = xtrue],
      [AC_MSG_WARN([clang-tidy not found in PATH])])
PKG_CHECK_MODULES([CHECK], [check >= 0.15.2])

AC_SUBST([AM_CFLAGS], ["-Wall -Wextra -Werror"])
AC_TYPE_SIZE_T
AC_CHECK_FUNCS([strerror])

AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_PROG_AR

LT_INIT

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AX_VALGRIND_CHECK
AX_CODE_COVERAGE
AC_OUTPUT
