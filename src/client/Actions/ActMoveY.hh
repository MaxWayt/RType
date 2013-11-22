#ifndef _ACTMOVEY_H_
# define _ACTMOVEY_H_

#include "Opcodes.h"
#include "Packet.hpp"
#include "Client.h"

#define K1 0
#define K2 1

class ActMoveY : public DamnCute::AAction<DamnCute::APlayer>
{

    public:
        explicit ActMoveY(DamnCute::APlayer *p, sf::Keyboard::Key k1, sf::Keyboard::Key k2, sf::Joystick::Axis stAxis) : AAction(p, k1, k2, stAxis) {
            _name = "ActMoveY";
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
            if (_who == K1 && (_entity->getPlayer().getPosition().y > 0))
                _entity->getPlayer().move(0, -(_entity->getSpeed()));
            if (_who == K2 && (_entity->getPlayer().getPosition().y < 1080 - _entity->getPlayer().getTexture()->getSize().y))
                _entity->getPlayer().move(0, _entity->getSpeed());

            sf::Vector2f const& pos = _entity->getPlayer().getPosition();
            Packet pkt(CMSG_PLAYER_POSITION);
            pkt << pos.x;
            pkt << pos.y;
            sClient->UDPSend(pkt);
        }

        virtual inline const std::string& getName() const { return (_name); }

        virtual ~ActMoveY() {}

    private:
        int _who;
        std::string _name;

};

#endif
