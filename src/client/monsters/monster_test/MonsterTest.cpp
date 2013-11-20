#include "MonsterTest.h"

MonsterTest::MonsterTest(int x, int y) : Monster(x, y)
{

    sf::Texture tex;
    tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setTexture(tex);
    _sprite.setScale(0.3, 0.3);
}

void MonsterTest::update(sf::RenderTarget* w_ptr) {

    updateQuadTreePos(_sprite.getPosition().x, _sprite.getPosition().y);
    _sprite.move(-1, 0);
    w_ptr->draw(_sprite);
}
