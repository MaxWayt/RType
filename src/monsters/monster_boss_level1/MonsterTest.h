#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

#include <iostream>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Monster.h"
#include "APhysics.hh"

class Boss1ShootPattern : public DamnCute::APattern {

    public:
        explicit Boss1ShootPattern(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~Boss1ShootPattern() {}
        virtual void initialize() {

            glm::mat4 m;
            m = glm::translate(glm::mat4(), glm::vec3(6, 2, 0));
            _x = new DamnCute::Path(m, 8, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 700), "../resources/mid_bullet_red.png");
            _x->setPhysicBulletModelId(4);
            addPath(_x);

            m = glm::translate(glm::mat4(), glm::vec3(6, -2, 0));
            _y = new DamnCute::Path(m, 8, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 700), "../resources/mid_bullet_red.png");
            _y->setPhysicBulletModelId(4);
            addPath(_y);

            m = glm::translate(glm::mat4(), glm::vec3(6, 0, 0));
            _z = new DamnCute::Path(m, 40, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 700), "../resources/mid_bullet_red.png");
            _z->setPhysicBulletModelId(4);
            addPath(_z);
        }

    private:
        DamnCute::Path *_x;
        DamnCute::Path *_y;
        DamnCute::Path *_z;
        glm::vec2 _v;
        std::string _bundlePath;
};

class MonsterTest : public Monster
{
    public:
        MonsterTest(unsigned int id, int x, int y);

        void update(sf::RenderTarget* w_ptr);

    private:
        bool _up;
};

#endif /* !MONSTERTEST_H_ */
