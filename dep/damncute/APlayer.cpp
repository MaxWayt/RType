#include <iostream>
#include "APlayer.hh"

DamnCute::APlayer::APlayer(const std::string& texfile, float x, float y, int nb, int speed) :
    APhysics((int)x, (int)y, true), _tex(), _speed(speed), _nbPlayer(nb)
{
    _tex.loadFromFile(texfile);
    _entity.setTexture(_tex);
    const sf::Vector2f& s = _entity.getScale();
    _entity.setOrigin(s.x / 2, s.y / 2);
    _entity.setPosition(x, y);
}

void DamnCute::APlayer::update(sf::RenderTarget* w_ptr)
{
    action();
    w_ptr->draw(_entity);
    updateQuadTreePos((int)_entity.getPosition().x, (int)_entity.getPosition().y);
}

void DamnCute::APlayer::action()
{
    for (size_t i = 0; i < _actions.size(); ++i) {
        if (_actions[i]->hasInput(_nbPlayer) == true)
            _actions[i]->execute();
    }
}

void DamnCute::APlayer::addAction(AAction<APlayer>* act)
{
    _actions.push_back(act);
}

DamnCute::AAction<DamnCute::APlayer>* DamnCute::APlayer::getAction(std::string name) {
    for (size_t i = 0; i < _actions.size(); ++i) {
        if (_actions[i]->getName() == name)
            return _actions[i];
    }
    return nullptr;
}

namespace DamnCute {
    template <>
        void APlayer::setActionInput<sf::Keyboard::Key>(int i, sf::Keyboard::Key key, int inputNumber) {
            if (inputNumber == 1)
                (_actions[i])->setKeyboardInput1(key);
            else if (inputNumber == 2)
                (_actions[i])->setKeyboardInput2(key);
            else
                std::cerr << "Error: key should be 1 or 2" << std::endl;
        }

    template <>
        void APlayer::setActionInput<sf::Joystick::Axis>(int i, sf::Joystick::Axis axis, int a) {
            (void)a;
            (_actions[i])->setStickInput(axis);
        }

    template <>
        void APlayer::setActionInput<int>(int i, int button, int a) {
            (void)a;
            (_actions[i])->setStickInput(button);
        }
}
