#ifndef DISPLAYMANAGER_H_
# define DISPLAYMANAGER_H_

# ifndef __DWIDTH
#  define __DWIDTH 1920
#  define __DHEIGHT 1200
# endif

# include <SFML/Graphics.hpp>
# include "Core/Core.hh"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Player.hh"
#include "Monster.h"
# include <iostream>

enum DisplayMode
{
    MODE_MENU       = 0,
    MODE_GAME       = 1,
};

class Client;

class EndGame : public DamnCute::IRenderable {

    private:
        sf::Text _text;
        sf::Font _font;

    public:
        EndGame(bool status) {
            _font.loadFromFile("../resources/font.ttf");
            _text.setFont(_font);
            _text.setString((status == 1 ? "Win" : "Loose"));
            _text.setCharacterSize(800);
            _text.move(150, 0);
        }
        virtual void update(sf::RenderTarget *r) {
            r->draw(_text);
        } 
        ~EndGame() {}

};

class DisplayManager
{
    public:
        DisplayManager(Client* client, int width = __DWIDTH, int height = __DHEIGHT, bool type = false);
        ~DisplayManager();
        void gameMode();
        void menuMode();

        void Start(DisplayMode mode = MODE_MENU);
        void SwitchMode(DisplayMode mode);
        bool IsAlive() const { return _alive; }
        inline void flushAll() { _engine->flushScene(); _engine->flushEvent(); }
        inline void UpdateAlive() { _alive = (bool)DamnCute::Core::getInstance()->getWindowStatus(); }
        void Init();

        void AddPlayer(Player* player);
        void RemovePlayer(Player* player);
        Player* GetPlayer(uint32 id);
        Player const* GetPlayer(uint32 id) const;

        void AddMonster(Monster* monster);
        void RemoveMonster(Monster* monster);
        Monster* GetMonster(uint32 id);
        Monster const* GetMonster(uint32 id) const;

        static std::string const& GetFileForClientId(uint32 id);

        void showWinLoose(bool);

        void UpdateFirePosition();

    private:
        DamnCute::Core* _engine;
        bool _alive;
        DisplayMode _mode;
        bool _init;
        int32 _width;
        int32 _height;
        bool _fullscreen;
        Client* _client;
        std::map<uint32, Player*> _players;
        std::map<uint32, Monster*> _monsters;
};

#endif /* !DISPLAYMANAGER_H_ */
