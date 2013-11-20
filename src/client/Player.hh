#ifndef PLAYER_H_
# define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"
#include <iostream>
#include <vector>
#include "Bullet.hh"
#include "APlayer.hh"
#include "SharedDefines.h"

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

class Player : public DamnCute::APlayer {

    public:
        explicit Player(const std::string& texfile = "../resources/player.tga", float x = 980, float y = 950, int speed = 5, bool active = true, int num = 0);
        virtual ~Player() = default;
        Player& operator=(const Player&) = delete;
        virtual void collisionHandler(DamnCute::APhysics* other);

        void levelUp() { ++_level; }

        void SetFire(bool fire);
        bool IsFire() const { return _fire; }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }
    private:
        bool _fire;

        ShootPatternDefault *_sp1;
        ShootPatternLevel1 *_sp2;
        ShootPatternLevel2 *_sp3;
        uint8 _level;
};



#endif
