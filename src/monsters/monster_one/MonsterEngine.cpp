#include "MonsterEngine.hh"

MonsterEngine::MonsterEngine(int row, int col, glm::mat4 mov) :
    DamnCute::APhysics(row, col, true), _row(row), _col(col), _mov(mov), _tex(), _life(4) {

    _tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setPosition(row, col);
    _sprite.setTexture(_tex);
    _sprite.setScale(0.3, 0.3);

    shoot();
}

void MonsterEngine::update(sf::RenderTarget* w_ptr) {

    if (_life == 0)
        std::cout << "apu vie" << std::endl;
    _sprite.move(-1, 0);
    _pattern->moveOrigin(convertVec(_sprite.getPosition()));
    w_ptr->draw(_sprite);
}

void MonsterEngine::collisionHandler(DamnCute::APhysics* other) {

    _life--;
    std::cout << "collision avec un monstre" << std::endl;
}

void MonsterEngine::shoot() {

    _engine = DamnCute::Core::getInstance();
    _pattern = new Pattern(convertVec(_sprite.getPosition()));
    _pattern->setStatusGen(true);
    _engine->addObject(_pattern);
}
