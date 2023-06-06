#pragma once

/*-------------------
	BaseAllocator
-------------------*/

class BaseAllocator
{
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};


/*-----------------------------------------
|			StompAllocator
-----------------------------------------*/
//메모리 오류를 잡는데 쓴다.

class StompAllocator {

	enum { PAGE_SIZE = 0x1000 };

public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};

/*-----------------------------------------
|			PoolAllocator
-----------------------------------------*/
//메모리 풀링을 사용하는데 쓸 Allocator이다.

class PoolAllocator {
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};

/*-----------------------------------------
|		STL Allocator
-------------------------------------------*/

template<typename T>
class STLAllocator {
public:
	using value_type = T;

	STLAllocator() {}

	template<typename Other>
	STLAllocator(const STLAllocator<Other>&) {}

	T* allocate(size_t count) 
	{
		const int32 size = static_cast<int32>(count * sizeof(T));
		return static_cast<T*>(xalloc(size));
	}

	void deallocate(T* ptr, size_t count)
	{
		xrelease(ptr);
	}
};