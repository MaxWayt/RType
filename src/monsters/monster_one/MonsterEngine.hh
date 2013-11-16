#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IMonster.hh"
#include "APhysics.hh"

class MonsterEngine : public DamnCute::IMonster, public DamnCute::APhysics {

    private:
        int _row;
        int _col;
        glm::mat4 _mov;
        sf::Texture _tex;
        sf::Sprite _sprite;
        int _life;

        virtual void collisionHandler(DamnCute::APhysics*);

    public:
        MonsterEngine(int, int, glm::mat4);
        ~MonsterEngine() = default;

        void shoot() {}
        void update(sf::RenderTarget* w_ptr);

};
