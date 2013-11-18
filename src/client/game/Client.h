#ifndef CLIENT_H_
# define CLIENT_H_

#include "Thread.hpp"
#include "UDPSocket.h"
#include "LockedQueue.hpp"

#define DEFAULT_SLEEP_TIME 50

class Client : public Thread
{
public:
    Client();

    void operator()();

    void Start();
    void Stop();
    void Wait();

    bool InitializeGame(uint32 clientKey, std::string const& addr, std::string const& port);

    void Update(uint32 const diff);

    void UDPHandleReceive(Packet* recvPkt);
    void UpdateIncomingPackets();

    void UDPSend(Packet const& pkt);


    // Handlers

    void HandleGreeting(Packet* recvPkt);
private:
    NetService _service;
    UDPSocket _udpSocket;
    uint32 _clientKey;
    LockedQueue<Packet> _recvQueue;

};

#endif /* !CLIENT_H_ */
