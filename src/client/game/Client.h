#ifndef CLIENT_H_
# define CLIENT_H_

#include "Thread.hpp"
#include "UDPSocket.h"
#include "LockedQueue.hpp"
#include "DisplayManager.hh"
#include "Singleton.hpp"

#define DEFAULT_SLEEP_TIME 50

class Client : public Singleton<Client>
{
public:
    Client();
    virtual ~Client();

    void Initialize(int32 width, int32 height, bool fullscreen);

    void Launch(uint32 clientId, std::string const &addr, std::string const &port);

    uint32 GetClientKey() const { return _clientKey; }

    bool InitializeGame(uint32 clientKey, std::string const& addr, std::string const& port);

    void UDPHandleReceive(Packet const* recvPkt);
    void UpdateIncomingPackets();

    void UDPSend(Packet const& pkt);

    DisplayManager* GetDisplay() { return _display; }

    uint32 GetPlayerId() const { return (_player ? _player->getNumPlayer() : 0); }

    // Handlers

    void HandleGreeting(Packet* recvPkt);
    void HandleConnectResult(Packet* recvPkt);
    void HandlePlayerPosition(Packet* recvPkt);
    void HandleAddPlayer(Packet* recvPkt);
    void HandleRemovePlayer(Packet* recvPkt);
    void HandlePlayerShot(Packet* recvPkt);
    void HandleAddMonster(Packet* recvPkt);
    void HandleRemoveMonster(Packet* recvPkt);
    void HandlePlayerGetHit(Packet* recvPkt);
    void HandleGameEnd(Packet* recvPkt);
 
private:
    NetService _service;
    UDPSocket _udpSocket;
    uint32 _clientKey;
    LockedQueue<Packet> _recvQueue;
    DisplayManager* _display;
    Player* _player;

};

#define sClient Client::instance()

#endif /* !CLIENT_H_ */
