#ifndef DISPLAYMANAGER_H_
# define DISPLAYMANAGER_H_

# ifndef __DWIDTH
#  define __DWIDTH 1920
#  define __DHEIGHT 1200
# endif

# include <iostream>
# include <SFML/Graphics.hpp>
# include <Core/Core.hh>
#include "Thread.hpp"

enum DisplayMode
{
    MODE_MENU       = 0,
    MODE_GAME       = 1,
};

class Client;

class DisplayManager
{
    public:
        DisplayManager(Client* client, int width = __DWIDTH, int height = __DHEIGHT, bool type = false);
        ~DisplayManager();
        void gameMode();
        void menuMode();

        void Start(DisplayMode mode = MODE_MENU);
        void SwitchMode(DisplayMode mode);
        void run();
    private:
        void init();
        DamnCute::Core* _engine;
        bool _alive;
        DisplayMode _mode;
        bool _init;
        int32 _width;
        int32 _height;
        bool _fullscreen;
        Client* _client;
};

#endif /* !DISPLAYMANAGER_H_ */
