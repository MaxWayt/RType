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
    Player(Game* game, Socket::SocketInfo const& sockInfo, uint32 number, uint32 key);

    std::string const& GetHostIdentifier() const { return _sockInfo.GetHostIdentifier(); }
    uint32 GetKey() const { return _key; }
    uint32 GetId() const { return _id; }

    void HandleReceive(Packet const* pkt);
    void Send(Packet const& pkt);

    void Update(uint32 const diff);

    float GetPositionX() const { return _x; }
    float GetPositionY() const { return _y; }

    bool IsLoginOut() const { return _loginOut; }


    void BuildCreatePacket(Packet& pkt) const;

    bool IsShooting() const { return _shooting; }


    // Handlers
    void HandlePosition(Packet* pkt);
    void HandleShot(Packet* pkt);
    void HandleHitMonster(Packet* pkt);

private:
    Socket::SocketInfo _sockInfo;
    Game* _game;
    uint32 _id;
    LockedQueue<Packet> _recvQueue;
    uint32 _key;

    float _x;
    float _y;

    uint32 _pingTimer;
    uint32 _lastPing;

    bool _loginOut;
    bool _shooting;
};

}

#endif /* !PLAYER_H_ */
