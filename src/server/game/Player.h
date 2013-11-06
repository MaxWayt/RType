#ifndef PLAYER_H_
# define PLAYER_H_

#include "Socket.hpp"
#include "Packet.hpp"
#include "LockedQueue.hpp"

namespace Game
{

class Game;

class Player
{
public:
    Player(Game* game, Socket::SocketInfo const& sockInfo, uint8 number, uint32 key);

    std::string const& GetHostIdentifier() const { return _sockInfo.GetHostIdentifier(); }
    uint32 GetKey() const { return _key; }

    void HandleReceive(Packet const* pkt);

    void Update(uint32 const diff);


    // Handlers
    void HandlePosition(Packet* pkt);

private:
    Socket::SocketInfo _sockInfo;
    Game* _game;
    uint8 _number;
    LockedQueue<Packet> _recvQueue;
    uint32 _key;
};

}

#endif /* !PLAYER_H_ */
