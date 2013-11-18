#include "UDPSocket.h"
#include "Packet.hpp"
#include "Client.h"

#include <iostream>

UDPSocket::UDPSocket(Client* client, NetService& service) : Socket(service),
    _client(client)
{
}

bool UDPSocket::Connect(std::string const& addr, std::string const& port)
{
    std::cout << "Connecting to " << addr << ":" << port << std::endl;
    if (!open(PROTO_UDP, addr.c_str(), port.c_str()))
    {
        std::cerr << "Fail to connect udp socket to " << addr << ":" << port << std::endl;
        return false;
    }
    char buff[PACKET_SIZE];
    ::memset(buff, 0, PACKET_SIZE);
    Send(buff, PACKET_SIZE);


    async_read(std::bind(&UDPSocket::HandleReceive, this));
    return true;
}

void UDPSocket::HandleReceive()
{
    try {
        Socket::SocketInfo remote;
        char buff[PACKET_SIZE];
        recvfrom(buff, PACKET_SIZE, remote);
        Packet recvPkt(buff);

        _client->UDPHandleReceive(&recvPkt);
    }
    catch (std::exception const& e)
    {
        std::cerr << "UDPSocket::HandleReceive Error: " << e.what() << std::endl;
    }

    async_read(std::bind(&UDPSocket::HandleReceive, this));
}

void UDPSocket::Send(char const buff[], size_t size)
{
    SocketInfo info(_sockIn);
    std::cout << "Send to : " << info.GetHostIdentifier() << std::endl;
    sendto(buff, size, info);
}

void UDPSocket::Receiv(char buff[], size_t size)
{
    SocketInfo info(_sockIn);
    recvfrom(buff, size, info);
}
