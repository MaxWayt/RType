#include "MonsterTest.h"

MonsterTest::MonsterTest(int x, int y) : Monster(x, y)
{

    _tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setTexture(_tex);
    _sprite.setScale(0.3, 0.3);

    DamnCute::Core* engine = DamnCute::Core::getInstance();
    _shootPattern = new TestShootPattern(convertVec(_sprite.getPosition()));
    _shootPattern->setStatusGen(false);
    engine->addObject(_shootPattern);
}

void MonsterTest::update(sf::RenderTarget* w_ptr) {

    updateQuadTreePos(_sprite.getPosition().x, _sprite.getPosition().y);
    _sprite.move(-1, 0);
    w_ptr->draw(_sprite);
}
