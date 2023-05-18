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
		Node(const T& value) : data(value), next(nullptr)
		{

		}

		T data;
		Node* next;
	};

private:
	atomic<Node*> m_aHead;
	atomic<uint32> m_aPopCount = 0; // Pop�� �������� �������� ����
	atomic<Node*> m_aPendingList; //���� �Ǿ�� �� ����(ù��°�� ���)

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
		++m_aPopCount;

		Node* oldHead = m_aHead;

		while (oldHead && m_aHead.compare_exchange_weak(oldHead, oldHead->next) == false) {

		}

		if (oldHead == nullptr) {
			--m_aPopCount;
			return false;
		}

		//Exception X
		_value = oldHead->data;
		TryDelete(oldHead);

		//���� ����
		//delete oldHead;
		return true;
	}

	// 1) ������ �и�
	// 2) Count üũ
	// 3) �� ȥ�ڸ� ����
	void TryDelete(Node* oldHead) {
		//�� �ܿ� ���� �õ��ϴ� �����尡 �ִ°�?
		if (m_aPopCount==1) {
			//�� ȥ�ڳ�?
			//�����͸� �и� �߱� ������ (head�� �ڷ� ����, ���� ���ڸ� ���Ҵ� �� �����尡 �̹� ������ ����)
			//�׷��� �ٷ� ���� ����

			//���� �����ʹ� ����
			delete oldHead;

			//�̿� ȥ���ΰ� ���� ����� �ٸ� �����͵鵵(pending list) �����ϱ�
			Node* node = m_aPendingList.exchange(nullptr);
			//�ٵ� pending list�� �̹� ���� �ǵ帮�� ���� �� �־ ���� ������ �� �ִ��� üũ�������
			// 1) ������ �и�, 2) Count üũ, 3) �� ȥ�ڸ� ���� 3���� ������ �� ��Ű�鼭 �õ��غ���.			

			if (--m_aPopCount == 0) {//������ �� �����忡 �� ȥ�ڸ� �ִٸ�
				//�߰��� ����� �ְ� ���ٸ� ���� ����
				// �����ͼ� �������� ����� ������ �����ʹ� �и��ص� ����!
				DeleteNodes(node);
			}
			else if(node) {
				//���� ���������� �ٽ� ������ ����
				ChainPendingNodeList(node);
			}
		}
		else {
			//���� �ֳ�? �׷� ���� �������� �ʰ� pending list�� �߰�����
			--m_aPopCount;
			ChainPendingNode(oldHead);
		}
	}

	//������ ����Ʈ(pending list)�� ���� ��������Ʈ�� �ڿ� ��������ش�.
	//pending list�� ���� ���ϸ� �ٽ� �̾�پ�����ϱ� ������ �� �Լ��� ����
	void ChainPendingNodeList(Node* first, Node* last) {
		last->next = m_aPendingList;

		while (m_aPendingList.compare_exchange_weak(last->next, first) == false) {

		}
	}
	
	//�̰� ù���� ��� ������ �˾Ƽ� ���ڸ� ã�Ƽ� ��������.
	void ChainPendingNodeList(Node* node) {
		Node* last = node;
		while (last->next)
			last = last->next;

		ChainPendingNodeList(node, last);
	}

	//�� �ϳ�¥���� �������� ��(Ư���� ���)
	void ChainPendingNode(Node* node) {
		ChainPendingNodeList(node);
	}

	static void DeleteNodes(Node* node) {
		while (node) {
			Node* next = node->next;
			delete node;
			node = next;
		}
	}
};