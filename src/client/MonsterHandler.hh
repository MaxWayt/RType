#ifndef MONSTERHANDLER_H_
# define MONSTERHANDLER_H_

#include <random>
#include <utility>
#include "IRenderable.hh"
#include "MonsterLoader.hh"

class MonsterHandler : public DamnCute::IRenderable {

    private:
        std::vector<MonsterLoader*> _monster;
        int randomize(std::pair<int, int>);
        int _lifetime;

        void deleteMonstersAtTime();

    public:
        MonsterHandler(std::string, int, int, std::pair<int, int>, std::pair<int, int>);
        ~MonsterHandler() = default;

        virtual void update(sf::RenderTarget*);

};

#endif
