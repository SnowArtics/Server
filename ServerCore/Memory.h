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
		// ~1024���� 32����, ~2048������ 128����, ~4096������ 256����
		//�� �޸� Ǯ�� ������ ���Ѵ�.
		POOL_COUNT = (1024/32)+(1024/128)+(2048/256),
		//4096�� ũ�⸦ �Ѵ� �޸��� ���, �ʹ� Ŀ�� �׳� �˾Ƽ� ����ϰԲ� �Ѵ�.
		MAX_ALLOC_SIZE = 4096
	};

private:
	vector<MemoryPool*> _pools;

	//�޸� ũ�⸦ ���� �޸� Ǯ�� ã��,
	//O(1)�ð����� ������ ã�� ���� ���̺� ����
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
	new(memory)Type(forward<Args>(args)...);//�Ҵ�� �޸𸮿� �ִ� ��ü�� �����ڸ� ȣ��
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