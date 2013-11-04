#ifndef GAME_H_
# define GAME_H_

#include <SharedDefines.h>
#include <Thread.hpp>
#include "SessionSocketMgr.h"
#include "Utils.hpp"

#define MAX_PLAYERS 4

struct GameConfig
{
    uint32 gameId;
    uint32 playersToken[MAX_PLAYERS];
    std::string gamePort;
};

class Game : public Thread
{
public:
    Game(GameConfig const& conf);
    virtual ~Game();

    uint32 GetId() const { return _config.gameId; }
    uint32 GetPort() const { return to<uint32>(_config.gamePort); }

    void Start();
    void Stop();
    void Wait();

    void operator()();
    void Update(uint32 const diff);

private:
    GameConfig _config;
    SessionSocketMgr _sockMgr;
};

#endif /* !GAME_H_ */
