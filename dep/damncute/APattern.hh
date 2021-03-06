#ifndef APATTERN_H_
# define APATTERN_H_

#include <type_traits>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Path.hh"
#include "Core/Core.hh"
#include "IRenderable.hh"

namespace DamnCute {
#ifdef __BULLER_PHYSIC_ID__
#undef __BULLER_PHYSIC_ID__
#endif
#define __BULLER_PHYSIC_ID__ 0
    class APattern : public IRenderable {
	public:
	    APattern() {}

	    ~APattern() {
		for (unsigned int i = 0; i != _paths.size(); ++i) {
		    delete _paths[i];
		}
	    }
	    virtual void initialize() = 0;
	    virtual int addPath(Path* p) {
		_paths.push_back(p);
		return _paths.size() - 1;
	    }
	    virtual void update(sf::RenderTarget* w_ptr) {
		for (unsigned int i = 0; i != _paths.size(); ++i) {
		    _paths[i]->update(w_ptr);
		}
		up();
	    }
	    virtual void moveOrigin(glm::vec2&& n) {
		for (unsigned int i = 0; i != _paths.size(); ++i) {
		    _paths[i]->moveOrigin(std::move(n));
		}
	    }
	    virtual void switchGen() {
		for (unsigned int i = 0; i != _paths.size(); ++i) {
		    _paths[i]->switchGen();
		}
	    }
	    virtual void setStatusGen(bool&& b) {
		for (unsigned int i = 0; i != _paths.size(); ++i) {
		    _paths[i]->setStatusGen(std::move(b));
		}
	    }
	    virtual void countdownPushMoveModifier(unsigned int f, const glm::mat4& m, unsigned int pathNumber) {
		_paths[pathNumber]->countdownPushMoveModifier(f, m);
	    }

	    virtual void setTimeSeparator(unsigned int newT, unsigned int p) {
		_paths[p]->setTimeSeparator(newT);
	    }
	    virtual void deletePath(unsigned int p) {
		if (p > _paths.size()) {
		    return;
		}
		delete _paths[p];
		std::vector<Path*>::iterator it = _paths.begin();
		while (p) {
		    --p;
		    ++it;
		}
		_paths.erase(it);
	    }
	protected:
	    virtual void up() {}
	    std::vector<Path*> _paths;
    };
}

#endif /* !APATTERN_H_ */
