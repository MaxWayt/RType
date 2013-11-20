#ifndef BULLET_H_
# define BULLET_H_

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "APhysics.hh"

namespace DamnCute {
    class Bullet : public APhysics {
        public:
            explicit Bullet(const glm::vec2&, const float = 0.0f, unsigned int = 60, unsigned int = 0);
            explicit Bullet(const Bullet&) = delete;
            explicit Bullet(Bullet&&);
            virtual ~Bullet() = default;
            Bullet& operator=(const Bullet&) = delete;
            Bullet& operator=(Bullet&&);
            void update(const glm::mat4&, sf::RenderTarget*);
            unsigned int decreaseLifeTime();
            inline const sf::Sprite& getSprite() const noexcept {
                return _s;
            }
            inline const glm::vec2& getOrigin() const noexcept {
                return _origin;
            }
            inline float getRot() const noexcept {
                return _rot;
            }
            inline unsigned int getLife() const noexcept {
                return _lifeTime;
            }
            inline void setLife(unsigned int l) noexcept {
                _lifeTime = l;
            }
            inline void moveOrigin(glm::vec2&& n) noexcept {
                _origin = n;
            }
            void setTexure(sf::Texture*);
            virtual void collisionHandler(APhysics*);

            unsigned int getOwnerId() const { return _id; }
        private:
            glm::vec2 _origin;
            float _rot;
            glm::mat4 _selfTransform;
            sf::Texture* _tex; // TODO : need to be deleted or changed by referance
            sf::Sprite _s;
            unsigned int _lifeTime;
            unsigned int _id;
    };
}

#endif
