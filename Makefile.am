TESTS=				threadqueue_test closurethread_test	\
				thread_test workerthread_test		\
				threadpool_test
check_PROGRAMS=			${TESTS}
lib_LTLIBRARIES=		libthread++.la
threadppdir=			${includedir}/thread++
threadpp_HEADERS=		threadpool.h

libthread___la_SOURCES=	closurethread.cc threadqueue.cc threadpool.cc	\
			workerthread.cc thread.cc
libthread___la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libthread___la_LIBADD=	${AC_LIBS}

${TESTS}:		LDADD="${GTEST_LIBS} ${PROTO_LIBS} ${lib_LTLIBRARIES}"
