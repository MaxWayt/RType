#ifndef PLAYER_H_
# define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Core/Core.hh"
#include "APattern.hh"
#include "Bullet.hh"
#include "APlayer.hh"
#include "SharedDefines.h"
#include "ShootPattern.hpp"
#include <iostream>
#include <vector>

class Player : public DamnCute::APlayer {

    public:
        explicit Player(const std::string& texfile = "../resources/player.tga", float x = 980, float y = 950, int speed = 5, bool active = true, int num = 0);
        virtual ~Player();
        Player& operator=(const Player&);
        virtual void collisionHandler(DamnCute::APhysics* other);

        void levelUp() { ++_level; }

        void SetFire(bool fire);
        bool IsFire() const { return _fire; }

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 90), float(v.y + 11));
        }

        uint32 GetHealth() const { return _health; }
        void SetHealth(uint32 val) { _health = val; }
        bool IsAlive() const { return _health > 0; }

        void UpdateFirePosition();

        void RemoveLife();

    private:
        bool _fire;

        ShootPatternDefault *_sp1;
        ShootPatternLevel1 *_sp2;
        ShootPatternLevel2 *_sp3;


        sf::Sound _sound;
        sf::SoundBuffer _buffer;

        uint8 _level;
        uint32 _health;

};



#endif
