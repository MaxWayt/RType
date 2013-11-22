#include "MonsterLoader.hh"

MonsterLoader::MonsterLoader(std::string name) {

    save(name);
}

MonsterLoader::~MonsterLoader() {

    close();
}

void MonsterLoader::save(std::string pat) {

    std::cout << "Load monster library " << pat << std::endl;
#ifdef UNIX
    if ((_handle = dlopen(pat.c_str(), RTLD_NOW)) == NULL)
        std::cerr << dlerror() << std::endl;
#else
	if ((_handle = LoadLibrary(pat.c_str())) == NULL)
		std::cerr << "Fail to load " << pat << std::endl;
#endif
}

Monster* MonsterLoader::load(uint32 id, int row, int col) {

    void *(*fct)(uint32, int, int);
      
#ifdef UNIX
    *(void**)(&fct) = dlsym(_handle, "createMonster");
#else
	FARPROC proc = GetProcAddress((HMODULE)_handle, "createMonster");
	*(void**)(&fct) = proc;
#endif
    if (fct == NULL)
    {
#ifdef UNIX
        std::cerr << dlerror() << std::endl;
#else
		std::cerr << "Fail to get \"createMonster\" address" << std::endl;
#endif
        return NULL;
    }
    return (Monster*)((*fct)(id, row, col));
}

void MonsterLoader::close() {
#ifdef UNIX
    dlclose(_handle);
#else
		FreeLibrary((HMODULE)_handle);
#endif
}
