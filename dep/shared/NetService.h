#ifndef NETSERVICE_H_
# define NETSERVICE_H_

#include "Thread.hpp"
#include "Mutex.hpp"

#include <functional>
#include <map>

#if defined(LINUX) || defined(OSX)
#include <sys/select.h>
#else // Windows
#endif

class NetService : public Thread
{
public:
    NetService();

    void Start();
    void Stop();
    void Wait();

    void operator()();

    void register_read_handler(int fd, std::function<void()> fct);
private:
    std::map<int, std::function<void()>> _handlerMap;
    Mutex _mutex;
    fd_set _masterfd;
    int _maxfd;
};

#endif /* !NETSERVICE_H_ */
