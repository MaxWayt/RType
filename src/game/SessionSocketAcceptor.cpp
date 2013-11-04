#include "SessionSocketAcceptor.h"
#include "SessionSocketMgr.h"

#include <iostream>

namespace Game
{

SessionSocketAcceptor::SessionSocketAcceptor(SessionSocketMgr* mgr) : _sock(mgr->GetNetService()), _mgr(mgr)
{
}

SessionSocketAcceptor::~SessionSocketAcceptor()
{
}

bool SessionSocketAcceptor::Initialize(std::string const& addr, std::string const& port)
{
    if (!_sock.listen(PROTO_UDP, port.c_str(), NULL))
        return false;
    std::cout << "Listen udp socket opened on port " << port << std::endl;
    return true;
}

} // namespace Game
