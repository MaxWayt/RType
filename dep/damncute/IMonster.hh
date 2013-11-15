#ifndef IMONSTER_H_
# define IMONSTER_H_

# include "APattern.hh"

namespace DamnCute {
    class IMonster : public IRenderable {

        public:
            DamnCute::APattern *_pattern;
            virtual void shoot() = 0;

    };
}

#endif
