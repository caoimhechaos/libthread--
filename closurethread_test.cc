/**
 * Tests for the simple thread implementation.
 */

#include <gtest/gtest.h>

#include "threadpool.h"

namespace threadpp
{
namespace testing
{
class TestFoo
{
public:
	TestFoo(QMutex* mtx, bool* has_run, QWaitCondition* done)
	: mtx_(mtx), has_run_(has_run), done_(done)
	{
	}

	void TestBody()
	{
		QMutexLocker l(mtx_);
		*has_run_ = true;
		done_->wakeAll();
	}

protected:
	QMutex* mtx_;
	bool* has_run_;
	QWaitCondition* done_;
};

class ClosureThreadTest : public ::testing::Test
{
};

TEST_F(ClosureThreadTest, DoesRun)
{
	QMutex mtx;
	QWaitCondition done;
	bool has_run;
	TestFoo foo(&mtx, &has_run, &done);

	// Lock the done mutex to ensure we won't get the notification before
	// we're running wait().
	mtx.lock();

	ClosureThread t(google::protobuf::NewCallback(
				&foo, &TestFoo::TestBody));
	ClosureThread::Yield();
	done.wait(&mtx);
	EXPECT_TRUE(has_run);
}

}  // namespace testing
}  // namespace threadpp
