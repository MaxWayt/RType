#include "Client.h"
#include "Opcodes.h"
#include "Player.hh"
#include "DisplayManager.hh"
#include <iostream>

void Client::HandleGreeting(Packet* recvPkt)
{
    Packet pkt(CMSG_PLAYER_KEY);
    pkt << uint32(_clientKey);

    UDPSend(pkt);
}

void Client::HandleConnectResult(Packet* recvPkt)
{
    uint8 result;
    *recvPkt >> result;
    if (result != CONNECT_OK)
    {
        std::cerr << "Fail to auth with serveur" << std::endl;
        return;
    }

    std::cout << "Successfull authed" << std::endl;
    uint32 playerId;
    *recvPkt >> playerId;

    _player = new Player(DisplayManager::GetFileForClientId(playerId), 100, 550, 5, true, (int)playerId);
    _display->AddPlayer(_player);
}

void Client::HandlePlayerPosition(Packet* recvPkt)
{
    uint32 playerId;
    float x, y;
    *recvPkt >> playerId;
    *recvPkt >> x >> y;

    DamnCute::APlayer* player = _display->GetPlayer(playerId);
    if (player)
        player->getPlayer().setPosition(x, y);
}

void Client::HandleAddPlayer(Packet* recvPkt)
{
    uint32 playerId;
    float x, y;
    uint8 fire;
    *recvPkt >> playerId;
    *recvPkt >> x >> y;
    *recvPkt >> fire;

    Player* player = new Player(DisplayManager::GetFileForClientId(playerId), x, y, 5, false, (int)playerId);
    _display->AddPlayer(player);
    player->SetFire(fire != 0);
}

void Client::HandleRemovePlayer(Packet* recvPkt)
{
    uint32 playerId;
    *recvPkt >> playerId;

    if (Player* player = _display->GetPlayer(playerId))
    {
        if (player == _player)
            return;
        _display->RemovePlayer(player);
    }

}


void Client::HandlePlayerShot(Packet* recvPkt)
{
    uint32 playerId;
    uint8 active, level;
    *recvPkt >> playerId >> active;
    
    if (Player* player = _display->GetPlayer(playerId))
        player->SetFire(active != 0);

    std::cout << "Player " << playerId << " SHOT" << std::endl;
}
