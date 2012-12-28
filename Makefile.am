TESTS=				threadqueue_test closurethread_test	\
				thread_test workerthread_test
check_PROGRAMS=			${TESTS}
lib_LTLIBRARIES=		libthread++.la
threadppdir=			${includedir}/thread++
threadpp_HEADERS=		threadpool.h

libthread___la_SOURCES=	closurethread.cc threadqueue.cc threadpool.cc	\
			workerthread.cc thread.cc
libthread___la_LDFLAGS=	-version-info ${LIBRARY_VERSION}
libthread___la_LIBADD=	${AC_LIBS}

thread_test_SOURCES=	thread_test.cc
thread_test_LDADD=	${GTEST_LIBS} ${lib_LTLIBRARIES}

closurethread_test_SOURCES=	closurethread_test.cc
closurethread_test_LDADD=	${GTEST_LIBS} ${PROTO_LIBS} ${lib_LTLIBRARIES}

threadqueue_test_SOURCES=	threadqueue_test.cc
threadqueue_test_LDADD=		${GTEST_LIBS} ${PROTO_LIBS} ${lib_LTLIBRARIES}

workerthread_test_SOURCES=	workerthread_test.cc
workerthread_test_LDADD=	${GTEST_LIBS} ${PROTO_LIBS} ${lib_LTLIBRARIES}
