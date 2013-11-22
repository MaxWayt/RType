#ifndef ACTWEAPON_H_
# define ACTWEAPON_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Player.hh"
#include "Core/Core.hh"
#include "APattern.hh"
#include "Client.h"
#include "Opcodes.h"


class ActWeapon : public DamnCute::AAction<DamnCute::APlayer>
{

    public:
        explicit ActWeapon(DamnCute::APlayer *p, sf::Keyboard::Key k1, int button)
            : AAction(p, k1, button), _shooting(false) {

                _name = "ActWeapon";
            }

        bool hasInput(int nbPlayer) {
            _nbPlayer = nbPlayer;
            if (sf::Keyboard::isKeyPressed(_key1))
                return true;
            else if (sf::Joystick::isButtonPressed(_nbPlayer, _stickButton) == true)
                return true;
            else if (_shooting)
            {
                std::cout << "SEND SHOT STOP" << std::endl;
                _shooting = false;
                Packet pkt(CMSG_SHOT);
                pkt << uint8(0);
                sClient->UDPSend(pkt);
            }
            return false;
        }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }

        void execute() {

            if (!_shooting)
            {
                std::cout << "SEND SHOT START" << std::endl;
                _shooting = true;
                Packet pkt(CMSG_SHOT);
                pkt << uint8(1);
                sClient->UDPSend(pkt);
            }

            /*
            if (_level == 0) {
                _sp1->moveOrigin(convertVec(_entity->getPlayer().getPosition()));
                _sp1->setStatusGen(true);
            }
            else if (_level == 1) {
                _sp2->moveOrigin(convertVec(_entity->getPlayer().getPosition()));
                _sp2->setStatusGen(true);
            }
            else if (_level >= 2) {
                _sp3->moveOrigin(convertVec(_entity->getPlayer().getPosition()));
                _sp3->setStatusGen(true);
            } 
            */
        }

        virtual inline const std::string& getName() const { return _name; }

        virtual ~ActWeapon();

    private:
        int _nbPlayer;
        std::string _name;

        bool _shooting;

};

#endif /* !ACTWEAPON_H_ */
