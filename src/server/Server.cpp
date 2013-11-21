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
#include "Utils.hpp"

#include <iostream>
#include <unistd.h>

Server::Server() : _gameMap()
{
}

void Server::operator()()
{
    static uint32 temp = 1 * IN_MILLISECONDS;

    std::cout << "R-Type> ";
    std::string str;
    while (std::getline(std::cin, str))
    {
        ServerCommand const* cmd = GetCommand(trim(str));
        if (!cmd)
        {
            std::cerr << "Command no found" << std::endl;
            std::cout << "R-Type> ";
            continue;
        }
        std::string params = "";
        if (str.length() > strlen(cmd->str))
            params = str.substr(strlen(cmd->str));
        (this->*(cmd->func))(trim(params));
        std::cout << "R-Type> ";
    }

    for (auto itr = _gameMap.begin(); itr != _gameMap.end(); ++itr)
        itr->second->Stop();

    for (auto itr = _gameMap.begin(); itr != _gameMap.end(); ++itr)
        itr->second->Wait();
    /*
    if (temp <= diff)
    {
        if (_gameMap.size() == 0)
        {
            Game::Game* game = NULL;
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
        }
        temp = 1 * IN_MILLISECONDS;
    }
    else
        temp -= diff;
        */
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

Server::ServerCommand const* Server::GetCommand(std::string const& cmd) const
{
    static ServerCommand cmdList[] = {
        {"game create", &Server::CommandGameCreate},
        {"game list", &Server::CommandGameList},
        {NULL, NULL},
    };

    for (uint32 i = 0; cmdList[i].str; ++i)
    {
        if (strncmp(cmdList[i].str, cmd.c_str(), strlen(cmdList[i].str)) == 0)
            return &cmdList[i];
    }
    return NULL;
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

Game::Game* Server::CreateNewGame()
{
    if (sConfig->GetIntDefault("Server.MaxGameCount", 100) <= _gameMap.size())
        throw std::runtime_error("Max game count exceded");

    Game::GameConfig config;
    for (uint32 i = 1; i <= MAX_PLAYERS; ++i)
        config.playersToken[i - 1] = i;
    config.gameId = _GetNewGameId();
    if (config.gameId == 0)
        throw std::runtime_error("Fail to create new game, no space left");
    uint32 port = _GetFreeGamePort();
    if (port == 0)
        throw std::runtime_error("Fail to get a free port");
    IntToString(port, config.gamePort);

    Game::Game* game = new Game::Game(config);
    _gameMap[config.gameId] = game;
    return game;
}

void Server::DeleteGame(Game::Game* game)
{
    if (!game)
        return;

    _gameMap.erase(game->GetId());
    delete game;
}

void Server::CommandGameCreate(std::string const& params)
{
    Game::Game* game = NULL;
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
}

void Server::CommandGameList(std::string const& params)
{
    std::cout << "Game count : " << _gameMap.size() << std::endl;

    for (auto itr = _gameMap.begin(); itr != _gameMap.end(); ++itr)
        std::cout << "\tGameId: " << itr->first << " - port: " << itr->second->GetPort() << " - players: " << itr->second->GetPlayerCount() << std::endl;
}
