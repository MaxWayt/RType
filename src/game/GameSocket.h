#ifndef GAMESOCKET_H_
# define GAMESOCKET_H_

#include "Socket.hpp"
#include "Packet.hpp"

#include <string>

namespace Game
{

class Game;

class GameSocket : public Socket
{
public:
    GameSocket(Game* game, NetService& service);
    bool Initialize(std::string const& port);

    void HandleReceive();

private:
    void _CleanWaitingHost();
    void _HandlePlayerKey(Packet& pkt, Socket::SocketInfo const& sockInfo);
    Game* _game;
    std::map<std::string, time_t> _waitingHost;
};

}

#endif /* !GAMESOCKET_H_ */
