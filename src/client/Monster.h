#ifndef MONSTER_H_
# define MONSTER_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"
#include <iostream>
#include <vector>
#include "Bullet.hh"
#include "IMonster.hh"
#include "SharedDefines.h"
#include "ShootPattern.hpp"

#define MAX_SHOOT_PATTERN_COUNT 3

class Monster : public DamnCute::IMonster, public DamnCute::APhysics {

    public:
        Monster(int x, int y);
        virtual void collisionHandler(DamnCute::APhysics* other);

        void SetFire(bool fire);
        bool IsFire() const { return _fire; }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }

        void UpdateFirePosition();


        virtual void update(sf::RenderTarget* w_ptr) = 0;
        bool isDead() const { return _health > 0; }
    protected:
        bool _fire;

        DamnCute::APattern* _shootPattern[MAX_SHOOT_PATTERN_COUNT];

        uint8 _health;

        sf::Sprite _sprite;
        uint8 _weapon;
};

#endif /* !MONSTER_H_ */
