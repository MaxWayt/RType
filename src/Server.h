/*
 * RType
 *
 */

#ifndef SERVER_H_
# define SERVER_H_

#include "Thread.hpp"
#include "SharedDefines.h"

#include <map>

#define SERVER_SLEEP_TIME 50

class Game;

class Server : public Thread
{
public:
    Server();

    void operator()();

    void Start();
    void Stop();
    void Wait();

    void Update(uint32 const diff);

    Game* CreateNewGame();
    void DeleteGame(Game* game);

private:
    uint32 _GetNewGameId() const;
    uint32 _GetFreeGamePort() const;
    std::map<uint32, Game*> _gameMap;
};

#endif
