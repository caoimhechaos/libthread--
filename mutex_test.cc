/**
 * Test for the basic mutex functionality.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mutex.h"

namespace threadpp
{
namespace testing
{
using ::testing::Return;

class MockMutex : public Mutex
{
public:
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(TryLock, bool());
	MOCK_METHOD0(Unlock, void());
};

class MockReadWriteMutex : public ReadWriteMutex
{
public:
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(ReadLock, void());
	MOCK_METHOD0(TryLock, bool());
	MOCK_METHOD0(TryReadLock, bool());
	MOCK_METHOD0(Unlock, void());
};

class MutexTest : public ::testing::Test
{
};

TEST_F(MutexTest, TestMutexLock)
{
	MockMutex mtx;

	EXPECT_CALL(mtx, Lock())
		.WillOnce(Return());
	EXPECT_CALL(mtx, Unlock())
		.WillOnce(Return());

	MutexLock l(&mtx);
}

TEST_F(MutexTest, TestMutexLockOnRWMutex)
{
	MockReadWriteMutex mtx;

	EXPECT_CALL(mtx, Lock())
		.WillOnce(Return());
	EXPECT_CALL(mtx, Unlock())
		.WillOnce(Return());

	MutexLock l(&mtx);
}

TEST_F(MutexTest, TestReadMutexLock)
{
	MockReadWriteMutex mtx;

	EXPECT_CALL(mtx, ReadLock())
		.WillOnce(Return());
	EXPECT_CALL(mtx, Unlock())
		.WillOnce(Return());

	ReadMutexLock l(&mtx);
}
}  // namespace testing
}  // namespace threadpp
