#include <iostream>
//#include "DisplayManager.hh"
#include "Utils.hpp"
#include "Client.h"

int main(int ac, char** av) {
    /*
    DisplayManager* d;

    if (ac > 2) {
        d = new DisplayManager(std::atoi(av[1]), std::atoi(av[2]));
    } else {
        d = new DisplayManager(1920, 1080, false);
    }
    d->run();
    */

    sClient->Initialize(800, 600, false);
    sClient->Launch(ac >= 2 ? to<uint32>(av[1]) : 1, ac >= 3 ? av[2] : "127.0.0.1", ac >= 4 ? av[3] : "5000");
    return EXIT_SUCCESS;
}
