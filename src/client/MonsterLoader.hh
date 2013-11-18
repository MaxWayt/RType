#ifndef MONSTERLOADER_H_
# define MONSTERLOADER_H_

# include <iostream>
# include <vector>
# include <dlfcn.h>
# include <glm/gtc/matrix_transform.hpp>
# include "IMonster.hh"

class MonsterLoader {

    private:
        DamnCute::IMonster *_monster;
        void *_handle;

        void save(std::string);
        void close();

    public:
        MonsterLoader(std::string);
        ~MonsterLoader();

        DamnCute::IMonster* load(int, int);
        DamnCute::IMonster* getMonster();

};

#endif
