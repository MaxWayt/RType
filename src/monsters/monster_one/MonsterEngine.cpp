#include "MonsterEngine.hh"

MonsterEngine::MonsterEngine(int row, int col, glm::mat4 mov) : _row(row), _col(col), _mov(mov), _tex() {

    _tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setTexture(_tex);
}

void MonsterEngine::update(sf::RenderTarget* w_ptr) {

    _sprite.move(1, 0);
    w_ptr->draw(_sprite);
}
