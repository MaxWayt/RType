#include "NetService.h"
#include <iostream>
#include <cstring>
#include <stdexcept>

NetService::NetService() : _handlerMap(), _mutex(), _masterfd(), _maxfd(0)
{
    FD_ZERO(&_masterfd);
}

void NetService::Start()
{
    _run();
}

void NetService::Stop()
{
    _stop();
}

void NetService::Wait()
{
    _join();
}

void NetService::operator()()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    struct timeval tv = {0, 1000};

#ifdef WIN32
    WORD Version;
    WSADATA wsaData;
    int err;

    Version = MAKEWORD(2, 2);
    err = WSAStartup(Version, &wsaData);
    if (err != 0)
    {
        std::cerr << "WSAStartup fail with code: " << err << std::endl;
        return;
    }
#endif

    while (!_isStopped())
    {
        int nready = 0;
        ::memcpy(&readfds, &_masterfd, sizeof(_masterfd));

        if(-1 == (nready = select(_maxfd + 1, &readfds, NULL, NULL, &tv)))
        {
#ifdef WIN32
            std::cerr << "select fail: " << WSAGetLastError() << std::endl;
#else
            std::cerr << "select fail: " << strerror(errno) << std::endl;
#endif
            continue;
        }


        for (int i = 0; i <= _maxfd && nready > 0; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                nready--;

                _mutex.lock();
                auto itr = _handlerMap.find(i);
                if (itr == _handlerMap.end())
                    continue;
                std::function<void()> fct = itr->second;
                _handlerMap.erase(itr);

                FD_CLR(i, &_masterfd);
                if (i == _maxfd)
                {
                    _maxfd = 0;
                    for (auto itr = _handlerMap.begin(); itr != _handlerMap.end(); ++itr)
                        if (itr->first < _maxfd)
                            _maxfd = itr->first;
                }
                _mutex.unlock();

                fct();

            }

        }
    }
}

void NetService::register_read_handler(int fd, std::function<void()> fct)
{
    if (_handlerMap.find(fd) != _handlerMap.end())
        throw std::runtime_error("Try to register new read handler by fd is already registered");

    ScopLock lock(_mutex);
    _handlerMap[fd] = fct;
    FD_SET(fd, &_masterfd);
    if (fd > _maxfd)
        _maxfd = fd;
}
