#include "SessionSocketAcceptor.h"
#include "SessionSocketMgr.h"

#include <iostream>

namespace Game
{

SessionSocketAcceptor::SessionSocketAcceptor(SessionSocketMgr* mgr) : _sock(), _mgr(mgr)
{
}

SessionSocketAcceptor::~SessionSocketAcceptor()
{
}

void SessionSocketAcceptor::Start()
{
    _run();
}

void SessionSocketAcceptor::Stop()
{
    _stop();
}

void SessionSocketAcceptor::Wait()
{
    _join();
}

void SessionSocketAcceptor::operator()()
{
    Thread::Sleep(50);
}

bool SessionSocketAcceptor::Initialize(std::string const& addr, std::string const& port)
{
    if (!_sock.listen(PROTO_UDP, port.c_str(), NULL))
        return false;
    std::cout << "Listen udp socket opened on port " << port << std::endl;
    return true;
}

} // namespace Game
