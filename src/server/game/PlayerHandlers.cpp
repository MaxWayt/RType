#include <iostream>
#include "Player.h"
#include "Game.h"
#include "Opcodes.h"

namespace Game
{

void Player::HandlePosition(Packet* pkt)
{
    if (!IsAlive() && _shooting)
        return;

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

    if (!IsAlive() && _shooting)
        return;

    Packet data(SMSG_SHOT);
    data << uint32(GetId());
    data << uint8(active);
    data << uint8(level);
    _game->BroadcastToAll(data);
}
void Player::HandleHitMonster(Packet* pkt)
{
    if (!IsAlive())
        return;

    uint32 id;
    *pkt >> id;

    std::cout << "PLAYER " << GetId() << " HIT MONSTER " << id << std::endl;

    auto monster = _game->GetLevel().getMonster(id);
    if (monster == NULL)
    {
        std::cout << "MONSTER " << id << " NOT FOUND" << std::endl;
        return;
    }
    if (monster->health - 1 <= 0) {

        _game->GetLevel().removeMonster(id);
        Packet data(SMSG_REMOVE_MONSTER);
        data << id;
        _game->BroadcastToAll(data);
        std::cout << "SEND REMOVE MOSNTER " << id << std::endl;
    }
    else {

        monster->health = monster->health - 1;
    }
}

void Player::HandleGetHit(Packet* pkt)
{
    if (!IsAlive())
        return;

    --_health;

    Packet data(SMSG_PLAYER_GET_HIT);
    data << uint32(GetId());
    data << uint32(_health);
    _game->BroadcastToAll(data);
}

}
