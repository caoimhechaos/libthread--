/*-
 * Copyright (c) 2012 Tonnerre Lombard <tonnerre@ancient-solutions.com>,
 *                    Ancient Solutions. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions  of source code must retain  the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions  in   binary  form  must   reproduce  the  above
 *    copyright  notice, this  list  of conditions  and the  following
 *    disclaimer in the  documentation and/or other materials provided
 *    with the distribution.
 *
 * THIS  SOFTWARE IS  PROVIDED BY  ANCIENT SOLUTIONS  AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO,  THE IMPLIED WARRANTIES OF  MERCHANTABILITY AND FITNESS
 * FOR A  PARTICULAR PURPOSE  ARE DISCLAIMED.  IN  NO EVENT  SHALL THE
 * FOUNDATION  OR CONTRIBUTORS  BE  LIABLE FOR  ANY DIRECT,  INDIRECT,
 * INCIDENTAL,   SPECIAL,    EXEMPLARY,   OR   CONSEQUENTIAL   DAMAGES
 * (INCLUDING, BUT NOT LIMITED  TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE,  DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT  LIABILITY,  OR  TORT  (INCLUDING NEGLIGENCE  OR  OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "threadpool.h"

#include <QtCore/QString>
#include <pthread.h>

namespace threadpp
{
ThreadError::ThreadError(int err)
: err_(err)
{
}

QString
ThreadError::String()
{
	char buf[128];
	strerror_r(err_, buf, 128);
	return QString(buf);
}

void*
Thread::CallHelper(void *thread)
{
	Thread* t = static_cast<Thread*>(thread);
	t->Run();
	return NULL;
}

Thread::Thread()
: cancelled_(false)
{
}

Thread*
Thread::Start()
{
	int err;
	pthread_attr_t attr;
	err = pthread_attr_init(&attr);
	if (err)
		throw new ThreadError(err);
	err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	if (err)
		throw new ThreadError(err);
	err = pthread_create(&thread_, &attr, &Thread::CallHelper, this);
	if (err)
		throw new ThreadError(err);
	err = pthread_attr_destroy(&attr);
	if (err)
		throw new ThreadError(err);

	return this;
}

void
Thread::WaitForFinished()
{
	pthread_join(thread_, NULL);
}

Thread::~Thread()
{
}

void
Thread::Cancel()
{
	cancelled_ = true;
}

bool
Thread::IsCancelled()
{
	return cancelled_;
}

void
Thread::Yield()
{
	pthread_yield();
}
}  // namespace threadpp
