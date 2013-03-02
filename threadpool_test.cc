/**
 * Tests for the simple thread implementation.
 */

#include <gtest/gtest.h>
#include <condition_variable>
#include <iostream>

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
		l.unlock();
		done_->notify_all();
	}

protected:
	mutex* mtx_;
	bool* has_run_;
	condition_variable* done_;
};

class ThreadPoolTest : public ::testing::Test
{
};

TEST_F(ThreadPoolTest, DoesRun)
{
	mutex mtx;
	condition_variable done;
	bool has_run = false;
	TestFoo foo(&mtx, &has_run, &done);

	// Lock the done mutex to ensure we won't get the notification before
	// we're running wait().
	unique_lock<mutex> l(mtx);

	ThreadPool t(1);
	t.Add(google::protobuf::NewCallback(&foo, &TestFoo::TestBody));
	EXPECT_NE(std::cv_status::timeout,
			done.wait_for(l, std::chrono::seconds(10)));
	EXPECT_TRUE(has_run);
}

}  // namespace testing
}  // namespace threadpp
