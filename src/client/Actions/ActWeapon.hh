#ifndef ACTWEAPON_H_
# define ACTWEAPON_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"

class ShootPattern : public DamnCute::APattern {
    public:
        explicit ShootPattern(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~ShootPattern() = default;
        virtual void initialize() {

            glm::mat4 m;
            m = glm::translate(glm::mat4(), glm::vec3(-15, 0, 0));
            _x = new DamnCute::Path(m, 6, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            addPath(_x);

            m = glm::translate(glm::mat4(), glm::vec3(-15, 4, 0));
            _y = new DamnCute::Path(m, 6, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            addPath(_y);

            m = glm::translate(glm::mat4(), glm::vec3(-15, -4, 0));
            _z = new DamnCute::Path(m, 6, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            addPath(_z);
        }

    private:
        DamnCute::Path *_x;
        DamnCute::Path *_y;
        DamnCute::Path *_z;
        glm::vec2 _v;
        std::string _bundlePath;
};

class ActWeapon : public DamnCute::AAction<DamnCute::APlayer>
{

    public:
        explicit ActWeapon(DamnCute::APlayer *p, sf::Keyboard::Key k1, int button)
            : AAction(p, k1, button) {
                _engine = DamnCute::Core::getInstance();
                _sp = new ShootPattern(convertVec(_entity->getPlayer().getPosition()));
                _sp->setStatusGen(false);
                _name = "ActWeapon";
                _engine->addObject(_sp);
            }

        bool hasInput(int nbPlayer) {
            _nbPlayer = nbPlayer;
            if (sf::Keyboard::isKeyPressed(_key1))
                return true;
            else if (sf::Joystick::isButtonPressed(_nbPlayer, _stickButton) == true)
                return true;
            else {
                _sp->setStatusGen(false);
                return false;
            }
        }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x), float(v.y));
        }

        void execute() {
            _sp->moveOrigin(convertVec(_entity->getPlayer().getPosition()));
            _sp->setStatusGen(true);
        }

        virtual inline const std::string& getName() const { return _name; }

        virtual ~ActWeapon() = default;

    private:
        int _nbPlayer;
        std::string _name;
        ShootPattern *_sp;
        DamnCute::Core *_engine;

};

#endif /* !ACTWEAPON_H_ */
