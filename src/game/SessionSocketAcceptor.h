#ifndef SESSIONSOCKETACCEPTOR_H_
# define SESSIONSOCKETACCEPTOR_H_

#include "Thread.hpp"
#include "Socket.hpp"
#include <string>

class SessionSocketMgr;

class SessionSocketAcceptor : public Thread
{
public:
    SessionSocketAcceptor(SessionSocketMgr* mgr);
    virtual ~SessionSocketAcceptor();

    void Start();
    void Stop();
    void Wait();

    void operator()();

    bool Initialize(std::string const& addr, std::string const& port);

private:
    Socket _sock;
    SessionSocketMgr* _mgr;
};

#endif /* !SESSIONSOCKETACCEPTOR_H_ */
