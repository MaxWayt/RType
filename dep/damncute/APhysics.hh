#ifndef APHISICS_H_
# define APHISICS_H_

#include <iostream>
#include <utility>
#include "Core/Core.hh"

/*
 * -----
 * |A|B|
 * -----
 * |C|D|
 * -----
 */

namespace DamnCute {
    class APhysics {
	private:
	    bool _physicallyActive;
	    bool _destructible;
	    bool _isInList;
	    unsigned int _type;

	    QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>* _quadTree;
	    QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_ _path;
	    std::list<APhysics*>* _listSection;
	    std::list<APhysics*>::iterator _whereInList;

	    template <unsigned int sizeX, unsigned int sizeY, unsigned short iter>
		inline QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_&& generateQuadTreePos(unsigned int x, unsigned int y) noexcept {
		    unsigned int nodeX = sizeX / 2;
		    unsigned int nodeY = sizeY / 2;

		    for (unsigned short i = 0; i < iter; ++i)
		    {
			if (x < nodeX && y > nodeY)
			{
			    _path[i] = QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::AZone;
			    nodeX -= nodeX / 2;
			    nodeY += nodeY / 2;
			}
			else if (x > nodeX && y > nodeY)
			{
			    _path[i] = QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::BZone;
			    nodeX += nodeX / 2;
			    nodeY += nodeY / 2;
			}
			else if (x < nodeX && y < nodeY)
			{
			    _path[i] = QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::CZone;
			    nodeX -= nodeX / 2;
			    nodeY -= nodeY / 2;
			}
			else
			{
			    _path[i] = QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::DZone;
			    nodeX += nodeX / 2;
			    nodeY -= nodeY / 2;
			}
		    }
		    return std::move(_path);
		}

	public:
	    APhysics(unsigned int x, unsigned int y, bool destructibility, unsigned int type = 0) : _physicallyActive(true), _destructible(destructibility), _isInList(false), _type(type), _quadTree(sCore->getQuadTree()) {
		generateQuadTreePos<1920, 1080, __DQUADTREE_COMPLEXITY__>(x, y);
		_listSection = _quadTree->getDataTreeNode(_path);
	    }

	    virtual ~APhysics() {
		if (_listSection) {
		    _listSection->erase(_whereInList);
		}
	    }

	    inline unsigned int getType() {
		return _type;
	    }

	    inline bool isDestructible() {
		return _destructible;
	    }

	protected:
	    virtual void collisionHandler(APhysics*) = 0;

	    bool preciseDetection(const sf::Sprite& s1, const sf::Sprite& s2) {
		if (s1.getGlobalBounds().intersects(s2.getGlobalBounds())) {
		    return true;
		}
		return false;
	    }


	    void updateQuadTreePos(unsigned int x, unsigned int y) {
		if (_listSection && _isInList) {
		    _listSection->erase(_whereInList);
		    _isInList = false;
		    if (_listSection->empty()) {
			delete _listSection;
			_quadTree->setTreeNode(NULL, _path);
		    }
		}
		generateQuadTreePos<1920, 1080, __DQUADTREE_COMPLEXITY__>(x, y);
		_listSection = _quadTree->getDataTreeNode(_path);
		if (_physicallyActive && _listSection) {
		    for (std::list<APhysics*>::iterator it = _listSection->begin(); it != _listSection->end(); ++it) {
			collisionHandler(*it);
		    }
		}
		if (!_listSection) {
		    _listSection = new std::list<APhysics*>();
		    _quadTree->setTreeNode(_listSection, _path);
		}
		_listSection->push_front(this);
		_whereInList = _listSection->begin();
		_isInList = true;
	    }
    };
}

#endif /* !APHISICS_H_ */
