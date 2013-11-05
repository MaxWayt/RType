#ifndef PLAYER_H_
# define PLAYER_H_

#include "Socket.hpp"
#include "Packet.hpp"

namespace Game
{

class Game;

class Player
{
public:
    Player(Game* game, Socket::SocketInfo const& sockInfo, uint8 number);

    std::string const& GetHostIdentifier() const { return _sockInfo.GetHostIdentifier(); }

    void HandleReceive(Packet const* pkt);

private:
    Socket::SocketInfo _sockInfo;
    Game* _game;
    uint8 _number;
};

}

#endif /* !PLAYER_H_ */
