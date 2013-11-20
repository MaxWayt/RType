#ifndef LEVELUUUU_H_
# define LEVELUUUU_H_

#include <unordered_map>
#include "SharedDefines.h"
#include "Opcodes.h"

/*                           8    32 32   8      F UINT8  F */
/* Packet : SMSG_ADD_MONSTER FIRE ID TYPE WEAPON X HEAL   Y */

namespace Game
{

class Game;

struct Monster
{
    uint32 id;
    uint32 type;
    uint8 weapon;
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
private:
    Game *_game;
    LevelConfig *_config;
    std::unordered_map<uint32, Monster *> _monsters;
    uint32 _id;
};
}

#endif

