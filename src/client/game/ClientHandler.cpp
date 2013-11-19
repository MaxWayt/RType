#include "Client.h"
#include "Opcodes.h"
#include "Player.hh"
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

    uint32 playerId;
    *recvPkt >> playerId;

    DamnCute::APlayer* player = new Player<0>("../resources/ship_red.png", 100, 550);
    _display->AddPlayer(player, playerId);

    UpdatePlayerPosition();
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
    *recvPkt >> playerId;
    *recvPkt >> x >> y;

    DamnCute::APlayer* player = new Player<1>("../resources/ship_blue.png", x, y);
    _display->AddPlayer(player, playerId);
}

void Client::HandleRemovePlayer(Packet* recvPkt)
{

}
