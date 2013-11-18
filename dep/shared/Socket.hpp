/*
** Socket.hpp for Socket in /home/leroy_v/Perso/Socket
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Wed Oct 30 13:30:26 2013 vincent leroy
** Last update Wed Oct 30 17:32:05 2013 vincent leroy
*/

#ifndef SOCKET_H_
# define SOCKET_H_

#include "NetService.h"
#include <string>
#include <cstring>
#include <stdexcept>

#if defined(LINUX) || defined(OSX)
# include <errno.h>
# include <netinet/in.h>
#endif
enum Protocoles
{
    PROTO_TCP       = 0,
    PROTO_UDP       = 1,
};

struct ProtoSockData
{
    Protocoles proto;
    int type;
    int p_proto;
};

extern ProtoSockData protoDatas[];

class Socket
{
public:
    class SocketInfo
    {
    public:
        SocketInfo();
        SocketInfo(struct sockaddr_in const& addr_in);
        std::string const& GetRemoteHost() const;
        std::string const& GetRemotePort() const;
        std::string const& GetHostIdentifier() const;

        operator struct sockaddr*();

    private:
        struct sockaddr_in _sockInfo;
    };

    Socket(NetService& service);
    Socket(NetService& service, int fd, struct sockaddr_in const& sock);
    virtual ~Socket();

    bool listen(Protocoles proto, const char *port);
    bool open(Protocoles proto, const char *hostname, const char *port);
    void close();
    bool read(char *buff, size_t len);
    void write(const char *buff, size_t len) const;
    void async_read(std::function<void()> fct);
    Socket* accept() const;
    void recvfrom(char buff[], size_t size, SocketInfo& from) const;
    void sendto(char const buff[], size_t size, SocketInfo& dest);

protected:
#if defined(LINUX) || defined(OSX)
    int _sockfd;
#else
    SOCKET _sockfd;
#endif
    NetService& _service;
    struct sockaddr_in _sockIn;
};

#endif /* !SOCKET_H_ */
