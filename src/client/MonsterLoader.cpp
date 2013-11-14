#include "MonsterLoader.hh"

MonsterLoader::MonsterLoader(std::string name) {

    save(name);
    load();
}

MonsterLoader::~MonsterLoader() {

    close();
}

void MonsterLoader::save(std::string pat) {

    if ((_handle = dlopen(pat.c_str(), RTLD_NOW)) == NULL)
        std::cerr << dlerror() << std::endl;
}

void MonsterLoader::load() {

    IMonster *m;
    void *(*fct)(int, int, glm::mat4);
      
    *(void**)(&fct) = dlsym(_handle, "createMonster");
    if (fct == NULL)
        std::cerr << dlerror() << std::endl;
    _monster = (IMonster*)((*fct)(400, 500,
                glm::translate(glm::mat4(), glm::vec3(0, 15, 0))));
}

void MonsterLoader::close() {

    dlclose(handle);
}
