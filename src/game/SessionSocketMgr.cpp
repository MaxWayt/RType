#include "Game.h"
#include "SessionSocketMgr.h"

SessionSocketMgr::SessionSocketMgr(Game* game) : _acceptor(this), _game(game)
{
}

SessionSocketMgr::~SessionSocketMgr()
{
}

bool SessionSocketMgr::Initialize(std::string const& addr, std::string const& port, uint8 threads)
{
    if (!_acceptor.Initialize(addr, port))
        return false;
    return true;
}

void SessionSocketMgr::StartNetwork()
{
    _acceptor.Start();
}

void SessionSocketMgr::StopNetwork()
{
    _acceptor.Stop();
}

void SessionSocketMgr::WaitNetwork()
{
    _acceptor.Wait();
}
