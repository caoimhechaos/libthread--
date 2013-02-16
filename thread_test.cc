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
	TestThread(mutex* mtx, condition_variable* done)
	: done_(done), mtx_(mtx), has_run_(false) {}

	bool HasRun() {
		return has_run_;
	}

protected:
	virtual void Run() {
		unique_lock<mutex> l(*mtx_);
		Yield();
		has_run_ = true;
		done_->notify_all();
	}

	condition_variable* done_;
	mutex* mtx_;
	bool has_run_;
};

class ThreadTest : public ::testing::Test
{
};

TEST_F(ThreadTest, DoesRun)
{
	mutex mtx;
	condition_variable done;

	// Lock the done mutex to ensure we won't get the notification before
	// we're running wait().
	unique_lock<mutex> l(mtx);

	TestThread t(&mtx, &done);
	t.Start();
	Thread::Yield();
	done.wait(l);
	EXPECT_TRUE(t.HasRun());
}

}  // namespace testing
}  // namespace threadpp
