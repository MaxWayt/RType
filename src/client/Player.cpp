#include "Player.hh"

#include "Actions/ActMoveX.hh"
#include "Actions/ActMoveY.hh"
#include "Actions/ActFocus.hh"
#include "Actions/ActWeapon.hh"

Player::Player(const std::string& texfile, float x, float y, int speed, bool active, int num) :
APlayer(texfile, x, y, num, speed, active),
_fire(false), _sp1(NULL), _sp2(NULL), _sp3(NULL), _level(0), _health(5)
{
    if (_active)
    {
        addAction(new ActMoveX(this, sf::Keyboard::Key::Left,
                    sf::Keyboard::Key::Right, sf::Joystick::X));
        addAction(new ActMoveY(this, sf::Keyboard::Key::Up,
                    sf::Keyboard::Key::Down, sf::Joystick::Y));
        addAction(new ActFocus(this, sf::Keyboard::Key::LShift, 2));
        addAction(new ActWeapon(this, sf::Keyboard::Key::W, 0));
    }

    DamnCute::Core* engine = DamnCute::Core::getInstance();
    _sp1 = new ShootPatternDefault(convertVec(getPlayer().getPosition()), num);
    _sp2 = new ShootPatternLevel1(convertVec(getPlayer().getPosition()), num);
    _sp3 = new ShootPatternLevel2(convertVec(getPlayer().getPosition()), num);
    _sp1->setStatusGen(false);
    _sp2->setStatusGen(false);
    _sp3->setStatusGen(false);
    engine->addObject(_sp1);
    engine->addObject(_sp2);
    engine->addObject(_sp3);
}

Player::~Player()
{
    _sp1->setStatusGen(false);
    _sp2->setStatusGen(false);
    _sp3->setStatusGen(false);
}

void Player::collisionHandler(DamnCute::APhysics* other) {

    DamnCute::Bullet* b = (DamnCute::Bullet*)other;
    if (!other->isDestructible() && preciseDetection(getPlayer(), b->getSprite()) && (other->getType() == 4)) {
        std::cout << "argh player is dead!" << std::endl;
        b->setLife(0);
    }
    /*if (!other->isDestructible() && preciseDetection(getPlayer(), b->getSprite())) {
      b->setLife(0);
      }*/
}

void Player::SetFire(bool fire)
{
    _fire = fire;
    if (!fire)
    {
        _sp1->setStatusGen(false);
        _sp2->setStatusGen(false);
        _sp3->setStatusGen(false);
    }
    else
    {
        UpdateFirePosition();
        switch (_level)
        {
            case 0:
                {
                    _sp1->setStatusGen(true);
                    break;
                }
            case 1:
                {
                    _sp2->setStatusGen(true);
                    break;
                }
            case 2:
                {
                    _sp3->setStatusGen(true);
                    break;
                } 
        }
    }
}

void Player::UpdateFirePosition()
{
    _sp1->moveOrigin(convertVec(getPlayer().getPosition()));
    _sp2->moveOrigin(convertVec(getPlayer().getPosition()));
    _sp3->moveOrigin(convertVec(getPlayer().getPosition()));
}

