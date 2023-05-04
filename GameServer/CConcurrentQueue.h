#pragma once

#include<mutex>

template <typename T>
class LockQueue {
private:
	queue<T> m_qQueue;
	mutex m_mMutex;
	condition_variable m_cvCondVar;

public:
	LockQueue() {}

	LockQueue(const LockQueue&) = delete;
	LockQueue& operator = (const LockQueue&) = delete;


public:
	void Push(T _value) {
		lock_guard<mutex> lock(m_mMutex);
		m_qQueue.push(move(_value));
		m_cvCondVar.notify_one();
	}

	bool TryPop(T& _value) {
		lock_guard<mutex> lock(m_mMutex);
		
		if (m_qQueue.empty())
			return false;

		_value = move(m_qQueue.front());
		m_qQueue.pop();
		return true;
	}

	bool Empty() {
		lock_guard<mutex> lock(m_mMutex);

		return m_qQueue.empty();
	}

	void WaitPop(T& _value) {
		unique_lock<mutex> lock(m_mMutex);
		m_cvCondVar.wait(lock, [this]() {return !m_qQueue.empty(); });
		_value = move(m_qQueue.front());
		m_qQueue.pop();
	}
};

