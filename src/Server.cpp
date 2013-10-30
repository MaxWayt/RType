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

#include <iostream>
#include <unistd.h>

Server::Server() { }

void Server::operator()()
{
    uint32 prevTime = GetMSTime();
    uint32 currTime = 0;
    uint32 prevSleep = 0;
    while (!_isStopped())
    {
        currTime = GetMSTime();
        uint32 diff = GetMSTimeDiff(prevTime, currTime);

        Update(diff);
        prevTime = currTime;

        if (diff <= SERVER_SLEEP_TIME + prevSleep)
        {
            prevSleep = SERVER_SLEEP_TIME + prevSleep - diff;
            usleep(prevSleep * IN_MILLISECONDS);
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
    std::cout << sConfig->GetStringDefault("motd", "Rtype alpha") << std::endl;
}
