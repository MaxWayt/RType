#include "Game.h"
#include "ConfigMgr.h"

#include <Utils.hpp>
#include <iostream>
#include <unistd.h>

namespace Game
{

Game::Game(GameConfig const& conf) :
    _config(conf), _service(), _sock(this, _service), _playerMap(),
    _playerAddedMap()
{
}

Game::~Game()
{
}

void Game::Start()
{
    if (sConfig->GetBoolDefault("Game.Debug", false))
        std::cout << "Game: Start thread gameId: " << _config.gameId << std::endl;

    if (!_sock.Initialize(_config.gamePort))
        throw std::runtime_error("Fail to init network for game");
    _service.Start();
    _run();
}

void Game::Stop()
{
    _service.Stop();
    _stop();
}

void Game::Wait()
{
    _service.Wait();
    _join();
}

void Game::operator()()
{
    uint32 prevTime = GetMSTime();
    uint32 currTime = 0;
    uint32 prevSleep = 0;

    uint32 sleepTime = sConfig->GetIntDefault("Game.SleepTime", 50);
    while (!_isStopped())
    {
        currTime = GetMSTime();
        uint32 diff = GetMSTimeDiff(prevTime, currTime);

        Update(diff);
        prevTime = currTime;

        if (diff <= sleepTime+ prevSleep)
        {
            prevSleep = sleepTime + prevSleep - diff;
            Thread::Sleep(prevSleep);
        }
        else
            prevSleep = 0;
    }
}

void Game::Update(uint32 const diff)
{
//    std::cout << "UPDATE GAME " << _config.gameId << std::endl;
}

Player* Game::GetPlayer(std::string const& hostIdent)
{
    auto itr = _playerMap.find(hostIdent);
    if (itr != _playerMap.end())
        return itr->second;
    return NULL;
}

Player const* Game::GetPlayer(std::string const& hostIdent) const
{
    auto itr = _playerMap.find(hostIdent);
    if (itr != _playerMap.end())
        return itr->second;
    return NULL;
}

bool Game::IsValidePlayerKey(uint32 key) const
{
    for (uint8 i = 0; i < MAX_PLAYERS; ++i)
        if (_config.playersToken[i] == key)
            return true;
    return false;
}

uint8 Game::GetPlayerNumberByKey(uint32 key) const
{
    for (uint8 i = 0; i < MAX_PLAYERS; ++i)
        if (_config.playersToken[i] == key)
            return i + 1;
    return 0;
}

} // namespace Game
