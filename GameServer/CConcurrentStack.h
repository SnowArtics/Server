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
	atomic<uint32> m_aPopCount = 0; // Pop을 실행중인 쓰레드의 개수
	atomic<Node*> m_aPendingList; //삭제 되어야 할 노드들(첫번째만 기억)

public:
	// 1) 새 노드를 만들고
	// 2) 새 노드의 next = head
	// 3) head = 새 노드
	void Push(const T& _value) {
		Node* node = new Node(_value);
		node->next = m_aHead;//헤드가 없으면 자연스레 nullptr이 들어감.

		//이 사이에 새치기 당하면?
		//_head = node;

		while (m_aHead.compare_exchange_weak(node->next, node) == false) {
			//무한대기
		}
	}

	//1) head 읽기
	// 2) head->next 읽기
	// 3) head = head->next
	// 4) data추출해서 반환
	// 5) 추출한 노드를 삭제
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

		//삭제 보류
		//delete oldHead;
		return true;
	}

	// 1) 데이터 분리
	// 2) Count 체크
	// 3) 나 혼자면 삭제
	void TryDelete(Node* oldHead) {
		//나 외에 팝을 시도하는 쓰레드가 있는가?
		if (m_aPopCount==1) {
			//나 혼자네?
			//데이터를 분리 했기 때문에 (head는 뒤로 갔고, 제일 앞자리 원소는 이 쓰레드가 이미 가지고 있음)
			//그래서 바로 삭제 가능

			//나의 데이터는 삭제
			delete oldHead;

			//이왕 혼자인거 삭제 예약된 다른 데이터들도(pending list) 삭제하기
			Node* node = m_aPendingList.exchange(nullptr);
			//근데 pending list도 이미 누가 건드리고 있을 수 있어서 내가 삭제할 수 있는지 체크해줘야함
			// 1) 데이터 분리, 2) Count 체크, 3) 나 혼자면 삭제 3가지 순서를 또 지키면서 시도해보자.			

			if (--m_aPopCount == 0) {//아직도 이 쓰레드에 나 혼자만 있다면
				//중간에 끼어든 애가 없다면 삭제 진행
				// 이제와서 누군가가 끼어들어도 어차피 데이터는 분리해둔 상태!
				DeleteNodes(node);
			}
			else if(node) {
				//누가 끼어들었으니 다시 가져다 놓자
				ChainPendingNodeList(node);
			}
		}
		else {
			//누가 있네? 그럼 지금 삭제하지 않고 pending list에 추가하자
			--m_aPopCount;
			ChainPendingNode(oldHead);
		}
	}

	//삭제할 리스트(pending list)를 기존 삭제리스트의 뒤에 연결시켜준다.
	//pending list를 삭제 못하면 다시 이어붙어줘야하기 때문에 이 함수를 만듬
	void ChainPendingNodeList(Node* first, Node* last) {
		last->next = m_aPendingList;

		while (m_aPendingList.compare_exchange_weak(last->next, first) == false) {

		}
	}
	
	//이건 첫번쨰 노드 던지면 알아서 뒷자리 찾아서 연결해줌.
	void ChainPendingNodeList(Node* node) {
		Node* last = node;
		while (last->next)
			last = last->next;

		ChainPendingNodeList(node, last);
	}

	//딱 하나짜리만 연결해줄 때(특수한 경우)
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