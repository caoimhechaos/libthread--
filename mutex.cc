/*-
 * Copyright (c) 2013 Caoimhe Chaos <caoimhechaos@protonmail.com>,
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
#endif

#include "mutex.h"

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#include "pthread_mutex.h"
#endif /* HAVE_PTHREAD_H */

#ifdef HAVE_MUTEX
#include <mutex>
#include "c++11mutex.h"
#endif /* HAVE_MUTEX */

namespace threadpp
{
Mutex::~Mutex()
{
}

Mutex*
Mutex::Create()
{
#ifdef HAVE_MUTEX
	return new Cpp11Mutex();
#else /* !HAVE_MUTEX */
#ifdef HAVE_PTHREAD_MUTEX_INIT
	return new PthreadMutex();
#endif /* HAVE_PTHREAD_MUTEX_INIT */
#endif /* HAVE_MUTEX */
}

MutexLock::MutexLock(Mutex* mtx)
: mtx_(mtx)
{
	mtx_->Lock();
}

MutexLock::~MutexLock()
{
	mtx_->Unlock();
}

ReadWriteMutex::~ReadWriteMutex()
{
}

ReadWriteMutex*
ReadWriteMutex::Create()
{
#ifdef HAVE_PTHREAD_RWLOCK_INIT
	return new PthreadReadWriteMutex();
#endif /* HAVE_PTHREAD_RWLOCK_INIT */
}

ReadMutexLock::ReadMutexLock(ReadWriteMutex* mtx)
: mtx_(mtx)
{
	mtx->ReadLock();
}

ReadMutexLock::~ReadMutexLock()
{
	mtx_->Unlock();
}
}  // namespace threadpp
