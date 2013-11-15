#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IMonster.hh"

class MonsterEngine : public IMonster {

    private:
        int _row;
        int _col;
        glm::mat4 _mov;

    public:
        MonsterEngine(int, int, glm::mat4);
        ~MonsterEngine() = default;

};
