#ifndef PLAYER_H_
# define PLAYER_H_

#include <iostream>
#include <vector>
#include "Bullet.hh"
#include "APlayer.hh"


class Player : public DamnCute::APlayer {

    public:
        explicit Player(const std::string& texfile = "../resources/player.tga", float x = 980, float y = 950, int speed = 5, bool active = true, int num = 0);
        virtual ~Player() = default;
        Player& operator=(const Player&) = delete;
        virtual void collisionHandler(DamnCute::APhysics* other);

        void levelUp();

        void SetFire(bool fire) { _fire = fire; }
        bool IsFire() const { return _fire; }
    private:
        bool _fire;
};



#endif
