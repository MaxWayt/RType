/*
** Socket.cpp for Socket in /home/leroy_v/Perso/Socket
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Oct 30 13:30:22 2013 vincent leroy
** Last update Wed Oct 30 17:35:20 2013 vincent leroy
*/

#if defined(LINUX) || defined(OSX)
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
#else
# define _WIN32_WINNT 0x501
# include <winsock2.h>
# include <ws2tcpip.h>
#endif

#include <stdlib.h>

#include "Socket.hpp"

#include <iostream>

ProtoSockData protoDatas[] = {
    {PROTO_TCP, SOCK_STREAM, IPPROTO_TCP},
    {PROTO_UDP, SOCK_DGRAM, IPPROTO_UDP}
};

Socket::Socket() :
    _sockfd()
{
}

Socket::~Socket()
{
}

bool Socket::listen(Protocoles proto, const char *port, int *num_port)
{
    struct addrinfo *addr;
    struct addrinfo hints = {};

    _sockfd = socket(AF_INET, protoDatas[proto].type, protoDatas[proto].p_proto);
#if defined(LINUX) || defined(OSX)
    if (_sockfd == -1)
#else
    if (_sockfd == INVALID_SOCKET)
#endif // LINUX
    {
        std::cerr << "Error: fail to create socket : " << strerror(errno) << std::endl;
        return false;
    }

    hints.ai_family = AF_INET;
    hints.ai_socktype = protoDatas[proto].type;
    hints.ai_protocol = protoDatas[proto].p_proto;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, port, &hints, &addr) != 0)
    {
        close();
        std::cerr << "Error: fail to get addrinfo port " << port << std::endl;
        return false;
    }

    if (bind(_sockfd, addr->ai_addr, sizeof(struct sockaddr_in)) != 0)
    {
        close();
        freeaddrinfo(addr);
        std::cerr << "Error: fail to bind socket" << std::endl;
        return false;
    }

    if (num_port)
        *num_port = ntohs(((struct sockaddr_in*)addr->ai_addr)->sin_port);

    freeaddrinfo(addr);
    return true;
}

bool Socket::open(const char *protoName, const char *hostname, const char *port)
{
    struct protoent *proto;
    struct addrinfo *addr;
    struct addrinfo hints = {};

    if ((proto = getprotobyname(protoName)) == NULL)
        return false;
    _sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
#if defined(LINUX) || defined(OSX)
    if (_sockfd == -1)
#else
    if (_sockfd == INVALID_SOCKET)
#endif // LINUX
        return false;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = proto->p_proto;

    if (getaddrinfo(hostname, port, &hints, &addr) != 0)
    {
        close();
        return false;
    }

    if (connect(_sockfd, addr->ai_addr, sizeof(struct sockaddr)) != 0)
    {
        close();
        freeaddrinfo(addr);
        return false;
    }

    freeaddrinfo(addr);
    return true;
}

void Socket::close()
{
#if defined(LINUX) || defined(OSX)
    ::close(_sockfd);
#else
    closesocket(_sockfd);
    WSACleanup();
#endif
}

bool Socket::read(char *buff, size_t len)
{
#if defined(LINUX) || defined(OSX)
    return ::read(_sockfd, buff, len) >= 0;
#else
    return recv(_sockfd, buff, len, 0) >= 0;
#endif
}

bool Socket::write(const char *buff, size_t len)
{
#if defined(LINUX) || defined(OSX)
    return ::write(_sockfd, buff, len) >= 0;
#else
    return send(_sockfd, buff, len, 0) >= 0;
#endif
}
