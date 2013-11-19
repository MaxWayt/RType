#ifndef CLIENT_H_
# define CLIENT_H_

#include "Thread.hpp"
#include "UDPSocket.h"
#include "LockedQueue.hpp"
#include "DisplayManager.hh"

#define DEFAULT_SLEEP_TIME 50

class Client : public Thread
{
public:
    Client(int32 width, int32 height, bool fullscreen = false);
    virtual ~Client();

    void operator()();

    void Start(uint32 clientId);
    void Stop();
    void Wait();

    uint32 GetClientKey() const { return _clientKey; }

    bool InitializeGame(uint32 clientKey, std::string const& addr, std::string const& port);

    void Update(uint32 const diff);

    void UDPHandleReceive(Packet const* recvPkt);
    void UpdateIncomingPackets();

    void UDPSend(Packet const& pkt);

    void UpdatePlayerPosition();

    // Handlers

    void HandleGreeting(Packet* recvPkt);
    void HandleConnectResult(Packet* recvPkt);
    void HandlePlayerPosition(Packet* recvPkt);
    void HandleAddPlayer(Packet* recvPkt);
private:
    NetService _service;
    UDPSocket _udpSocket;
    uint32 _clientKey;
    LockedQueue<Packet> _recvQueue;
    DisplayManager _display;

};

#endif /* !CLIENT_H_ */
