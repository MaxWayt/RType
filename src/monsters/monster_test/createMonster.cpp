#include "Monster.h"
#include "MonsterTest.h"
#include <iostream>

#ifdef WIN32
extern "C" __declspec(dllexport) Monster* createMonster(unsigned int id, int x, int y)
#else
extern "C" Monster* createMonster(unsigned int id, int x, int y)
#endif
{
    return new MonsterTest(id, x, y);
}
