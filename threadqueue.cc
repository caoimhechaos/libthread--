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

#include <google/protobuf/stubs/common.h>
#include "threadpool.h"

#include <mutex>
#include <queue>
#include <condition_variable>

namespace threadpp
{
ThreadQueue::ThreadQueue()
{
}

ThreadQueue::~ThreadQueue()
{
}

void
ThreadQueue::Add(google::protobuf::Closure* t)
{
	unique_lock<mutex> l(queue_lock_);
	queued_threads_.push(t);
	task_availability_.notify_all();
}

google::protobuf::Closure*
ThreadQueue::GetNextTask()
{
	unique_lock<mutex> l(queue_lock_);
	google::protobuf::Closure* ret;

	while (queued_threads_.empty())
		task_availability_.wait(l);

	ret = queued_threads_.front();
	queued_threads_.pop();
	return ret;
}

void
ThreadQueue::WaitUntilEmpty()
{
	queue_lock_.lock();

	while (!queued_threads_.empty())
	{
		queue_lock_.unlock();
		queue_lock_.lock();
	}

	queue_lock_.unlock();
}

void
ThreadQueue::Clear()
{
	unique_lock<mutex> l(queue_lock_);
	while (!queued_threads_.empty())
		queued_threads_.pop();
}
}  // namespace threadpp
