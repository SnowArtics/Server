#pragma once

/*----------------------------
|		MemoryHeader
-------------------------------*/

struct MemoryHeader
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

	// TODO : �ʿ��� �߰� ����
};

/*------------------------------
|		MemoryPool
-------------------------------*/

class MemoryPool
{
private:
	int32 _allocSize = 0;	//�� �޸� Ǯ�� �����ϴ� �޸��� ũ��
	atomic<int32> _allocCount = 0;	//�� �޸� Ǯ�� �����ϴ� �޸��� ����

	USE_LOCK; //Lock�� ����� ���̴�.
	queue<MemoryHeader*> _queue;//_queue�� �޸� Ǯ�� ���� ������.

public:
	MemoryPool(int32 allocSize);//�� �޸� Ǯ�� ����ϴ� �޸��� ũ�⸦ �־��ش�.
	~MemoryPool();

	void						Push(MemoryHeader* ptr);//�޸𸮸� ������� ������ �޸� Ǯ�� �־��ش�
	MemoryHeader*	Pop();//�޸𸮸� ����ҷ��� �ϸ� �޸� Ǯ���� ���� ����.
};

