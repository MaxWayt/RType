#ifndef GAME_H_
# define GAME_H_

#include <SharedDefines.h>
#include <Thread.hpp>
#include "GameSocket.h"
#include "Utils.hpp"
#include "Player.h"

#define MAX_PLAYERS 4

namespace Game
{
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

    Player* GetPlayer(std::string const& hostIdent);
    Player const* GetPlayer(std::string const& hostIdent) const;

    bool IsValidePlayerKey(uint32 key) const;
    uint8 GetPlayerNumberByKey(uint32 key) const;

    void AddPlayer(Player* player) { _playerAddedMap[player->GetHostIdentifier()] = player; }

private:
    GameConfig _config;
    NetService _service;
    GameSocket _sock;
    std::map<std::string, Player*> _playerMap;
    std::map<std::string, Player*> _playerAddedMap;
};
}

#endif /* !GAME_H_ */
