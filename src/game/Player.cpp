#include "Player.h"

#include "Game.h"

namespace Game
{

Player::Player(Game* game, Socket::SocketInfo const& sockInfo, uint8 number) :
    _sockInfo(sockInfo), _game(game), _number(number)
{
}

void Player::HandleReceive(Packet const* pkt)
{
    
}

}
