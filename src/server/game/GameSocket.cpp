#include "GameSocket.h"
#include "Game.h"
#include "Packet.hpp"
#include "Opcodes.h"
#include "ConfigMgr.h"

#include <iostream>

namespace Game
{

GameSocket::GameSocket(Game* game, NetService& service) : Socket(service),
    _game(game), _waitingHost()
{
}

bool GameSocket::Initialize(std::string const& port)
{
    if (!listen(PROTO_UDP, port.c_str()))
        return false;
    std::cout << "Listen udp socket opened on port " << port << std::endl;

    async_read(std::bind(&GameSocket::HandleReceive, this));
    return true;
}

void GameSocket::HandleReceive()
{
    try {
        Socket::SocketInfo remote;
        char buff[PACKET_SIZE];
        recvfrom(buff, PACKET_SIZE, remote);
        ::Packet recvPkt(buff);


        std::string const& hostIdent = remote.GetHostIdentifier();

        if (Player* player = _game->GetPlayer(hostIdent))
            player->HandleReceive(&recvPkt);
        else
        {
            auto itr = _waitingHost.find(hostIdent);
            if (itr == _waitingHost.end())
            {
                std::cout << "New connection from " << hostIdent << std::endl;
                _waitingHost[hostIdent] = time(NULL) + sConfig->GetIntDefault("Game.Socket.Timeout", 10);
                // send to
                Packet pkt(SMSG_GREETING);
                sendto(pkt.data(), pkt.size(), remote);
            }
            else
                _HandlePlayerKey(recvPkt, remote);
        }

        _CleanWaitingHost();
    }
    catch (std::exception const& e)
    {
        std::cerr << "GameSocket::HandleReceive Error: " << e.what() << std::endl;
    }

    async_read(std::bind(&GameSocket::HandleReceive, this));
}

void GameSocket::_CleanWaitingHost()
{
    time_t currTime = time(NULL);
    auto itr = _waitingHost.begin();

    for(; itr != _waitingHost.end(); )
    {
        if (currTime > itr->second)
        {
            std::cout << "Drop client " << itr->first << std::endl;
            _waitingHost.erase(itr++);
        }
        else
            ++itr;
    }
}

void GameSocket::_HandlePlayerKey(::Packet& pkt, Socket::SocketInfo const& sockInfo)
{
    if (pkt.GetOpcode() != CMSG_PLAYER_KEY)
    {
        std::cerr << "Error: invalid key packet (" << pkt.GetOpcode() << ")" << std::endl;
        Packet data(SMSG_CONNECT_RESULT);
        data << uint8(CONNECT_FAIL);
        sendto(data.data(), data.size(), sockInfo);
        return;
    }

    uint32 key;
    pkt >> key;

    if (!_game->IsValidePlayerKey(key))
    {
        std::cerr << "Error: player try to connect with an invalid key (" << key << ")" << std::endl;

        Packet data(SMSG_CONNECT_RESULT);
        data << uint8(CONNECT_FAIL);
        sendto(data.data(), data.size(), sockInfo);
        return;
    }

    uint32 number = _game->GetPlayerNumberByKey(key);

    Player* player = new Player(_game, sockInfo, number, key);
    _game->AddPlayer(player);

    std::cout << "New registered player " << player->GetHostIdentifier() << std::endl;

    Packet data(SMSG_CONNECT_RESULT);
    data << uint8(CONNECT_OK);
    data << uint32(number);
    sendto(data.data(), data.size(), sockInfo);
}

}
