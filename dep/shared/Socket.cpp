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
# include <poll.h>
#else
# define _WIN32_WINNT 0x501
# include <winsock2.h>
# include <Mswsock.h>
# include <ws2tcpip.h>
#endif

#include <stdlib.h>

#include "Socket.hpp"
#include "Utils.hpp"

#include <iostream>
#include <utility>

ProtoSockData protoDatas[] = {
    {PROTO_TCP, SOCK_STREAM, IPPROTO_TCP},
    {PROTO_UDP, SOCK_DGRAM, IPPROTO_UDP}
};

Socket::SocketInfo::SocketInfo() :
    _sockInfo()
{
}

Socket::SocketInfo::SocketInfo(struct sockaddr_in const& sockInfo) :
    _sockInfo(sockInfo)
{
}

Socket::SocketInfo::operator struct sockaddr*()
{
    return (struct sockaddr*)&_sockInfo;
}

std::string const& Socket::SocketInfo::GetRemoteHost() const
{
    static std::string str;
    str = inet_ntoa(_sockInfo.sin_addr);
    return str;
}

std::string const& Socket::SocketInfo::GetRemotePort() const
{
    static std::string str;
    IntToString((int)ntohs(_sockInfo.sin_port), str);
    return str;
}

std::string const& Socket::SocketInfo::GetHostIdentifier() const
{
    static std::string str;
    str = GetRemoteHost();
    str += ":";
    str += GetRemotePort();
    return str;
}


Socket::Socket(NetService& service) :
    _sockfd(), _service(service), _sockIn()
{
}

Socket::Socket(NetService& service, int fd, struct sockaddr_in const& sock) :
    _sockfd(fd), _service(service), _sockIn(sock)
{
}

Socket::~Socket()
{
}

bool Socket::listen(Protocoles proto, const char *port)
{
    _sockfd = ::socket(AF_INET, protoDatas[proto].type, protoDatas[proto].p_proto);
#if defined(LINUX) || defined(OSX)
    if (_sockfd == -1)
#else
    if (_sockfd == INVALID_SOCKET)
#endif // LINUX
    {
        std::cerr << "Socket::listen 1, Error: " << strerror(errno) << std::endl;
        return false;
    }

    ::memset(&_sockIn, 0, sizeof(struct sockaddr_in));
    _sockIn.sin_family = AF_INET;
    _sockIn.sin_port = htons(to<int>(port));
    _sockIn.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(_sockfd, (const struct sockaddr*)&_sockIn, sizeof(struct sockaddr_in)) < 0)
    {
        close();
        std::cerr << "Socket::listen 2, Error: " << strerror(errno) << std::endl;
        return false;
    }

    if (proto == PROTO_TCP && ::listen(_sockfd, 0) < 0)
    {
        close();
        std::cerr << "Socket::listen 3, Error: " << strerror(errno) << std::endl;
        return false;
    }

    return true;
}

bool Socket::open(Protocoles proto, const char *hostname, const char *port)
{
    _sockfd = socket(AF_INET, protoDatas[proto].type, protoDatas[proto].p_proto);
#if defined(LINUX) || defined(OSX)
    if (_sockfd == -1)
#else
    if (_sockfd == INVALID_SOCKET)
#endif // LINUX
    {
        std::cerr << "Error while create socket: " << strerror(errno) << std::endl;
        return false;
    }

    ::memset(&_sockIn, 0, sizeof(_sockIn));  
    _sockIn.sin_family = AF_INET;  
    _sockIn.sin_addr.s_addr = inet_addr(hostname);  
    _sockIn.sin_port = htons(to<int>(port));  
    
    if (proto == PROTO_TCP && connect(_sockfd, (const struct sockaddr*)&_sockIn, sizeof(struct sockaddr_in)) != 0)
    {
        std::cerr << "Error while connect socket: " << strerror(errno) << std::endl;
        close();
        return false;
    }

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

void Socket::write(const char *buff, size_t len) const
{
    int ret = 0;
    pollfd fdarray;
    fdarray.fd = _sockfd;
    fdarray.events = POLLWRNORM;
#if defined(LINUX) || defined(OSX)
    ret = poll(&fdarray, 1, 0);
#else
    ret = WSAPoll(&fdarray, 1, 0);
#endif
    if (ret == 0)
        throw std::runtime_error("Socket::write, request timedout");
    if (ret < 0)
        throw std::runtime_error("Socket::write, poll ret < 0");
    if (fdarray.revents & POLLWRNORM)
    {
        //Send data
#if defined(LINUX) || defined(OSX)
        if (::write(_sockfd, buff, len) < 0)
#else
        if (SOCKET_ERROR == (ret = send(_sockfd, buff, len, 0)))
#endif
            throw std::runtime_error("Socket::write, fail to write un the socket");
    }
}

void Socket::async_read(std::function<void()> fct)
{
    _service.register_read_handler(_sockfd, fct);
}

Socket* Socket::accept() const
{
    int newFd;
    unsigned int t;
    struct sockaddr_in remote;

    t = sizeof(remote);

    if ((newFd = ::accept(_sockfd, (struct sockaddr *)&remote, &t)) == -1)
    {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        return NULL;
    }

    std::cout << "NewFD : " << newFd << std::endl;
    Socket* sock = new Socket(_service, newFd, remote);
    return sock;
}

void Socket::recvfrom(char buff[], size_t size, Socket::SocketInfo& from) const
{
    socklen_t fromlen;

    fromlen = sizeof (struct sockaddr_in);
    if (::recvfrom(_sockfd, buff, size, 0, (struct sockaddr *)&from, &fromlen) <= 0)
        throw std::runtime_error(strerror(errno));
}

void Socket::sendto(char const buff[], size_t size, Socket::SocketInfo& dest)
{
    socklen_t destlen;

    destlen = sizeof (struct sockaddr_in);
    if (::sendto(_sockfd, buff, size, 0, (struct sockaddr const*)&dest, destlen) < 0)
        std::cerr << "Socket::sendto : " << strerror(errno) << std::endl;
}
