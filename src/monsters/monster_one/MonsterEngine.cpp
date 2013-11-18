#include "MonsterEngine.hh"

MonsterEngine::MonsterEngine(int row, int col) :
    DamnCute::APhysics(row, col, true), _row(row), _col(col), _tex(), _life(4), _isDead(false) {

    _tex.loadFromFile("../resources/dango_monster.png");
    _sprite.setPosition(row, col);
    _sprite.setTexture(_tex);
    _sprite.setScale(0.3, 0.3);
    shoot();
}

MonsterEngine::~MonsterEngine() {

    _engine->delObject(_pattern);
}

void MonsterEngine::update(sf::RenderTarget* w_ptr) {

    updateQuadTreePos(_sprite.getPosition().x, _sprite.getPosition().y);
    if (_life == 0)
        _isDead = true;
    _sprite.move(-1, 0);
    _pattern->moveOrigin(convertVec(_sprite.getPosition()));
    w_ptr->draw(_sprite);
}

void MonsterEngine::collisionHandler(DamnCute::APhysics* other) {

    //death condition
    _life--;
    ((DamnCute::Bullet*)other)->setLife(0);
}

void MonsterEngine::shoot() {

    _engine = DamnCute::Core::getInstance();
    _pattern = new Pattern(convertVec(_sprite.getPosition()));
    _pattern->setStatusGen(true);
    _engine->addObject(_pattern);
}

bool MonsterEngine::isDead() const {
    return _isDead;
}
