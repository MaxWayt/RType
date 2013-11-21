/*
 * RType
 *
 */

#ifndef SERVER_H_
# define SERVER_H_

#include "Thread.hpp"
#include "SharedDefines.h"

#include <string>
#include <map>

#define SERVER_SLEEP_TIME 50

namespace Game { class Game; }

class Server : public Thread
{
public:
    Server();

    void operator()();

    void Start();
    void Stop();
    void Wait();

    Game::Game* CreateNewGame(std::string const& file);
    void DeleteGame(Game::Game* game);

    struct ServerCommand
    {
        char const* str;
        void (Server::*func)(std::string const&);
    };
    ServerCommand const* GetCommand(std::string const&) const;
    void CommandGameCreate(std::string const& params);
    void CommandGameList(std::string const& params);

private:
    uint32 _GetNewGameId() const;
    uint32 _GetFreeGamePort() const;
    std::map<uint32, Game::Game*> _gameMap;
};

#endif
