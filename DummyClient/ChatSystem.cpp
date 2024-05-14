#include "pch.h"
#include "ChatSystem.h"
#include "Service.h"

ChatSystem::ChatSystem()
{
}

ChatSystem::~ChatSystem()
{
}

void ChatSystem::Broadcast(SendBufferRef sendBuffer)
{
	m_pClientService->Broadcast(sendBuffer);
}
