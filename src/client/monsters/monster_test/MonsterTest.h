#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

#include <iostream>
#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Monster.h"
#include "APhysics.hh"

class MonsterTest : public Monster
{
    public:
        MonsterTest(int x, int y);

        void update(sf::RenderTarget* w_ptr);
};

#endif /* !MONSTERTEST_H_ */
