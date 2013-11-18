#ifndef UDPSOCKET_H_
# define UDPSOCKET_H_

#include "Socket.hpp"
#include "Packet.hpp"

#include <string>

class Client;

class UDPSocket : public Socket
{
public:
    UDPSocket(Client* client, NetService& service);
    bool Connect(std::string const& addr, std::string const& port);

    void HandleReceive();

    void Send(char const buff[], size_t size);
    void Receiv(char buff[], size_t size);

private:
    Client* _client;
};

#endif /* !UDPSOCKET_H_ */
