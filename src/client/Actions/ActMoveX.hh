#ifndef _ACTMOVEX_H_
# define _ACTMOVEX_H_

#include "Opcodes.h"
#include "Packet.hpp"
#include "Client.h"

#define K1 0
#define K2 1

class ActMoveX : public DamnCute::AAction<DamnCute::APlayer>
{

    public:
        explicit ActMoveX(DamnCute::APlayer *p, sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Joystick::Axis stAxis) : AAction(p, k1, k2, stAxis) {
            _name = "ActMoveX";
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
                    _who = K1;
                    return true;
                }

                else if (sf::Joystick::getAxisPosition(nbPlayer, _stickAxis) > 50) {
                    _who = K2;
                    return true;
                }

            }
            return false;
        }

        void execute() {
            if (_who == K1 && (_entity->getPlayer().getPosition().x > 0))
                _entity->getPlayer().move(-(_entity->getSpeed()), 0);
            if (_who == K2 && _entity->getPlayer().getPosition().x < 1920 - _entity->getPlayer().getTexture()->getSize().x)
                _entity->getPlayer().move(_entity->getSpeed(), 0);

            sf::Vector2f const& pos = _entity->getPlayer().getPosition();
            Packet pkt(CMSG_PLAYER_POSITION);
            pkt << pos.x;
            pkt << pos.y;
            sClient->UDPSend(pkt);

        }

        virtual inline const std::string& getName() const { return (_name); }

        virtual ~ActMoveX() {}

    private:
        int _who;
        std::string _name;

};

#endif
