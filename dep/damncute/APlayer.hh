#ifndef APLAYER_H_
# define APLAYER_H_

#include <iostream>
#include <vector>
#include <type_traits>
#include <stack>
#include "AAction.hh"
#include "IRenderable.hh"
#include "Core/Core.hh"
#include "APhysics.hh"

namespace DamnCute
{
#ifdef __PLAYER_PHYSIC_ID__
#undef __PLAYER_PHYSIC_ID__
#endif
#define __PLAYER_PHYSIC_ID__ 1

    class Life : public DamnCute::IRenderable {

        private:
            sf::Sprite _sprite;
            sf::Texture _tex;

        public:
            Life(std::string sprite, int offset) {
                _tex.loadFromFile(sprite);
                _sprite.setTexture(_tex);
                _sprite.setPosition(offset, 10);
                _sprite.setScale(0.15, 0.15);
            }
            ~Life() {}

            void update(sf::RenderTarget* a) {
                a->draw(_sprite);
            }
    };

    class APlayer : public IRenderable, public APhysics
    {

        public:
            explicit APlayer(const std::string& = "resources/player.tga",
                    float = 980, float = 950, int nbPlayer = 1, int speed = 5, bool active = true);
            virtual ~APlayer() {}

            void update(sf::RenderTarget*);
            void addAction(AAction<APlayer>*);

            inline sf::Sprite& getPlayer() { return _entity; }
            inline sf::Sprite const& getPlayer() const { return _entity; }
            inline sf::Texture& getTexture() { return _tex; }
            inline int& getSpeed() { return _speed; }
            inline AAction<APlayer>* getAction(std::string);
            inline int getNumPlayer() const { return _nbPlayer; }

            bool isEmpty() { return _life.empty(); }

            template <int inputNumber, typename T>
                void setAction(const std::string& name, T t) {

                    for (size_t i = 0; i < _actions.size(); ++i) {
                        if (name == (_actions[i])->getName())
                            setActionInput(i, t, inputNumber);
                    }
                }

            template <typename T>
                void setActionInput(int i, T t, int a);

        private:
            void action();
            std::vector<AAction<APlayer>*> _actions;

            sf::Sprite _entity;
            sf::Texture _tex;
            int _speed;
            int _nbPlayer;
            /*uint8*/int _health;

        protected:
            bool _active;
            std::stack<Life*> _life;
    };

}
#endif
