#pragma once
#include <stack>
#include <map>
#include <vector>
#include <set>

/*-------------------
|	DeadLockProfiler
--------------------*/

class DeadLockProfiler
{
private:
	unordered_map<const char*, int32>	_nameToId;
	unordered_map<int32, const char*>	_idToName;
	stack<int32>						_lockStack;
	map<int32, set<int32>>				_lockHistory;

	Mutex _lock;

private:
	vector<int32>	_discoveredOrder; // 노드가 발견된 순서를 기록하는 배열
	int32			_discoveredCount = 0; // 노드가 발견된 순서를 추적하는 카운터
	vector<bool>	_finished;			//Dfs(i)가 종료되었는지 여부
	vector<int32>	_parent;			//발견된 나의 부모님이 누구인가.

public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();

private:
	void Dfs(int32 index);

};

