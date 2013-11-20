#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

#include <iostream>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Monster.h"
#include "APhysics.hh"

class TestShootPattern : public DamnCute::APattern {

    public:
        explicit TestShootPattern(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~TestShootPattern() = default;
        virtual void initialize() {

            glm::mat4 m;
            m = glm::translate(glm::mat4(), glm::vec3(6, 0, 0));
            _x = new DamnCute::Path(m, 100, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 700), "../resources/mid_bullet_red.png");
            _x->setPhysicBulletModelId(4);
            addPath(_x);
        }

    private:
        DamnCute::Path *_x;
        glm::vec2 _v;
        std::string _bundlePath;
};

class MonsterTest : public Monster
{
    public:
        MonsterTest(int x, int y);

        void update(sf::RenderTarget* w_ptr);
};

#endif /* !MONSTERTEST_H_ */
