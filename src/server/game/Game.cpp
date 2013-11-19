#include "Game.h"
#include "ConfigMgr.h"
#include "Opcodes.h"

#include <Utils.hpp>
#include <iostream>
#include <unistd.h>

namespace Game
{

Game::Game(GameConfig const& conf) :
    _config(conf), _service(), _sock(this, _service), _playerMap(),
    _playerAddedMap(), _playerRemovedMap(), _playerAddedMutex(), _playerRemovedMutex()
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
    _ProcessAddedPlayer();
//    std::cout << "UPDATE GAME " << _config.gameId << std::endl;
    for (auto itr = _playerMap.begin(); itr != _playerMap.end(); ++itr)
        if (!itr->second->IsLoginOut())
            itr->second->Update(diff);
    _ProcessRemovedPlayer();
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
    for (auto itr = _playerMap.begin(); itr != _playerMap.end(); ++itr)
        if (itr->second->GetKey() == key)
            return false;

    for (auto itr = _playerAddedMap.begin(); itr != _playerAddedMap.end(); ++itr)
        if (itr->second->GetKey() == key)
            return false;

    for (uint8 i = 0; i < MAX_PLAYERS; ++i)
        if (_config.playersToken[i] == key)
            return true;
    return false;
}

uint32 Game::GetPlayerNumberByKey(uint32 key) const
{
    for (uint8 i = 0; i < MAX_PLAYERS; ++i)
        if (_config.playersToken[i] == key)
            return i + 1;
    return 0;
}

void Game::AddPlayer(Player* player)
{
    ScopLock lock(_playerAddedMutex);
    _playerAddedMap[player->GetHostIdentifier()] = player;
}

void Game::RemovePlayer(Player* player)
{
    ScopLock lock(_playerRemovedMutex);
    _playerRemovedMap[player->GetHostIdentifier()] = player;
}

void Game::_ProcessAddedPlayer()
{
    ScopLock lock(_playerAddedMutex);
    for (auto itr = _playerAddedMap.begin(); itr != _playerAddedMap.end(); ++itr)
    {
        Packet currPkt(SMSG_ADD_PLAYER);
        currPkt << itr->second->GetId();
        currPkt << itr->second->GetPositionX();
        currPkt << itr->second->GetPositionY();
        for (auto itr2 = _playerMap.begin(); itr2 != _playerMap.end(); ++itr2)
        {
            itr2->second->Send(currPkt);
            Packet newPkt(SMSG_ADD_PLAYER);
            newPkt << itr2->second->GetId();
            newPkt << itr2->second->GetPositionX();
            newPkt << itr2->second->GetPositionY();
            itr->second->Send(newPkt);
        }
        _playerMap[itr->first] = itr->second;
    }
    _playerAddedMap.clear();
}

void Game::_ProcessRemovedPlayer()
{
    ScopLock lock(_playerRemovedMutex);
    for (auto itr = _playerRemovedMap.begin(); itr != _playerRemovedMap.end(); ++itr)
    {
        Packet currPkt(SMSG_REMOVE_PLAYER);
        currPkt << itr->second->GetId();
        _playerMap.erase(itr->first);
        for (auto itr2 = _playerMap.begin(); itr2 != _playerMap.end(); ++itr2)
            itr2->second->Send(currPkt);
    }
    _playerRemovedMap.clear();
}


void Game::BroadcastPlayerPositionChange(uint32 playerId, float x, float y) const
{
    Packet pkt(SMSG_PLAYER_POSITION);
    pkt << uint32(playerId);
    pkt << x;
    pkt << y;

    for (auto itr = _playerMap.begin(); itr != _playerMap.end(); ++itr)
        if (itr->second->GetKey() != playerId)
            itr->second->Send(pkt);
}

void Game::SendTo(Packet const& pkt, Socket::SocketInfo const& remote)
{
    _sock.sendto(pkt.data(), pkt.size(), remote);
}

} // namespace Game


