#include "Game.h"
#include "SessionSocketMgr.h"

namespace Game
{

SessionSocketMgr::SessionSocketMgr(Game* game) : _netService(), _acceptor(this), _game(game)
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
    _netService.Start();
}

void SessionSocketMgr::StopNetwork()
{
    _netService.Stop();
}

void SessionSocketMgr::WaitNetwork()
{
    _netService.Wait();
}

} // namespace Game
