#ifndef MONSTERLOADER_H_
# define MONSTERLOADER_H_

#include <glm/gtc/matrix_transform.hpp>
#include "Monster.h"
#include <iostream>
#include <vector>
#if defined(UNIX)
# include <dlfcn.h>
#else
#ifndef NOMINMAX
# define NOMINMAX
#endif
#include <windows.h>
#endif

class MonsterLoader {

    public:
        MonsterLoader(std::string);
        ~MonsterLoader();

        Monster* load(unsigned int, int, int);
    private:
        void *_handle;

        void save(std::string);
        void close();


};

#endif
