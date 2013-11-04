#ifndef SESSIONSOCKETMGR_H_
# define SESSIONSOCKETMGR_H_

#include <string>
#include "SharedDefines.h"
#include "SessionSocketAcceptor.h"

namespace Game
{
class Game;

class SessionSocketMgr
{
public:
    SessionSocketMgr(Game* game);
    virtual ~SessionSocketMgr();

    NetService& GetNetService() { return _netService; }

    // threads unused ATM
    bool Initialize(std::string const& addr, std::string const& port, uint8 threads);

    void StartNetwork();
    void StopNetwork();
    void WaitNetwork();

private:
    NetService _netService;
    SessionSocketAcceptor _acceptor;
    Game* _game;
};
}


#endif /* !SESSIONSOCKETMGR_H_ */
