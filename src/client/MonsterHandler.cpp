#include "MonsterHandler.hh"

MonsterHandler::MonsterHandler(std::string soName, int nbrMonster, int lifetime, std::pair<int, int> limitX, std::pair<int, int> limitY)
    : _lifetime(lifetime) {

        for (size_t i = 0; i < nbrMonster; ++i) {
            _monster.push_back(new MonsterLoader(std::string("./" + soName + ".so")));
            DamnCute::sCore->addObject(_monster[i]->load(randomize(limitX), randomize(limitY)));
        }
    }

int MonsterHandler::randomize(std::pair<int, int> pair) {

    std::random_device rd;
    std::uniform_int_distribution<int> generator(pair.first, pair.second);
    int random = generator(rd);
    return random;
}

void MonsterHandler::deleteMonstersAtTime() {

    if (_lifetime > 0)
        _lifetime--;

    if (_lifetime == 0) {

        for (size_t i = 0; i < _monster.size(); ++i) {
            DamnCute::sCore->delObject(_monster[i]->getMonster());
        }
        _monster.clear();
    }
}

void MonsterHandler::update(sf::RenderTarget* w_ptr) {

    (void)w_ptr;
    deleteMonstersAtTime();
}
