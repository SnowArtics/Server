#pragma once

#include <thread>
#include <functional>

/*---------------------
|	Thread Manager
----------------------*/

class ThreadManager
{
private:
	//�Ŵ����� lock
	Mutex _lock;
	//�Ŵ����� ����ִ� ������ ���
	vector<thread> _threads;


public:
	ThreadManager();
	~ThreadManager();

	//�Լ��� �޾Ƽ� �������ش�.
	void Launch(function<void(void)> callback);
	//�����尡 ������ �ʰ� join���ش�.
	void Join();

	//�������� TLS �ʱ�ȭ
	static void InitTLS();
	//�������� TLS ����
	static void DestoryTLS();

};

