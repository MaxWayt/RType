#include <iostream>
#include "Player.h"
#include "Game.h"

namespace Game
{

void Player::HandlePosition(Packet* pkt)
{
    *pkt >> _x;
    *pkt >> _y;

    std::cout << "RECV POS : " << _x << " - " << _y << std::endl;

    _game->BroadcastPlayerPositionChange(GetId(), _x, _y);
}

}
