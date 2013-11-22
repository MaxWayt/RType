#ifndef MONSTERLOADER_H_
# define MONSTERLOADER_H_

#include <iostream>
#include <vector>
#if defined(UNIX)
# include <dlfcn.h>
#else
#include <WinBase.h>
#endif
#include <glm/gtc/matrix_transform.hpp>
#include "Monster.h"

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
