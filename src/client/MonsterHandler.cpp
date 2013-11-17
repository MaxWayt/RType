#include "MonsterHandler.hh"

MonsterHandler::MonsterHandler(std::string soName, int nbrMonster, int lifetime, std::pair<int, int> limitX, std::pair<int, int> limitY) {

    std::vector<MonsterLoader*> monster;
    for (size_t i = 0; i < nbrMonster; ++i) {
        monster.push_back(new MonsterLoader(std::string("./" + soName + ".so")));
        DamnCute::sCore->addObject(monster[i]->load(randomize(limitX), randomize(limitY)));
    }
}

int MonsterHandler::randomize(std::pair<int, int> pair) {

    std::random_device rd;
    std::uniform_int_distribution<int> generator(pair.first, pair.second);
    int random = generator(rd);
    return random;
}
