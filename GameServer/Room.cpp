#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

shared_ptr<Room> GRoom = make_shared<Room>();

void Room::Enter(PlayerRef player)
{
	_players[player->playerId] = player;
}

void Room::Leave(PlayerRef player)
{
	_players.erase(player->playerId);
}

void Room::Broadcast(SendBufferRef sendBuffer, PlayerRef player)
{
	for (auto& p : _players)
	{
		if (player != nullptr && player->playerId != p.second->playerId)
			p.second->ownerSession->Send(sendBuffer);
	}
}