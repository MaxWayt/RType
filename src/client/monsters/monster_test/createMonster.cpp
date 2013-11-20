#include "Monster.h"
#include "MonsterTest.h"

extern "C" Monster* createMonster(int x, int y)
{
    return new MonsterTest(x, y);
}
