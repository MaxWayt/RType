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

Monster* MonsterLoader::load(uint32 id, int row, int col) {

    void *(*fct)(uint32, int, int);
      
    *(void**)(&fct) = dlsym(_handle, "createMonster");
    if (fct == NULL)
        std::cerr << dlerror() << std::endl;
    return (Monster*)((*fct)(id, row, col));
}

void MonsterLoader::close() {

    dlclose(_handle);
}
