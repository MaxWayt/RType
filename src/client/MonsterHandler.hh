#ifndef MONSTERHANDLER_H_
# define MONSTERHANDLER_H_

#include <random>
#include <utility>
#include "MonsterLoader.hh"

class MonsterHandler {

    private:
        int randomize(std::pair<int, int>);

    public:
        MonsterHandler(std::string, int, int, std::pair<int, int>, std::pair<int, int>);
        ~MonsterHandler() = default;

};

#endif
