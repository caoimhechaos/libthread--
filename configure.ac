#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libtoolbox], [0.9.1], [caoimhechaos@protonmail.com])
AC_CONFIG_SRCDIR([threadpool.h])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE
LT_INIT

AC_ARG_WITH([qt-includes], [AC_HELP_STRING([--with-qt-includes=DIR],
	    [Path to the QT headers])], [INCLUDES="$INCLUDES -I${withval}"])
AC_ARG_WITH([qt-libs], [AC_HELP_STRING([--with-qt-libs=DIR],
	    [Path to the QT libraries])],
	    LDFLAGS="${LDFLAGS} -L${withval} -L${withval}"])
AC_SUBST(INCLUDES)
AC_SUBST(LDFLAGS)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL
AC_LANG(C++)

LIBRARY_VERSION=`echo $VERSION | $SED -e's/\.//g' -e's/^0*//g'`:0:0
AC_SUBST(LIBRARY_VERSION)

OLDCXXFLAGS="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -std=c++11"
AC_MSG_CHECKING([whether $CXX accepts -std=c++11])
AC_LINK_IFELSE([AC_LANG_CALL([], [main])], [AC_MSG_RESULT(yes)], [
		AC_MSG_RESULT(no)
		CXXFLAGS="$OLDCXXFLAGS -std=c++0x"
		AC_MSG_CHECKING([whether $CXX accepts -std=c++0x])
		AC_LINK_IFELSE([AC_LANG_CALL([], [main])],
			       [AC_MSG_RESULT(yes)],
			       [AC_MSG_RESULT(no); CXXFLAGS="$OLDCXXFLAGS"])
		])
unset OLDCXXFLAGS
CXXFLAGS="${CXXFLAGS}"
AC_SUBST(CXXFLAGS)

# Checks for libraries.
GTEST_LIBS=""
QT_LIBS=""
PROTO_LIBS=""
PTHREAD_LIBS=""
AC_CHECK_LIB([gtest], [main],
	     [GTEST_LIBS="$GTEST_LIBS -lgtest"])
old_LIBS="$LIBS"
LIBS="$LIBS $GTEST_LIBS"
AC_CHECK_LIB([gmock], [main],
	     [GTEST_LIBS="$GTEST_LIBS -lgmock"])
AC_CHECK_LIB([gtest_main], [main],
	     [GTEST_LIBS="$GTEST_LIBS -lgtest_main"])
LIBS="$old_LIBS"
AC_CHECK_LIB([QtCore], [main],
	     [QT_LIBS="$QT_LIBS -lQtCore"])
AC_CHECK_LIB([QtNetwork], [main],
	     [QT_LIBS="$QT_LIBS -lQtNetwork"])
AC_CHECK_LIB([protobuf], [main],
	     [PROTO_LIBS="$PROTO_LIBS -lprotobuf"])
AC_CHECK_LIB([pthread], [main],
	     [PTHREAD_LIBS="$PTHREAD_LIBS -lpthread"])
AC_LIBS="$AC_LIBS $QT_LIBS $PROTO_LIBS $PTHREAD_LIBS"
AC_SUBST(GTEST_LIBS)
AC_SUBST(QT_LIBS)
AC_SUBST(AC_LIBS)
AC_SUBST(PROTO_LIBS)

# Checks for header files.
old_CPPFLAGS="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $INCLUDES"
AC_CHECK_HEADERS([QtCore/QMap QtCore/QString])
CPPFLAGS="$old_CPPFLAGS"

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT32_T

# Checks for library functions.
orig_LIBS="$LIBS"
LIBS="$LIBS $PTHREAD_LIBS"
AC_CHECK_FUNCS(pthread_yield)
LIBS="$orig_LIBS"

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
