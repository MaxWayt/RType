#ifndef SHOOTPATTERN_H_
# define SHOOTPATTERN_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"
#include <iostream>
#include <vector>
#include "Bullet.hh"
#include "SharedDefines.h"

#define TIME_SEPARATOR 6

class ShootPatternDefault : public DamnCute::APattern {
    public:
        explicit ShootPatternDefault(glm::vec2 v, bool reverse = false) : _v(v), _reverse(reverse) {
            initialize();
        }

        virtual ~ShootPatternDefault() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, 0, 0));
            _x = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _x->setPhysicBulletModelId(5);
            addPath(_x);
        }

    private:
        DamnCute::Path *_x;
        glm::vec2 _v;
        glm::mat4 _m;
        bool _reverse;
};

class ShootPatternLevel1 : public DamnCute::APattern {
    public:
        explicit ShootPatternLevel1(glm::vec2 v, bool reverse = false) : _v(v), _reverse(reverse) {
            initialize();
        }

        virtual ~ShootPatternLevel1() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, 2, 0));
            _y = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _y->setPhysicBulletModelId(5);
            addPath(_y);

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, -2, 0));
            _z = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _z->setPhysicBulletModelId(5);
            addPath(_z);
        }

    private:
        DamnCute::Path *_y;
        DamnCute::Path *_z;
        glm::vec2 _v;
        glm::mat4 _m;
        bool _reverse;
};

class ShootPatternLevel2 : public DamnCute::APattern {
    public:
        explicit ShootPatternLevel2(glm::vec2 v, bool reverse = false) : _v(v) _reverse(reverse) {
            initialize();
        }

        virtual ~ShootPatternLevel2() = default;
        virtual void initialize() {

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, 0, 0));
            _x = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _x->setPhysicBulletModelId(5);
            addPath(_x);

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, 4, 0));
            _y = new DamnCute::Path(_m, TIME_SEPARATOR, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 150), "../resources/pink-bullet.tga");
            _y->setPhysicBulletModelId(5);
            addPath(_y);

            _m = glm::translate(glm::mat4(), glm::vec3(_reverse ? 15 : -15, -4, 0));
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
        bool _reverse;
};

#endif /* !SHOOTPATTERN_H_ */
