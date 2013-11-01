#include "Game.h"
#include "ConfigMgr.h"

#include <Utils.hpp>
#include <iostream>
#include <unistd.h>

Game::Game(GameConfig const& conf) : _config(conf)
{
}

Game::~Game()
{
}

void Game::Start()
{
    if (sConfig->GetBoolDefault("Game.Debug", false))
        std::cout << "Game: Start thread gameId: " << _config.gameId << std::endl;
    _run();
}

void Game::Stop()
{
    _stop();
}

void Game::Wait()
{
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