#ifndef MONSTERLOADER_H_
# define MONSTERLOADER_H_

# include <iostream>
# include <vector>
# include <dlfcn.h>
# include <glm/gtc/matrix_transform.hpp>
# include "Monster.h"

class MonsterLoader {

    public:
        MonsterLoader(std::string);
        ~MonsterLoader();

        Monster* load(int, int);
    private:
        void *_handle;

        void save(std::string);
        void close();


};

#endif
