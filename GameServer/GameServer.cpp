// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include "ThreadManager.h"

class TestLock {
	USE_LOCK;

private:
	queue<int32> _queue;

public:
	int32 TestRead() {
		READ_LOCK;
		if (_queue.empty())
			return -1;

		return _queue.front();
	}

	void TestPush() {
		WRITE_LOCK;
		_queue.push(rand() % 100);
	}

	void TestPop(){
		WRITE_LOCK;

		while(true)

		if (_queue.empty() == false)
			_queue.pop();
	}
};

TestLock testLock;

using namespace std;

void ThreadWrite() {
	while (true)
	{
		testLock.TestPush();
		this_thread::sleep_for(1ms);
		testLock.TestPop();
	}
}

void ThreadRead() {
	while (true) {
		int32 value = testLock.TestRead();
		cout << value << endl;
		this_thread::sleep_for(1ms);
	}

}

int main()
{
	for (int32 i = 0; i < 2; i++) {
		GThreadManager->Launch(ThreadWrite);
	}

	for (int32 i = 0; i < 5; i++) {
		GThreadManager->Launch(ThreadRead);
	}

	GThreadManager->Join();
}


