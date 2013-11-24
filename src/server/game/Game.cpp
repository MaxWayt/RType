#include "Game.h"
#include "ConfigMgr.h"
#include "Opcodes.h"

#include <Utils.hpp>
#include <iostream>
#ifdef UNIX
# include <unistd.h>
#endif

namespace Game
{

Game::Game(GameConfig const& conf) :
    _config(conf), _service(), _sock(this, _service), _playerMap(),
    _playerAddedMap(), _playerRemovedMap(), _playerAddedMutex(), _playerRemovedMutex(), _level(this), _gamePlayerCount(0), _ended(false)
{
    _gamePlayerCount = sConfig->GetIntDefault("Game.PlayerCount", MAX_PLAYERS);
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

    if (!_ended && GetPlayerCount() >= _gamePlayerCount)
    {
        if (GetAlivePlayerCount() == 0 && !_ended)
        {
            _ended = true;
            HandleGameEnd(false);
        }
        else
            if (_level.update(diff))
            {
                _ended = true;
                HandleGameEnd(true);
            }
    }
    _ProcessRemovedPlayer();
}

Player* Game::GetPlayer(std::string const& hostIdent, bool inAdded)
{
    auto itr = _playerMap.find(hostIdent);
    if (itr != _playerMap.end())
        return itr->second;
    if (inAdded)
    {
        auto itr2 = _playerAddedMap.find(hostIdent);
        if (itr2 != _playerAddedMap.end())
            return itr2->second;
    }
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
        itr->second->BuildCreatePacket(currPkt);
        for (auto itr2 = _playerMap.begin(); itr2 != _playerMap.end(); ++itr2)
        {
            itr2->second->Send(currPkt);
            if (itr2->second->IsAlive())
            {
                Packet newPkt(SMSG_ADD_PLAYER);
                itr2->second->BuildCreatePacket(newPkt);
                itr->second->Send(newPkt);
            }
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
        BroadcastToAll(currPkt, itr->second);
        _playerMap.erase(itr->first);
    }
    _playerRemovedMap.clear();
}

void Game::BroadcastToAll(Packet const& pkt, Player const* except) const
{
    for (auto itr = _playerMap.begin(); itr != _playerMap.end(); ++itr)
        if (itr->second != except)
            itr->second->Send(pkt);

}

void Game::SendTo(Packet const& pkt, Socket::SocketInfo const& remote)
{
    _sock.sendto(pkt.data(), pkt.size(), remote);
}

uint32 Game::GetAlivePlayerCount() const
{
    uint32 count = 0;
    for (auto itr = _playerMap.begin(); itr != _playerMap.end(); ++itr)
        if (itr->second->IsAlive())
            ++count;
    return count;
}

void Game::HandleGameEnd(bool win)
{
    Packet pkt(SMSG_GAME_END);
    pkt << uint8(win ? 1 : 0);
    BroadcastToAll(pkt);
}

} // namespace Game


