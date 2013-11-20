#ifndef ACTWEAPON_H_
# define ACTWEAPON_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Player.hh"
#include "Core/Core.hh"
#include "APattern.hh"
#include "Client.h"
#include "Opcodes.h"

#define TIME_SEPARATOR 6

class ShootPatternDefault : public DamnCute::APattern {
    public:
        explicit ShootPatternDefault(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~ShootPatternDefault() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(-15, 0, 0));
            _x = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _x->setPhysicBulletModelId(5);
            addPath(_x);
        }

    private:
        DamnCute::Path *_x;
        glm::vec2 _v;
        glm::mat4 _m;
};

class ShootPatternLevel1 : public DamnCute::APattern {
    public:
        explicit ShootPatternLevel1(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~ShootPatternLevel1() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(-15, 2, 0));
            _y = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _y->setPhysicBulletModelId(5);
            addPath(_y);

            _m = glm::translate(glm::mat4(), glm::vec3(-15, -2, 0));
            _z = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _z->setPhysicBulletModelId(5);
            addPath(_z);
        }

    private:
        DamnCute::Path *_y;
        DamnCute::Path *_z;
        glm::vec2 _v;
        glm::mat4 _m;
};

class ShootPatternLevel2 : public DamnCute::APattern {
    public:
        explicit ShootPatternLevel2(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~ShootPatternLevel2() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(-15, 0, 0));
            _x = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _x->setPhysicBulletModelId(5);
            addPath(_x);

            _m = glm::translate(glm::mat4(), glm::vec3(-15, 4, 0));
            _y = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _y->setPhysicBulletModelId(5);
            addPath(_y);

            _m = glm::translate(glm::mat4(), glm::vec3(-15, -4, 0));
            _z = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _z->setPhysicBulletModelId(5);
            addPath(_z);
        }

    private:
        DamnCute::Path *_x;
        DamnCute::Path *_y;
        DamnCute::Path *_z;
        glm::vec2 _v;
        glm::mat4 _m;
};

class ActWeapon : public DamnCute::AAction<DamnCute::APlayer>
{

    public:
        explicit ActWeapon(DamnCute::APlayer *p, sf::Keyboard::Key k1, int button)
            : AAction(p, k1, button), _level(0), _timeLoad(0) {
                _engine = DamnCute::Core::getInstance();
                _sp1 = new ShootPatternDefault(convertVec(_entity->getPlayer().getPosition()));
                _sp2 = new ShootPatternLevel1(convertVec(_entity->getPlayer().getPosition()));
                _sp3 = new ShootPatternLevel2(convertVec(_entity->getPlayer().getPosition()));
                _sp1->setStatusGen(false);
                _sp2->setStatusGen(false);
                _sp3->setStatusGen(false);
                _engine->addObject(_sp1);
                _engine->addObject(_sp2);
                _engine->addObject(_sp3);
                _name = "ActWeapon";
            }

        bool hasInput(int nbPlayer) {
            _nbPlayer = nbPlayer;
            if (sf::Keyboard::isKeyPressed(_key1))
                return true;
            else if (sf::Joystick::isButtonPressed(_nbPlayer, _stickButton) == true)
                return true;
            else {
                _sp1->setStatusGen(false);
                _sp2->setStatusGen(false);
                _sp3->setStatusGen(false);
                return false;
            }
        }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }

        void execute() {

            if ( _timeLoad == TIME_SEPARATOR)
            {
                _timeLoad = 0;
                sf::Vector2f const& pos = _entity->getPlayer().getPosition();
                Packet pkt(CMSG_SHOT);
                pkt << pos.x;
                pkt << pos.y;
                pkt << uint8(_level);
                sClient->UDPSend(pkt);
            }
            else
                ++_timeLoad;

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

        void levelUp() {
            ++_level;
        }

        virtual ~ActWeapon() = default;

    private:
        int _nbPlayer;
        int _level;
        std::string _name;
        ShootPatternDefault *_sp1;
        ShootPatternLevel1 *_sp2;
        ShootPatternLevel2 *_sp3;
        DamnCute::Core *_engine;
        unsigned int _timeLoad;

};

#endif /* !ACTWEAPON_H_ */
