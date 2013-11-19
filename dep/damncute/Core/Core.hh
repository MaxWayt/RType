#ifndef CORE_H_
# define CORE_H_

#include <list>
#include <SFML/Audio.hpp>

#include "QuadTree.hh"
#include "../IRenderable.hh"

# ifndef __DWIDTH
#  define __DWIDTH 1920
#  define __DHEIGHT 1080
# endif

#ifndef __DQUADTREE_COMPLEXITY__
#define __DQUADTREE_COMPLEXITY__ 8
#endif

#if __DQUADTREE_COMPLEXITY__ > 10
#warning "you will use more than 300 Mb =O"
#endif

namespace DamnCute {
    class APhysics;
    class Core {
        public:
            Core(const Core&) = delete;
            Core(const Core&&) = delete;
            Core& operator=(const Core&) = delete;
            Core& operator=(const Core&&) = delete;

            static Core* getInstance();
            void reset();
            void freeAll();
            void addObject(IRenderable*);
            void delObject(IRenderable*);
            void addOnBg(IRenderable*);
            void flushScene();
            void flushEvent();
            template <unsigned int SIZEX = __DWIDTH, unsigned int SIZEY = __DHEIGHT>
                void createWin(unsigned int width = 0, unsigned int height = 0, bool full = false) {
                    unsigned int style = full << 3 | sf::Style::Titlebar;
                    sf::VideoMode v;

                    if (full) {
                        v = sf::VideoMode::getFullscreenModes()[0];
                    } else if (width == 0 && height == 0) {
                        v = sf::VideoMode::getDesktopMode();
                    } else {
                        v = sf::VideoMode(width, height);
                    }

                    _win = new sf::RenderWindow(v, "Death Curtain", style);
                    _Rtex.create(SIZEX, SIZEY);
                    _Rtex.setSmooth(true);

                    _rsp.setTexture(_Rtex.getTexture());
                    _rsp.setScale((float)getWindowSizeX() / (float)__DWIDTH , (float)getWindowSizeY() / (float)__DHEIGHT);

                    _win->setVerticalSyncEnabled(true);
                    _win->setFramerateLimit(60);
                }
            int  getWindowStatus();
            int  getWindowSizeX();
            int  getWindowSizeY();

            inline bool getGameStatus() const {
                return _gameStatus;
            }
            inline void switchGameStatus() {
                _gameStatus = !_gameStatus;
            }
            inline sf::Event getEvent() const {
                return event;
            }
            inline void setFPSDisplay(bool value) {
                _displayFPS = value;
            }
            inline void addBulletsCounter() {
                ++_numberOfBullets;
            }
            inline QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__>* getQuadTree() {
                return &_physicTree;
            }
            void menuMusic() {
                _music.setLoop(true);
                if (_music.openFromFile("../resources/music/menu.flac"))
                    _music.play();
            }
            void gameMusic() {
                _music.stop();
                if (_music.openFromFile("../resources/music/game.flac"))
                    _music.play();
            }
        private:

            Core();
            ~Core();
            void refresh();

            static Core* __coreInstance;
            QuadTree<std::list<APhysics*>, __DQUADTREE_COMPLEXITY__> _physicTree;
            sf::RenderWindow* _win;
            sf::RenderTexture _Rtex;
            std::list<IRenderable*> _objects;
            bool _gameStatus;
            bool _displayFPS;
            unsigned int _numberOfBullets;
            unsigned int _Pframmes;
            unsigned int _tmpFrammes;

            sf::Sprite _rsp;
            sf::Clock _gameClock;
            sf::Event event;
            sf::Music _music;
    };
}

#define sCore Core::getInstance()

#endif /* !CORE_H_ */
