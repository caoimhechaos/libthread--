TESTS=				threadqueue_test closurethread_test	\
				thread_test workerthread_test		\
				threadpool_test mutex_test
check_PROGRAMS=			${TESTS}
lib_LTLIBRARIES=		libthread++.la
threadppdir=			${includedir}/thread++
threadpp_HEADERS=		threadpool.h mutex.h
noinst_HEADERS=			c++11mutex.h pthread_mutex.h

libthread___la_SOURCES=	closurethread.cc threadqueue.cc threadpool.cc	\
			workerthread.cc thread.cc mutex.cc c++11mutex.cc\
			pthread_mutex.cc
libthread___la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libthread___la_LIBADD=	${AC_LIBS}

${TESTS}:		LDADD="${GTEST_LIBS} ${PROTO_LIBS} ${lib_LTLIBRARIES}"
