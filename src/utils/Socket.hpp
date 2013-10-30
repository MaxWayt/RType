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

class Socket
{
public:
    Socket();
    virtual ~Socket();

    bool listen(const char *protoName, int type, const char *port, int *num_port);
    bool open(const char *protoName, int type, const char *hostname, const char *port);
    void close();
    bool read(char *buff, size_t len);
    bool write(const char *buff, size_t len);

private:
#ifdef LINUX
    int _sockfd;
#else
    SOCKET _sockfd;
#endif
};

#endif /* !SOCKET_H_ */
