#ifndef LEVELUUUU_H_
# define LEVELUUUU_H_

#include <random>
#include <unordered_map>
#include "SharedDefines.h"
#include "Opcodes.h"

/*                           8    32 32   F UINT8  F */
/* Packet : SMSG_ADD_MONSTER FIRE ID TYPE X HEAL   Y */

namespace Game
{

class Game;

struct Monster
{
    uint32 id;
    uint32 type;
    uint8 health;
    uint8 fire;
    float x;
    float y;

};
struct QueenMonster
{
    uint32 nb;
    uint16 pregnancy_time;
    uint16 timer;
    Monster monster;
};
struct LevelConfig
{
    uint32 nb;
    QueenMonster collection[20];
};

class Level
{
public:
    Level(Game *game);
    virtual ~Level();
    void update(uint32 time);
    void sendMonster(Monster *monster);
    Monster *getMonster(uint32 id);
    void removeMonster(uint32 id);
private:
    float _getRandomBetween(int min, int max);
    Game *_game;
    LevelConfig *_config;
    std::unordered_map<uint32, Monster *> _monsters;
    uint32 _id;
};
}

#endif
