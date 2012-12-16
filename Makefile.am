TESTS=				
check_PROGRAMS=			${TESTS}
lib_LTLIBRARIES=		libthread++.la
threadppdir=			${includedir}/thread++
threadpp_HEADERS=		threadpool.h

libthread___la_SOURCES=	threadqueue.cc threadpool.cc workerthread.cc thread.cc
libthread___la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libthread___la_LIBADD=	${AC_LIBS}
