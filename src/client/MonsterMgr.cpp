#include "MonsterMgr.h"

void MonsterMgr::addMonterLoader(std::string const& name)
{
#ifdef OSX
    MonsterLoader* loader = new MonsterLoader(std::string("../lib/lib" + name + ".dylib"));
#elif defined(LINUX)
    MonsterLoader* loader = new MonsterLoader(std::string("../lib/lib" + name + ".so"));
#else
    MonsterLoader* loader = new MonsterLoader(std::string("../lib/" + name + ".dll"));
#endif

    _monsterLoaders[_nextId++] = loader; 
}

Monster* MonsterMgr::createMonster(uint32 id, uint32 type, int32 x, int32 y)
{
    auto itr = _monsterLoaders.find(type);
    if (itr != _monsterLoaders.end())
        return itr->second->load(id, x, y);
    return NULL;
}
