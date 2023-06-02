#include "pch.h"
#include "Lock.h"
#include "CoreTLS.h"
#include "DeadLockProfiler.h"

void Lock::WriteLock(const char* name)
{
#if _DEBUG
	GDeadLockProfiler->PushLock(name);
#endif

	//동일한 쓰레드가 소유하고 있다면 무조건 성공.
	const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (LThreadId == lockThreadId) {
		_writeCount++;
		return;
	}

	//아무도 소유(쓰기) 및 공유(읽기)하고 있지 않을 때(즉, EMPTY_FLAG 일때), 경합해서 소유권을 얻는다.

	const int64 beginTick = ::GetTickCount64();
	const uint32 desired = ((LThreadId << 16) & WRITE_THREAD_MASK);
	while (true) {
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++) {
			uint32 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(OUT expected, desired)) {
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("LOCK_TIMEOUT");

		this_thread::yield();
	}
}

void Lock::WriteUnlock(const char* name)
{
#if _DEBUG
	GDeadLockProfiler->PopLock(name);
#endif
	//ReadLock 다 풀기 전에는 Write Unlock 불가능.
	//왜냐하면 정책상 쓰기락 하고 읽기락 하기 때문이다.
	if ((_lockFlag.load() & READ_COUNT_MASK) != 0)
		CRASH("INVAILD_UNLOCK_ORDER");

	const int32 lockCount = --_writeCount;

	//더 이상 이 쓰레드가 Lock을 잡고 있지 않다면
	if (lockCount == 0)
		_lockFlag.store(EMPTY_FLAG);
}

void Lock::ReadLock(const char* name)
{
#if _DEBUG
	GDeadLockProfiler->PushLock(name);
#endif

	//동일한 쓰레드가 소유하고 있다면 무조건 성공.
	//동일한 쓰레드가 소유하고 있다면 읽기를 동시에 해도 상관없으니까 증가시킨다.
	const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (LThreadId == lockThreadId) {
		_lockFlag.fetch_add(1);
		return;
	}

	//아무도 소유하고 있지 않을 때,(쓰고 있지 않을 때) 경합해서 공유 카운트를 올린다.
	const int64 beginTick = ::GetTickCount64();
	while (true) {
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++) {
			uint32 expected = (_lockFlag.load() & READ_COUNT_MASK);
			if (_lockFlag.compare_exchange_strong(OUT expected, expected + 1))
				return;
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("LOCK_TIMEOUT");

		this_thread::yield();
	}
}

void Lock::ReadUnlock(const char* name)
{
#if _DEBUG
	GDeadLockProfiler->PopLock(name);
#endif

	if ((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
		CRASH("MULTIPLE_UNLOCK");
}
