#include "Player.h"
#include "Game.h"
#include "Opcodes.h"

#include <iostream>

namespace Game
{

Player::Player(Game* game, Socket::SocketInfo const& sockInfo, uint8 number, uint32 key) :
    _sockInfo(sockInfo), _game(game), _number(number), _recvQueue(), _key(key),
    _x(0.0f), _y(0.0f)
{
}

void Player::HandleReceive(::Packet const* pkt)
{
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
}

void Player::Send(Packet const& pkt)
{
    _game->SendTo(pkt, _sockInfo);
}

}
