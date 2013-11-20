#include "Monster.h"

Monster::Monster(int x, int y) : DamnCute::APhysics(x, y, true),
    _fire(false), _health(5), _sprite(), _weapon(0)
{
    _sprite.setPosition(x, y);

    DamnCute::Core* engine = DamnCute::Core::getInstance();
    _shootPattern[0] = new ShootPatternDefault(convertVec(_sprite.getPosition()), true);
    _shootPattern[1] = new ShootPatternLevel1(convertVec(_sprite.getPosition()), true);
    _shootPattern[2] = new ShootPatternLevel2(convertVec(_sprite.getPosition()), true);
    _shootPattern[0]->setStatusGen(false);
    _shootPattern[1]->setStatusGen(false);
    _shootPattern[2]->setStatusGen(false);
    engine->addObject(_shootPattern[0]);
    engine->addObject(_shootPattern[1]);
    engine->addObject(_shootPattern[2]);


}

void Monster::collisionHandler(DamnCute::APhysics* other) {

    // 5 == player bullets
    if (other->getType() == 5) {
        _health--;
        ((DamnCute::Bullet*)other)->setLife(0);
    }
}

void Monster::SetFire(bool fire)
{
    _fire = fire;
    if (!fire)
    {
        for (uint8 i = 0; i < MAX_SHOOT_PATTERN_COUNT; ++i)
            _shootPattern[i]->setStatusGen(false);
    }
    else
    {
        if (_weapon >= MAX_SHOOT_PATTERN_COUNT)
            return;
        UpdateFirePosition();
        _shootPattern[_weapon]->setStatusGen(true);
    }
}

void Monster::UpdateFirePosition()
{
    for (uint8 i = 0; i < MAX_SHOOT_PATTERN_COUNT; ++i)
        _shootPattern[i]->moveOrigin(convertVec(_sprite.getPosition()));
}
