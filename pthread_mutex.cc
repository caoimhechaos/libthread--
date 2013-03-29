/*-
 * Copyright (c) 2013 Tonnerre Lombard <tonnerre@ancient-solutions.com>,
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif /* HAVE_PTHREAD_H */

#include "mutex.h"
#include "pthread_mutex.h"

namespace threadpp
{
PthreadMutex::PthreadMutex()
: mutex_(PTHREAD_MUTEX_INITIALIZER)
{
}

PthreadMutex::~PthreadMutex()
{
	pthread_mutex_destroy(&mutex_);
}

void
PthreadMutex::Lock()
{
	pthread_mutex_lock(&mutex_);
}

bool
PthreadMutex::TryLock()
{
	int err = pthread_mutex_trylock(&mutex_);
	return err == 0;
}

void
PthreadMutex::Unlock()
{
	pthread_mutex_unlock(&mutex_);
}

PthreadReadWriteMutex::PthreadReadWriteMutex()
: rwlock_(PTHREAD_RWLOCK_INITIALIZER)
{
}

PthreadReadWriteMutex::~PthreadReadWriteMutex()
{
	pthread_rwlock_destroy(&rwlock_);
}

void
PthreadReadWriteMutex::Lock()
{
	pthread_rwlock_wrlock(&rwlock_);
}

void
PthreadReadWriteMutex::ReadLock()
{
	pthread_rwlock_rdlock(&rwlock_);
}

bool
PthreadReadWriteMutex::TryLock()
{
	int err = pthread_rwlock_trywrlock(&rwlock_);
	return err == 0;
}

bool
PthreadReadWriteMutex::TryReadLock()
{
	int err = pthread_rwlock_tryrdlock(&rwlock_);
	return err == 0;
}

void
PthreadReadWriteMutex::Unlock()
{
	pthread_rwlock_unlock(&rwlock_);
}
}  // namespace threadpp
