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
	google::protobuf::Closure* cl1 = NewCallback(&Empty);
	google::protobuf::Closure* cl2 = NewCallback(&Empty);
	google::protobuf::Closure* cl3 = NewCallback(&Empty);
	ThreadQueue q;
	q.Add(cl1);
	q.Add(cl2);
	q.Add(cl3);
	EXPECT_EQ(cl1, q.GetNextTask());
	EXPECT_EQ(cl2, q.GetNextTask());
	EXPECT_EQ(cl3, q.GetNextTask());
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
