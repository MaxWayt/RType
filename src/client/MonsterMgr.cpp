#include "MonsterMgr.h"

void MonsterMgr::addMonterLoader(std::string const& name)
{
    MonsterLoader* loader = new MonsterLoader(name);

    _monsterLoaders[_nextId++] = loader; 
}

Monster* MonsterMgr::createMonster(uint32 type, int32 x, int32 y)
{
    auto itr = _monsterLoaders.find(type);
    if (itr != _monsterLoaders.end())
        return itr->second->load(x, y);
    return NULL;
}
