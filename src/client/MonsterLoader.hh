#ifndef MONSTERLOADER_H_
# define MONSTERLOADER_H_

# include <iostream>
# include <vector>
# include <dlfcn.h>
# include <glm/gtc/matrix_transform.hpp>
# include "IMonster.hh"

class MonsterLoader {

    private:
        IMonster *_monster;
        void *_handle;

        void save(std::string);
        void load();
        void close();

    public:
        MonsterLoader(std::string);
        ~MonsterLoader();

};

#endif
