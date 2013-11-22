#include "MonsterTest.h"

MonsterTest::MonsterTest(unsigned int id, int x, int y) : Monster(id, x, y), _up(false)
{

    _tex.loadFromFile("../resources/mart_s.jpg");
    _sprite.setTexture(_tex);
    _sprite.setScale(1.2, 1.2);

    DamnCute::Core* engine = DamnCute::Core::getInstance();
    _shootPattern = new Boss1ShootPattern(convertVec(_sprite.getPosition()));
    _shootPattern->setStatusGen(false);
    engine->addObject(_shootPattern);
}

void MonsterTest::update(sf::RenderTarget* w_ptr) {

    updateQuadTreePos(_sprite.getPosition().x, _sprite.getPosition().y);
    if (_sprite.getPosition().x > 1450)
        _sprite.move(-1, 0);
    else
        if (_up)
        {
            if (_sprite.getPosition().y > 800)
                _up = false;
            else
                _sprite.move(0, 1);
        }
        else
        {

            if (_sprite.getPosition().y < 40)
                _up = true;
            else
                _sprite.move(0, -1);
        }
    w_ptr->draw(_sprite);
}
