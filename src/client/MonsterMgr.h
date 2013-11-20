#ifndef MONSTERMGR_H_
# define MONSTERMGR_H_

#include "MonsterLoader.hh"
#include "Singleton.hpp"

class MonsterMgr : public Singleton<MonsterMgr>
{
public:
    MonsterMgr() : _monsterLoaders(), _nextId(0) {}
    void addMonterLoader(std::string const& name);

    Monster* createMonster(uint32 type, int32 x, int32 y);
private:
    std::map<uint32, MonsterLoader*> _monsterLoaders;
    uint32 _nextId;
};

#endif /* !MONSTERMGR_H_ */
