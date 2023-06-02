#pragma once
#include "Types.h"

/*--------------
|	RW SpinLock
---------------*/

/*---------------------------------------------
| [WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
| W : WriteFlag (Exclusive Lock Owner ThreadId)
| R : ReadFlag (Shared Lock Count)
----------------------------------------------*/

//이 프로젝트의 정책
// W -> R (O) //동일 쓰레드가 쓰기 후 읽기 가능
// R -> W (X) //동일 쓰레드가 읽기 후 쓰기 불가능
class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000,
	};

private:
	Atomic<uint32> _lockFlag = EMPTY_FLAG; //현재 Lock이 어떤 방식으로 걸려있는지 체크
	uint16 _writeCount = 0; //Lock을 잡은 쓰레드가 동일 할 때마다 count 증가

public:
	void WriteLock(const char* name);
	void WriteUnlock(const char* name);
	void ReadLock(const char* name);
	void ReadUnlock(const char* name);
};


/*---------------
|	LockGuards
-----------------*/

//RAII 패턴
class ReadLockGuard
{
private:
	Lock& _lock;
	const char* _name;

public:
	ReadLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.ReadLock(name); }
	~ReadLockGuard() { _lock.ReadUnlock(_name); }

};

class WriteLockGuard
{
private:
	Lock& _lock;
	const char* _name;

public:
	WriteLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.WriteLock(name); }
	~WriteLockGuard() { _lock.WriteUnlock(_name); }

};

