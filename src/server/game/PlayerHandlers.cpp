#include <iostream>
#include "Player.h"
#include "Game.h"
#include "Opcodes.h"

namespace Game
{

void Player::HandlePosition(Packet* pkt)
{
    *pkt >> _x;
    *pkt >> _y;

    Packet data(SMSG_PLAYER_POSITION);
    data << uint32(GetId());
    data << _x;
    data << _y;

    _game->BroadcastToAll(data, this);
}

void Player::HandleShot(Packet* pkt)
{
    float x, y;
    uint8 level;
    *pkt >> x >> y >> level;

    Packet data(SMSG_SHOT);
    data << uint32(GetId());
    data << x;
    data << y;
    data << uint8(level);
    _game->BroadcastToAll(data);
}

}
