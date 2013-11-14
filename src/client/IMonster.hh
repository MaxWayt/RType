#ifndef IMONSTER_H_
# define IMONSTER_H_

# include <APattern.hh> 

class IMonster {

    public:
        IMonster() = default;
        DamnCute::APattern *_pattern;
        void Shoot();

};

#endif
