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
    uint8 active, level;
    *pkt >> active >> level;

    _shooting = (active != 0);

    Packet data(SMSG_SHOT);
    data << uint32(GetId());
    data << uint8(active);
    data << uint8(level);
    _game->BroadcastToAll(data);
}
void Player::HandleHitMonster(Packet* pkt)
{
    uint32 id;
    *pkt >> id;

    auto monster = _game->GetLevel().getMonster(id);
    if (monster == NULL)
        return;
    if (monster->health - 1 <= 0) {

        _game->GetLevel().removeMonster(id);
        Packet data(SMSG_REMOVE_MONSTER);
        data >> id;
        _game->BroadcastToAll(data);
    }
    else {

        monster->health = monster->health - 1;
    }
}

}
