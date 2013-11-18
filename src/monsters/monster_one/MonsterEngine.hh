#include <iostream>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IMonster.hh"
#include "APhysics.hh"

class Pattern : public DamnCute::APattern {

    public:
        explicit Pattern(glm::vec2 v) : _v(v) {
            initialize();
        }

        virtual ~Pattern() = default;
        virtual void initialize() {

            glm::mat4 m;
            m = glm::translate(glm::mat4(), glm::vec3(6, 0, 0));
            _x = new DamnCute::Path(m, 100, DamnCute::Bullet(glm::vec2(0, 0.0f), 0, 700), "../resources/mid_bullet_red.png");
            addPath(_x);
        }

    private:
        DamnCute::Path *_x;
        glm::vec2 _v;
        std::string _bundlePath;
};

class MonsterEngine : public DamnCute::IMonster, public DamnCute::APhysics {

    private:
        int _row;
        int _col;
        glm::mat4 _mov;
        sf::Texture _tex;
        sf::Sprite _sprite;
        int _life;
        Pattern *_pattern;
        DamnCute::Core *_engine;

        virtual void collisionHandler(DamnCute::APhysics*);
        void shoot();

        glm::vec2 convertVec(sf::Vector2f v) {
            return glm::vec2(float(v.x + 20), float(v.y + 35));
        }

    public:
        MonsterEngine(int, int);
        ~MonsterEngine();

        void update(sf::RenderTarget* w_ptr);

};
