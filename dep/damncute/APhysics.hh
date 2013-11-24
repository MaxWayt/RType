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
	    bool _destructor;
	    unsigned int _type;

	    QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>* _quadTree;
	    QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_ _path;

	    std::map<std::list<APhysics*>*, std::list<APhysics*>::iterator> _where;

	    template <unsigned int sizeX, unsigned int sizeY, unsigned short iter>
		inline QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_&& _generateQuadTreePos(unsigned int x, unsigned int y) {
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

	    template <unsigned int sizeX, unsigned int sizeY, unsigned short iter>
		inline std::list<QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_>&& _generateQuadTreePos(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
            std::list<QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>::Array_Type_> list;
            unsigned int quadWidth = sizeX / (2 * __DQUADTREE_COMPLEXITY__);
            unsigned int quadHeight = sizeY / (2 * __DQUADTREE_COMPLEXITY__);

            for (unsigned int i = 0; i < w; i += quadWidth) {
                for (unsigned int j = 0; j < h; j += quadHeight) {
                    list.push_back(_generateQuadTreePos<sizeX, sizeY, __DQUADTREE_COMPLEXITY__>(x + i, y + j));
                }
            }
            return std::move(list);
        }

	public:
	    APhysics(unsigned int x, unsigned int y, bool destructibility, bool destructor, unsigned int type = 0) : _physicallyActive(true), _destructible(destructibility), _destructor(destructor), _type(type), _quadTree(sCore->getQuadTree()) {
		_generateQuadTreePos<1920, 1080, __DQUADTREE_COMPLEXITY__>(x, y);
	    }

	    virtual ~APhysics() {
		for (std::map<std::list<APhysics*>*, std::list<APhysics*>::iterator>::iterator it = _where.begin(); it != _where.end(); ++it) {
		    it->first->erase(it->second);
		}
	    }

	    inline unsigned int getType() {
		return _type;
	    }

	    inline void setType(unsigned int id) {
		_type = id;
	    }

	    inline bool isDestructible() {
		return _destructible;
	    }

	    inline bool isDestructor() {
		return _destructor;
	    }

	protected:
	    virtual void collisionHandler(APhysics*) = 0;

	    bool preciseDetection(const sf::Sprite& s1, const sf::Sprite& s2) {
		if (s1.getGlobalBounds().intersects(s2.getGlobalBounds())) {
		    return true;
		}
		return false;
	    }

	    void updateQuadTreePos(unsigned int x, unsigned int y, unsigned int width = 1, unsigned int height = 1) {
		const unsigned int quadWidth = 1920 / (2 * __DQUADTREE_COMPLEXITY__);
		const unsigned int quadHeight = 1080 / (2 * __DQUADTREE_COMPLEXITY__);

		std::list<APhysics*>* potentialDangerList;
		std::list<APhysics*>::iterator whereInList;

		if (!_physicallyActive)
		    return;
		for (std::map<std::list<APhysics*>*, std::list<APhysics*>::iterator>::iterator it = _where.begin(); it != _where.end(); ++it) {
		    it->first->erase(it->second);
		}
		_where.clear();

		width += quadWidth;
		height += quadHeight;
		for (unsigned int i = 0; i <= width; i += quadWidth) {
		    for (unsigned int j = 0; j <= height; j += quadHeight) {
			_generateQuadTreePos<1920, 1080, __DQUADTREE_COMPLEXITY__>(x + i, y + j);
			potentialDangerList = _quadTree->getDataTreeNode(_path);
			if (_destructible && potentialDangerList) {
			    for (std::list<APhysics*>::iterator potentialDanger = potentialDangerList->begin(); potentialDanger != potentialDangerList->end(); ++potentialDanger) {
				if ((*potentialDanger)->isDestructor()) {
				    collisionHandler(*potentialDanger);
				}
			    }
			}
			if (!potentialDangerList) {
			    potentialDangerList = new std::list<APhysics*>();
			    _quadTree->setTreeNode(potentialDangerList, _path);
			}
			potentialDangerList->push_front(this);
			whereInList = potentialDangerList->begin();
			_where[potentialDangerList] = whereInList;
		    }
		}
	    }
    };
}

#endif /* !APHISICS_H_ */
