/**
 * Tests for the simple thread implementation.
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "threadpool.h"

namespace threadpp
{
namespace testing
{

class TestThread : public Thread
{
public:
	TestThread(QMutex* mtx, QWaitCondition* done)
	: done_(done), mtx_(mtx), has_run_(false) {}

	bool HasRun() {
		return has_run_;
	}

protected:
	virtual void Run() {
		QMutexLocker l(mtx_);
		Yield();
		has_run_ = true;
		done_->wakeAll();
	}

	QWaitCondition* done_;
	QMutex* mtx_;
	bool has_run_;
};

class ThreadTest : public ::testing::Test
{
};

TEST_F(ThreadTest, DoesRun)
{
	QMutex mtx;
	QWaitCondition done;

	// Lock the done mutex to ensure we won't get the notification before
	// we're running wait().
	mtx.lock();

	TestThread t(&mtx, &done);
	Thread::Yield();
	done.wait(&mtx);
	EXPECT_TRUE(t.HasRun());
}

}  // namespace testing
}  // namespace threadpp
