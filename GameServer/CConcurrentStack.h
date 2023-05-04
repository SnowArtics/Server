#pragma once

#include <mutex>

template<typename T>
class LockStack 
{
private:
	stack<T> m_sStack;
	mutex m_mMutex;
	condition_variable m_cvCondVar;

public:
	LockStack() {};

	LockStack(const LockStack&) = delete;
	LockStack& operator = (const LockStack&) = delete;

public:
	void Push(T _value) {
		lock_guard<mutex> lock(m_mMutex);
		m_sStack.push(move(_value));
		m_cvCondVar.notify_one();
	}

	bool TryPop(T& _value) {
		lock_guard<mutex> lock(m_mMutex);
		if(m_sStack.empty())
			return false;

		_value = std::move(m_sStack.top());
		m_sStack.pop();
		return true;
	}

	bool Empty() {
		lock_guard<mutex> lock(m_mMutex);
		return m_sStack.empty();
	}

	void WaitPop(T& _value) {
		unique_lock<mutex> lock(m_mMutex);
		m_cvCondVar.wait(lock, [this]() {return !m_sStack.empty(); });
		_value = std::move(m_sStack.pop());
		m_sStack.pop();
	}
};

template<typename T>
class LockFreeStack
{
	struct Node {
		Node(const T& value) : data(value)
		{

		}

		T data;
		Node* next;
	};

private:
	atomic<Node*> m_aHead;

public:
	// 1) �� ��带 �����
	// 2) �� ����� next = head
	// 3) head = �� ���
	void Push(const T& _value) {
		Node* node = new Node(_value);
		node->next = m_aHead;//��尡 ������ �ڿ����� nullptr�� ��.

		//�� ���̿� ��ġ�� ���ϸ�?
		//_head = node;

		while (m_aHead.compare_exchange_weak(node->next, node) == false) {
			//���Ѵ��
		}
	}

	//1) head �б�
	// 2) head->next �б�
	// 3) head = head->next
	// 4) data�����ؼ� ��ȯ
	// 5) ������ ��带 ����
	bool TryPop(T& _value) {
		Node* oldHead = m_aHead;

		while (oldHead && m_aHead.compare_exchange_weak(oldHead, oldHead->next) == false) {

		}

		if (oldHead == nullptr)
			return false;

		//Exception X
		_value = oldHead->data;

		//���� ����
		//delete oldHead;
		return true;
	}

};