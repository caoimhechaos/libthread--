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

#ifndef INCLUDED_LIBTHREADPP_MUTEX_H
#define INCLUDED_LIBTHREADPP_MUTEX_H

namespace threadpp
{
// Represents a mutually exclusive lock which can be locked only by one user at
// a time.
class Mutex
{
public:
	virtual ~Mutex();

	// Obtains an exclusive lock for the resource protected by the mutex.
	// This will prevent anyone else from obtaining the lock until the
	// holder calls Unlock(). This will block until all other locks have
	// been released and the resource is definitely locked by the caller.
	virtual void Lock() = 0;

	// Attempts to obtain the exclusive lock. If the lock is currently
	// held, returns immediately. Returns true if the lock has been
	// obtained, false otherwise.
	virtual bool TryLock() = 0;

	// Releases the exclusive lock on the resource.
	virtual void Unlock() = 0;

	// Creates a new mutex lock of an appropriate type for the system the
	// program is running on.
	static Mutex* Create();
};

// Object representing a lock on a given mutex. When the object is created,
// it obtains an exclusive lock on the mutex, which will be released when
// the object is deleted.
class MutexLock
{
public:
	// Lock the mutex given as "mtx".
	MutexLock(Mutex* mtx);

	// Release the lock on the mutex.
	virtual ~MutexLock();

private:
	Mutex* mtx_;
};

// A read-write mutex, or shared mutex, is a special type of mutex which
// allows an arbitrarily large number of readers to lock an object at the
// same time, and just one writer to lock it exclusively. While the writer
// is holding the exclusive lock, no readers can hold shared locks, and vice
// versa.
class ReadWriteMutex : public Mutex
{
public:
	virtual ~ReadWriteMutex();

	// Obtain a shared lock for the mutex, rather than an exclusive lock.
	// This will block if an exclusive lock is being held.
	virtual void ReadLock() = 0;

	// Try to obtain a shared lock for the mutex. If it is currently
	// exclusively locked, this wil return false, otherwise it will obtain
	// a shared lock and return true.
	virtual bool TryReadLock() = 0;

	// Creates a new mutex lock of an appropriate type for the system the
	// program is running on.
	static ReadWriteMutex* Create();
};

// Object representing a read lock on a given read-write mutex. When the
// object is created, it obtains a shared lock on the mutex, which will be
// released when the object is deleted.
class ReadMutexLock
{
public:
	// Lock the mutex given as "mtx".
	ReadMutexLock(ReadWriteMutex* mtx);

	// Release the lock on the mutex.
	virtual ~ReadMutexLock();

private:
	ReadWriteMutex* mtx_;
};
}  // namespace threadpp

#endif /* INCLUDED_LIBTHREADPP_MUTEX_H */
