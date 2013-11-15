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

DamnCute::IMonster* MonsterLoader::load() {

    void *(*fct)(int, int, glm::mat4);
      
    *(void**)(&fct) = dlsym(_handle, "createMonster");
    if (fct == NULL)
        std::cerr << dlerror() << std::endl;
    _monster = (DamnCute::IMonster*)((*fct)(400, 500,
                glm::translate(glm::mat4(), glm::vec3(0, 15, 0))));
    return _monster;
}

void MonsterLoader::close() {

    dlclose(_handle);
}
