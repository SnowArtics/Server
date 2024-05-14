#pragma once

class ChatSystem
	: public CSingleton<ChatSystem>
{
private:
	ClientServiceRef m_pClientService;

private:
	ChatSystem();
	~ChatSystem();

public:
	void SetClientService(ClientServiceRef _clientService) { m_pClientService = _clientService; }

public:
	void Broadcast(SendBufferRef sendBuffer);

	friend class CSingleton;
};

