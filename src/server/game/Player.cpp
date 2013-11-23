#include "Player.h"
#include "Game.h"
#include "Opcodes.h"
#include "ConfigMgr.h"

#include <iostream>

namespace Game
{

Player::Player(Game* game, Socket::SocketInfo const& sockInfo, uint32 number, uint32 key) :
    _sockInfo(sockInfo), _game(game), _id(number), _recvQueue(), _key(key),
    _x(0.0f), _y(0.0f), _pingTimer(0), _lastPing(GetMSTime()), _loginOut(false),
    _shooting(false)
{
    _pingTimer = sConfig->GetIntDefault("Game.Player.PingInterval", 2000);
}

void Player::HandleReceive(::Packet const* pkt)
{
    if (pkt->GetOpcode() == CMSG_PONG)
    {
        _lastPing = GetMSTime();
        return;
    }
    ::Packet* recv = new ::Packet(*pkt);
    _recvQueue.add(recv);
}

void Player::Update(uint32 const diff)
{
    uint32 size = _recvQueue.size();
    for (uint32 i = 0; i < size && !_recvQueue.empty(); ++i)
    {
        ::Packet* pkt = _recvQueue.get();
        if (!pkt)
            continue;

        Opcode::OpcodeHandler const* opcodehandler = Opcode::GetHandler((Opcodes)pkt->GetOpcode());
        if (!opcodehandler)
        {
            std::cerr << "Error: receiv an unknow opcode : " << pkt->GetOpcode() << std::endl;
            delete pkt;
            continue;
        }
        if (opcodehandler->handler)
            (this->*(opcodehandler->handler))(pkt);

        delete pkt;
    }

    if (_pingTimer <= diff)
    {
        if (GetMSTimeDiffToNow(_lastPing) >= uint32(sConfig->GetIntDefault("Game.Player.PingInterval", 2000) + 1000))
        {
            std::cout << "Player " << GetHostIdentifier() << "'s ping timeout, removing" << std::endl;
            _game->RemovePlayer(this);
            _loginOut = true;
            return;
        }

       Packet pkt(SMSG_PING);
       Send(pkt);
        _pingTimer = sConfig->GetIntDefault("Game.Player.PingInterval", 2000);
    }
    else
        _pingTimer -= diff;
}

void Player::Send(Packet const& pkt)
{
    _game->SendTo(pkt, _sockInfo);
}

void Player::BuildCreatePacket(Packet& pkt) const
{
    pkt << uint32(GetId());
    pkt << GetPositionX();
    pkt << GetPositionY();
    pkt << uint8(IsShooting() ? 1 : 0);
}

}
