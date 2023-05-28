#pragma once

#include <thread>
#include <functional>

/*---------------------
|	Thread Manager
----------------------*/

class ThreadManager
{
private:
	//매니저의 lock
	Mutex _lock;
	//매니저가 들고있는 쓰레드 목록
	vector<thread> _threads;


public:
	ThreadManager();
	~ThreadManager();

	//함수를 받아서 실행해준다.
	void Launch(function<void(void)> callback);
	//쓰레드가 끊이지 않게 join해준다.
	void Join();

	//쓰레드의 TLS 초기화
	static void InitTLS();
	//쓰레드의 TLS 삭제
	static void DestoryTLS();

};

