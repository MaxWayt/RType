#include "MonsterLoader.hh"

MonsterLoader::MonsterLoader(std::string name) {

    save(name);
}

MonsterLoader::~MonsterLoader() {

    close();
}

void MonsterLoader::save(std::string pat) {

    if ((_handle = dlopen(pat.c_str(), RTLD_NOW)) == NULL)
        std::cerr << dlerror() << std::endl;
}

DamnCute::IMonster* MonsterLoader::load(int row, int col) {

    void *(*fct)(int, int);
      
    *(void**)(&fct) = dlsym(_handle, "createMonster");
    if (fct == NULL)
        std::cerr << dlerror() << std::endl;
    _monster = (DamnCute::IMonster*)((*fct)(row, col));
    return _monster;
}

DamnCute::IMonster *MonsterLoader::getMonster() {

    return _monster;
}

void MonsterLoader::close() {

    dlclose(_handle);
}
