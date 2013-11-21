#include "Monster.h"
#include "MonsterTest.h"
#include <iostream>

extern "C" Monster* createMonster(unsigned int id, int x, int y)
{
    return new MonsterTest(id, x, y);
}
