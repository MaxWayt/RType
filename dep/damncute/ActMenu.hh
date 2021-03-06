#ifndef _ACTMENU_H_
# define _ACTMENU_H_

#include <iostream>
#include "AAction.hh"
#include "Menu.hh"

#define K1 0
#define K2 1
#define ST1 2
#define ST2 3

class ActMenu : public DamnCute::AAction<DamnCute::Menu>
{

    public:
        explicit ActMenu(DamnCute::Menu *p, sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Joystick::Axis stAxis) : AAction(p, k1, k2, stAxis) {
            _name = "ActMenu";
        }

        bool hasInput(int nbPlayer) {
            if (sf::Keyboard::isKeyPressed(_key1)) {
                _who = K1;
                return true;
            }

            else if (sf::Keyboard::isKeyPressed(_key2)) {
                _who = K2;
                return true;
            }

            else if (hasStickAxis() == true) {

                if (sf::Joystick::getAxisPosition(nbPlayer, _stickAxis) < -50) {
                    _who = ST1;
                    return true;
                }

                else if (sf::Joystick::getAxisPosition(nbPlayer, _stickAxis) > 50) {
                    _who = ST2;
                    return true;
                }

            }
            return false;
        }

        void execute() {
            if ((_who == K2 || _who == ST2) && _key2 == sf::Keyboard::Key::Down)
                _entity->MoveDown();
            if ((_who == K1 || _who == ST1) && _key1 == sf::Keyboard::Key::Up)
                _entity->MoveUp();
            if ((_who == K2 || _who == ST2) && _key2 == sf::Keyboard::Key::Left)
                _entity->MoveLeft();
            if ((_who == K1 || _who == ST1) && _key1 == sf::Keyboard::Key::Right)
                _entity->MoveRight();
            if ((_who == K1 || _who == ST1) && _key1 == sf::Keyboard::Return && _entity->getAlive() == true)
                _entity->MoveReturn();
            if ((_who == K2 || _who == ST2) && _key2 == sf::Keyboard::Escape && _entity->getAlive() == false)
                _entity->MoveReturn();
        }
        virtual inline const std::string& getName() const { return (_name); }
        virtual ~ActMenu() {}

    private:
        int _who;
        std::string _name;

};

#endif
