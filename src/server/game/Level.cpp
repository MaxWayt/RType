#include <fstream>
#include <iostream>
#include "Level.h"
#include "Game.h"

namespace Game
{
Level::Level(Game *game)
    : _game(game), _config(NULL), _monsters(), _id(0) {

    // Do stuff
    _config = new LevelConfig();
    _config->nb = 0;
    load(_game->GetLevelFile());
}

Level::~Level() { }

void Level::load(std::string const &file) {

    std::ifstream isFile;
    isFile.open(file, std::ios::in|std::ios::binary);

    uint32 nb = 0;

    while(!isFile.eof())
    {
        isFile.read((char *)&(_config->collection[nb]), sizeof(QueenMonster));
        _config->nb = _config->nb + 1;
        nb++;
    }
}

float Level::_getRandomBetween(int min, int max) {

    std::random_device rd;
    std::uniform_int_distribution<int> generator(min, max);
    float random = (float)generator(rd);

    return random;
}

void Level::sendMonster(Monster *monster) {

    Packet pkt(SMSG_ADD_MONSTER);
    pkt <<  (uint8)monster->fire;
    pkt << (uint32)monster->id;
    pkt << (uint32)monster->type;
    pkt <<  _getRandomBetween(2000, 2400);
    pkt <<  (uint8)monster->health;
    pkt <<  _getRandomBetween(0, 1000);
    _game->BroadcastToAll(pkt);
    std::cout << "Monster = { id : " << monster->id << ", type : " << monster->type << " }" << std::endl;
}

Monster *Level::getMonster(uint32 id) {

    auto itr = _monsters.find(id);
    if (itr == _monsters.end())
        return NULL;
    return itr->second;
}

void Level::removeMonster(uint32 id) {

    _monsters.erase(id);
}

void Level::update(uint32 diff) {

    for (int i = 0; i < _config->nb; ++i) {

        QueenMonster *qm = &(_config->collection[i]);

        if (diff >= qm->timer && qm->nb > 0) {

            Monster *m = new Monster(qm->monster);
            m->id = _id++;
            _monsters[m->id] = m;
            sendMonster(m);
            qm->nb = qm->nb - 1;
            qm->timer = qm->pregnancy_time;
        }
        else {

            qm->timer -= diff;
        }
    }
}
}
