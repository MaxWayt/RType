#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <APlayer.hh>
#include "Bullet.hh"
#include "Core/Core.hh"

DamnCute::Bullet::Bullet(const glm::vec2& origin, const float rot, unsigned int lifeTime, unsigned int owner) : APhysics(origin.x, origin.y, false, 0), _origin(origin), _rot(rot), _selfTransform(glm::translate(glm::rotate(glm::mat4(), rot, glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(-origin.x, -origin.y, 0))), _tex(NULL), _lifeTime(lifeTime), _id(owner) {
}

DamnCute::Bullet::Bullet(DamnCute::Bullet&& b) : APhysics(b._origin.x, b._origin.y, false, b.getType()), _origin(b._origin), _rot(b._rot), _selfTransform(glm::translate(glm::rotate(glm::mat4(), b._rot, glm::vec3(0.0f, 0.0f, 1.0f)), glm::vec3(-b._origin.x, -b._origin.y, 0))), _tex(b._tex), _lifeTime(b._lifeTime), _id(b._id) {
    if (b._tex) {
        _s.setTexture(*_tex);
        const sf::Vector2f& s = _s.getScale();
        _s.setOrigin(s.x / 2, s.y / 2);
    }
}

DamnCute::Bullet& DamnCute::Bullet::operator=(Bullet&& b) {
    _s = b._s;
    _lifeTime = b._lifeTime;
    return *this;
}

void DamnCute::Bullet::update(const glm::mat4& transform, sf::RenderTarget* w_ptr) {
    _selfTransform *= transform;

    glm::mat3 rotMat(_selfTransform);
    glm::vec3 d(_selfTransform[3]);
    glm::vec3 retVec = -d * rotMat;

    _s.setPosition(retVec.x, retVec.y);
    updateQuadTreePos(retVec.x, retVec.y);
    w_ptr->draw(_s);
    DamnCute::Core::getInstance()->addBulletsCounter();
}

void DamnCute::Bullet::setTexure(sf::Texture* tex) {
    _tex = tex;
    _s.setTexture(*_tex);
}

unsigned int DamnCute::Bullet::decreaseLifeTime() {
    if (_lifeTime) {
        --_lifeTime;
    }
    return _lifeTime;
}

void DamnCute::Bullet::collisionHandler(APhysics* other) {
    if (other->getType() == 1) {
        if (((DamnCute::APlayer*)(other))->isEmpty())
            sCore->delObject((DamnCute::APlayer*)other);
    }
}
