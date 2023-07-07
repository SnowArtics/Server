// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	//밑의 함수로 소켓을 세팅할 수 있다.
	//첫번째 파라미터로는 세팅할 소켓을 넣어주자.
	//두번째 파라미터는 level인데, 옵션을 언저 어디서 해석하고 처리할지 주체를 지정한다.
	// 소켓 코드 단계 -> SOL_SOCKET
	// IPv4 단계 -> IPPROTO_IP
	// TCP 프로토콜 단계 -> IPPROTO_TCP
	//세번째 파라미터로는 lever에 맞는 추가 옵션을 넣는다. 대표적으로 알아야할 5가지를 밑에 적는다.
	//SO_KEEPALIVE, SO_LINGER, SO_RCVBUF, SO_REUSEADDR, SO_SNDBUF
	//네번째 파라미터는 세번째 파라미터의 옵션에 맞게 리턴되는 값을 받아줄 변수를 넣는다.
	//5번째는 네번째 파라미터의 길이이다.
	//::setsockopt();

	//이 함수는 현재 설정된 소켓의 옵션을 알 수 있다.
	//::getsockopt();


	// SO_KEEPALIVE = 주기적으로 연결 여부 상태 확인 (TCP Only)
	// 상대방이 소리소문없이 연결을 끊는다면?
	// 주기적으로 TCP 프로토콜 연결 상태 확인 -> 끊어진 연결 감지
	//bool enable = true;
	//::setsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&enable, sizeof(enable));

	// SO_LINGER = 지연하다
	// 연결을 끊을 때, 송신 버퍼에 있는 데이터를 보낼 것인가? 날릴 것인가?
	// onoff = 0이면, closesocket()이 바로 리턴, 아니면 linger초만큼 대기 (default 0)
	// linger = 대기시간
	//LINGER linger;
	//linger.l_onoff = 1;
	//linger.l_linger = 5;
	//::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));

	//Half-close
	// SD_SEND : send 막는다
	// SD_RECEIVE : recv 막는다.
	// SD_BOTH : 둘 다 막는다.
	//::shutdown(serverSocket, SD_SEND);
	//이렇게 하면 더 이상 이 소켓으로 SEND를 할 수 없다. 이렇게 설정하면 나는 더 보낼께 없다!는 거니까
	// 클라측에서 보고 아 더이상 버퍼에 값이 없네? 하면 나도 보낼께 없다! 하고 서로 체크하고 끊는게 우아함.

	// SO_SNDBUF = 송신 버퍼 크기
	// SO_RCVBUF = 수신 버퍼 크기

	int32 sendBufferSize;
	int32 optionLen = sizeof(sendBufferSize);
	::getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, (char*)&sendBufferSize, &optionLen);
	cout << "송신 버퍼 크기 : " << sendBufferSize << endl;

	int32 recvBufferSize;
	optionLen = sizeof(recvBufferSize);
	::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)&recvBufferSize, &optionLen);
	cout << "수신 버퍼 크기 : " << recvBufferSize << endl;

	// SO_REUSEADDR
	// IP주소 및 Port 재사용
	// 서버가 강제로 종료되거나 연결이 비정상적으로 종료되면, 소켓에 찌그레기가 남아있어서
	// 다시 사용하려면 운영체제가 그 소켓의 아이피나 포트를 풀어줘야 할 때가 있다.
	// 길게는 몇분이나 기다려야 할 수 있다. 이때, 이 옵션을 해주면 강제로 내가 점유를 뺏어올 수 있다.
	{
		bool enable = true;
		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable)); \
	}

	//GameServer.cpp

	// IPPROTO_TCP
	// TCP_NODELAY = NAGLE 네이글 알고리즘 작동 여부
	// 데이터가 충분히 크면 보내고, 그렇지 않으면 데이터가 충분히 쌓일때까지 대기!
	// 장점 : 작은 패킷이 불필요하게 많이 생성되는 일을 방지
	// 단점 : 반응시간 손해
	{
		bool enable = true;
		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable));
	}

	// 윈속 종료
	::WSACleanup();
}