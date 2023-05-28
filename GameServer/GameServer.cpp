// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include "ThreadManager.h"

using namespace std;

CoreGlobal Core;

void ThreadMain() {
	while (true)
	{
		cout << "Hello! I am Thread..." << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

int main()
{
	for (int32 i = 0; i < 5; i++) {
		GThreadManager->Launch(ThreadMain);
	}
	GThreadManager->Join();
}


