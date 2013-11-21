#include "MonsterTest.h"

MonsterTest::MonsterTest(unsigned int id, int x, int y) : Monster(id, x, y)
{

    _tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setTexture(_tex);
    _sprite.setScale(0.5, 0.5);

    DamnCute::Core* engine = DamnCute::Core::getInstance();
    _shootPattern = new Test2ShootPattern(convertVec(_sprite.getPosition()));
    _shootPattern->setStatusGen(false);
    engine->addObject(_shootPattern);
}

void MonsterTest::update(sf::RenderTarget* w_ptr) {

    updateQuadTreePos(_sprite.getPosition().x, _sprite.getPosition().y);
    _sprite.move(-1, 0);
    w_ptr->draw(_sprite);
}
