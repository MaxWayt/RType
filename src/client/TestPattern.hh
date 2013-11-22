#ifndef TESTPATTERN_H_
# define TESTPATTERN_H_

#include "APattern.hh"

class TestPattern : public DamnCute::APattern {
    public:
        explicit TestPattern();
        virtual ~TestPattern() {}
        virtual void initialize();
};

class pat1 : public DamnCute::APattern {
    public:
        explicit pat1();
        virtual ~pat1() {}
        virtual void initialize();
        void up();
        void labyrinth(int);
        void a_roulette();

    private:
        std::vector<int> labyrinthGroup;
        int _timeframe;

};

class pat2 : public DamnCute::APattern {
    public:
        explicit pat2();
        virtual ~pat2() {}
        virtual void initialize();

};

class CrossingDeath : public DamnCute::APattern {
    public:
        explicit CrossingDeath();
        virtual ~CrossingDeath() {}
        virtual void initialize();
        void generate(int, int, int, int);
};

#endif /* !TESTPATTERN_H_ */
