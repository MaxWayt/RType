/*
 * RType
 *
 */

#ifdef WIN32
# undef __STRICT_ANSI__
#endif

#include "Server.h"
#include "Utils.hpp"
#include "ConfigMgr.h"
#include "Game.h"

#include <iostream>
#include <unistd.h>

Server::Server() : _gameMap()
{
}

void Server::operator()()
{
    uint32 prevTime = GetMSTime();
    uint32 currTime = 0;
    uint32 prevSleep = 0;
    uint32 sleepTime = sConfig->GetIntDefault("Server.SleepTime", 50);
    while (!_isStopped())
    {
        currTime = GetMSTime();
        uint32 diff = GetMSTimeDiff(prevTime, currTime);

        Update(diff);
        prevTime = currTime;

        if (diff <= sleepTime + prevSleep)
        {
            prevSleep = sleepTime + prevSleep - diff;
            Thread::Sleep(prevSleep);
        }
        else
            prevSleep = 0;
    }
}

void Server::Start()
{
    _run();
}

void Server::Stop()
{
    _stop();
}

void Server::Wait()
{
    _join();
}

void Server::Update(uint32 const diff)
{
    static uint32 temp = 5 * IN_MILLISECONDS;
    if (temp <= diff)
    {
        Game* game = NULL;
        try {
            game = CreateNewGame();
            if (sConfig->GetBoolDefault("Server.Debug", false))
                std::cout << "Server: launching new game, id: " << game->GetId() << std::endl;
            game->Start();
        }
        catch (std::exception const& e) {
            std::cerr << e.what() << std::endl;
            DeleteGame(game);
        }
        temp = 1 * IN_MILLISECONDS;
    }
    else
        temp -= diff;
}

uint32 Server::_GetNewGameId() const
{
    for (uint32 id = 1; id < 0xFFFFFFFF; ++id)
        if (_gameMap.find(id) == _gameMap.end())
            return id;
    return 0;
}

uint32 Server::_GetFreeGamePort() const
{
    uint32 port = sConfig->GetIntDefault("Game.StartPort", 5000);
    for (; port < 65536; ++port)
    {
        bool free = true;
        for (auto itr = _gameMap.begin(); free && itr != _gameMap.end(); ++itr)
            if (itr->second->GetPort() == port)
                free = false;

        if (free)
            return port;
    }
    return 0;
}

Game* Server::CreateNewGame()
{
    if (sConfig->GetIntDefault("Server.MaxGameCount", 100) <= _gameMap.size())
        throw std::runtime_error("Max game count exceded");

    GameConfig config;
    config.gameId = _GetNewGameId();
    if (config.gameId == 0)
        throw std::runtime_error("Fail to create new game, no space left");
    uint32 port = _GetFreeGamePort();
    if (port == 0)
        throw std::runtime_error("Fail to get a free port");
    {
        std::stringstream ss;
        ss << port;
        ss >> config.gamePort;
    }
    std::cout << "PORT : " << port << " config.gamePort : " << config.gamePort << std::endl;

    Game* game = new Game(config);
    _gameMap[config.gameId] = game;
    return game;
}

void Server::DeleteGame(Game* game)
{
    if (!game)
        return;

    _gameMap.erase(game->GetId());
    delete game;
}
