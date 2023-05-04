// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
//#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

#include <future>

#include "CConcurrentQueue.h"
#include "CConcurrentStack.h"

using namespace std;

LockQueue<int32> q;
LockFreeStack<int32> s;

void Push() {
	while (true) {
		int32 value = rand() % 100;
		s.Push(value);

		//this_thread::sleep_for(10ms);
	}
}

void Pop() {
	while (true) {
		int32 data = 0;

		//if (q.TryPop(data))
		//	cout << data << endl;

		if(s.TryPop(data))
		cout << data << endl;

	}
}

int main()
{
	thread t1(Push);
	thread t2(Pop);
	thread t3(Pop);

	t1.join();
	t2.join();
	t3.join();
}


