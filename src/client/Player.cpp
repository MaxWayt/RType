#include "Player.hh"

#include "Actions/ActMoveX.hh"
#include "Actions/ActMoveY.hh"
#include "Actions/ActFocus.hh"
#include "Actions/ActWeapon.hh"

Player::Player(const std::string& texfile, float x, float y, int speed, bool active, int num) :
APlayer(texfile, x, y, num, speed, active),
_fire(false)
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
}

void Player::collisionHandler(DamnCute::APhysics* other) {

    DamnCute::Bullet* b = (DamnCute::Bullet*)other;
    if (other->getType() == 4) {
        std::cout << "argh player is dead!" << std::endl;
        b->setLife(0);
    }
    /*if (!other->isDestructible() && preciseDetection(getPlayer(), b->getSprite())) {
      b->setLife(0);
      }*/
}


void Player::levelUp() {
    //getAction("ActWeapon")->levelUp();
}
