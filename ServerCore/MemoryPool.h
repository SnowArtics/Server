#pragma once

enum
{
	SLIST_ALIGNMENT = 16
};

/*----------------------------
|		MemoryHeader
-------------------------------*/

DECLSPEC_ALIGN(SLIST_ALIGNMENT)
struct MemoryHeader : public SLIST_ENTRY
{
	int32 allocSize;

	// [MemoryHeader] [Data]
	MemoryHeader(int32 size) : allocSize(size) {}
	
	static void* AttachHeader(MemoryHeader* header, int32 size)
	{
		new(header)MemoryHeader(size);//placement new
		return reinterpret_cast<void*>(++header);
	}

	static MemoryHeader* DetachHeader(void* ptr)
	{
		MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr) - 1;
		return header;
	}

	// TODO : 필요한 추가 정보
};

/*------------------------------
|		MemoryPool
-------------------------------*/

DECLSPEC_ALIGN(SLIST_ALIGNMENT)
class MemoryPool
{
private:
	SLIST_HEADER		_header;
	int32				_allocSize = 0;	//이 메모리 풀이 관리하는 메모리의 크기
	atomic<int32>		_useCount = 0;	//이 메모리 풀이 관리하는 메모리의 개수
	atomic<int32>		_reserveCount = 0;	//이 메모리 풀의 메모리가 사용되는 개수

public:
	MemoryPool(int32 allocSize);//이 메모리 풀이 담당하는 메모리의 크기를 넣어준다.
	~MemoryPool();

	void						Push(MemoryHeader* ptr);//메모리를 사용하지 않으면 메모리 풀에 넣어준다
	MemoryHeader*	Pop();//메모리를 사용할려고 하면 메모리 풀에서 꺼내 간다.
};

