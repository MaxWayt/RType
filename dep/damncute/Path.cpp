#include <climits>
#include <glm/gtc/matrix_transform.hpp>
#include "Path.hh"

DamnCute::Path::Path(const glm::mat4& m, unsigned int timestep, DamnCute::Bullet&& model, const std::string& texfile) : _bulletModel(std::move(model)), _timeLoad(0), _timeSeparator(timestep), _stepModifier(m), _generate(true) {
    _tex.loadFromFile(texfile);
    _tex.setSmooth(true);
    _tex.setRepeated(false);
    _bulletModel.setTexure(&_tex);
}

void DamnCute::Path::update(sf::RenderTarget* w_ptr) {
    for (std::list<Bullet>::iterator it = _bullets.begin(); it != _bullets.end();) {
	(*it).update(_stepModifier, w_ptr);
	if ((*it).decreaseLifeTime() <= 0) {
	    it = _bullets.erase(it);
	} else {
	    ++it;
	}
    }

    if (_modEventStack.size() > 0) {
	if (_modEventStack.top()._futureframe == 0) {
	    _stepModifier = _modEventStack.top()._newMat;
	    _modEventStack.pop();
	} else {
	    -- _modEventStack.top()._futureframe;
	}
    }

    if (( _timeLoad == _timeSeparator) && (_generate)) {
        _timeLoad = 0;
        _bullets.push_back(std::move(_bulletModel));
    } else if (_generate){
	++_timeLoad;
    }
}

void DamnCute::Path::countdownPushMoveModifier(unsigned int framme, const glm::mat4& newMat) {
	modEvent event = {framme, newMat};
    _modEventStack.push(event);
}

void DamnCute::Path::setPhysicBulletModelId(unsigned int id) {
    _bulletModel.setType(id);
}

void DamnCute::Path::setAllPhysicBulletId(unsigned int id) {
    for (std::list<Bullet>::iterator it = _bullets.begin(); it != _bullets.end(); ++it) {
	(*it).setType(id);
    }
}
