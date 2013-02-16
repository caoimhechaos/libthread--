/**
 * Tests for the simple thread implementation.
 */

#include <gtest/gtest.h>
#include <condition_variable>

#include "threadpool.h"

namespace threadpp
{
namespace testing
{
class TestFoo
{
public:
	TestFoo(mutex* mtx, bool* has_run, condition_variable* done)
	: mtx_(mtx), has_run_(has_run), done_(done)
	{
	}

	void TestBody()
	{
		unique_lock<mutex> l(*mtx_);
		*has_run_ = true;
		done_->notify_all();
	}

protected:
	mutex* mtx_;
	bool* has_run_;
	condition_variable* done_;
};

class ClosureThreadTest : public ::testing::Test
{
};

TEST_F(ClosureThreadTest, DoesRun)
{
	mutex mtx;
	condition_variable done;
	bool has_run = false;
	TestFoo foo(&mtx, &has_run, &done);

	// Lock the done mutex to ensure we won't get the notification before
	// we're running wait().
	unique_lock<mutex> l(mtx);

	ClosureThread t(google::protobuf::NewCallback(
				&foo, &TestFoo::TestBody));
	t.Start();
	ClosureThread::Yield();
	done.wait(l);
	EXPECT_TRUE(has_run);
}

}  // namespace testing
}  // namespace threadpp
