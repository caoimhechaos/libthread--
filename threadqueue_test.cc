/**
 * Tests for the thread queue implementation.
 */

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "threadpool.h"

namespace threadpp
{
namespace testing
{
using google::protobuf::NewCallback;

void Empty()
{
}

class ThreadQueueTest : public ::testing::Test
{
};

TEST_F(ThreadQueueTest, AddGetTask)
{
	google::protobuf::Closure* cl = NewCallback(&Empty);
	ThreadQueue q;
	q.Add(cl);
	EXPECT_EQ(cl, q.GetNextTask());
}

TEST_F(ThreadQueueTest, WaitUntilEmpty)
{
	ThreadQueue q;
	q.WaitUntilEmpty();
}

TEST_F(ThreadQueueTest, AddClearWait)
{
	google::protobuf::Closure* cl = NewCallback(&Empty);
	ThreadQueue q;
	q.Add(cl);
	q.Clear();
	q.WaitUntilEmpty();
}



}  // namespace testing
}  // namespace threadpp
