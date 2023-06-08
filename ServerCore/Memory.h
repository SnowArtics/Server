#pragma once

#include "Allocator.h"

class MemoryPool;

/*-------------------------------------
|			Memory
---------------------------------------*/

class Memory
{
	enum
	{
		// ~1024까지 32단위, ~2048까지는 128단위, ~4096까지는 256단위
		//총 메모리 풀의 개수를 말한다.
		POOL_COUNT = (1024/32)+(1024/128)+(2048/256),
		//4096의 크기를 넘는 메모리일 경우, 너무 커서 그냥 알아서 사용하게끔 한다.
		MAX_ALLOC_SIZE = 4096
	};

private:
	vector<MemoryPool*> _pools;

	//메모리 크기를 통해 메모리 풀을 찾고,
	//O(1)시간으로 빠르게 찾기 위한 테이블 생성
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];

public:
	Memory();
	~Memory();

	void* Allocate(int32 size);
	void Release(void* ptr);
};


template<typename Type, typename... Args>
Type* xnew(Args&&... args) {
	Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));

	//placement new
	new(memory)Type(forward<Args>(args)...);//할당된 메모리에 있는 객체의 생성자를 호출
	return memory;
}

template<typename Type>
void xdelete(Type* obj) {
	obj->~Type();
	PoolAllocator::Release(obj);
}

template<typename Type>
shared_ptr<Type> MakeShared()
{
	return shared_ptr<Type> {xnew<Type>(), xdelete<Type>};
}