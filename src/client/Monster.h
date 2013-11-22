#ifndef MONSTER_H_
# define MONSTER_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"
#include "Bullet.hh"
#include "IMonster.hh"
#include "SharedDefines.h"
#include <iostream>
#include <vector>

class Monster : public DamnCute::IMonster, public DamnCute::APhysics {

    public:
        Monster(uint32 id, int x, int y);
        virtual ~Monster();
        virtual void collisionHandler(DamnCute::APhysics* other);

        uint32 GetId() const { return _id; }

        void SetFire(bool fire);
        bool IsFire() const { return _fire; }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }

        void UpdateFirePosition();


        virtual void update(sf::RenderTarget* w_ptr) = 0;
        bool isDead() const { return _health > 0; }
        void SetHealth(uint8 val) { _health = val; }
    protected:
        uint32 _id;
        bool _fire;

        DamnCute::APattern* _shootPattern;

        uint8 _health;

        sf::Sprite _sprite;
        sf::Texture _tex;
};

#endif /* !MONSTER_H_ */
