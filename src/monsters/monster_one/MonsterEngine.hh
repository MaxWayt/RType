#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IMonster.hh"

class MonsterEngine : public DamnCute::IMonster {

    private:
        int _row;
        int _col;
        glm::mat4 _mov;
        sf::Texture _tex;
        sf::Sprite _sprite;

    public:
        MonsterEngine(int, int, glm::mat4);
        ~MonsterEngine() = default;

        void shoot() {}
        void update(sf::RenderTarget* w_ptr);

};
