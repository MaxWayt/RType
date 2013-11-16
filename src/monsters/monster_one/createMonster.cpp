#include "IMonster.hh"
#include "MonsterEngine.hh"

extern "C" DamnCute::IMonster* createMonster(int row, int col)
{
    MonsterEngine *lib;

    lib = new MonsterEngine(row, col);
    return (lib);
}
