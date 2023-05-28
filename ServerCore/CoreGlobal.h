#pragma once

//전역으로 사용할 매니저류의 클래스들을 여기 넣음
//매니저 클래스들의 생성순서랑 삭제순서를
//맞춰줘야 할 수 있어서 여기서 조절해줌.

extern class ThreadManager* GThreadManager;

class CoreGlobal
{
public:
	CoreGlobal();
	~CoreGlobal();

};

