#include <iostream>
#include "Level.h"
#include "Game.h"

namespace Game
{
Level::Level(Game *game)
    : _game(game), _config(NULL), _monsters(), _id(0) {

    // Do stuff
    _config = new LevelConfig();
    _config->nb = 1;
    _config->collection[0].nb = 66;
    _config->collection[0].pregnancy_time = 5000;
    _config->collection[0].timer = 1200;
    _config->collection[0].monster.id = 0;
    _config->collection[0].monster.type = 0;
    _config->collection[0].monster.weapon = 0;
    _config->collection[0].monster.health = 100;
    _config->collection[0].monster.fire = 20;
    _config->collection[0].monster.x = 2000.0;
    _config->collection[0].monster.y = 500.0;
}

Level::~Level() {

}

void Level::sendMonster(Monster *monster) {

    Packet pkt(SMSG_ADD_MONSTER);
    pkt <<  (uint8)monster->fire; 
    pkt << (uint32)monster->id; 
    pkt << (uint32)monster->type; 
    pkt <<  (uint8)monster->weapon; 
    pkt <<  (float)monster->x; 
    pkt <<  (uint8)monster->health; 
    pkt <<  (float)monster->y; 
    _game->BroadcastToAll(pkt);
    std::cout << "Toto : " << monster->id << std::endl;    
}

void Level::update(uint32 diff) {

    for (int i = 0; i < _config->nb; ++i) {

        QueenMonster *qm = &(_config->collection[i]);

        if (diff >= qm->timer && qm->nb > 0) {

            Monster *m = new Monster(qm->monster);
            m->id = _id++;
            _monsters[_id] = m;
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
