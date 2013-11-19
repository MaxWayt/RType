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

    Client client(800, 600);
    client.Start(ac >= 2 ? to<uint32>(av[1]) : 1);
    client.Wait();
    return EXIT_SUCCESS;
}
