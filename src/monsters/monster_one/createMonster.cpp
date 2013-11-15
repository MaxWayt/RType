#include "IMonster.hh"
#include "MonsterEngine.hh"

extern "C" DamnCute::IMonster* createMonster(int row, int col, glm::mat4 mov)
{
    MonsterEngine *lib;

    lib = new MonsterEngine(row, col, mov);
    return (lib);
}
