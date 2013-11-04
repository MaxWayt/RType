#ifndef SESSIONSOCKETMGR_H_
# define SESSIONSOCKETMGR_H_

#include <string>
#include "SharedDefines.h"
#include "SessionSocketAcceptor.h"

class Game;

class SessionSocketMgr
{
public:
    SessionSocketMgr(Game* game);
    virtual ~SessionSocketMgr();

    // threads unused ATM
    bool Initialize(std::string const& addr, std::string const& port, uint8 threads);

    void StartNetwork();
    void StopNetwork();
    void WaitNetwork();

private:
    SessionSocketAcceptor _acceptor;
    Game* _game;
};


#endif /* !SESSIONSOCKETMGR_H_ */
