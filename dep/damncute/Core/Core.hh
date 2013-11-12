#ifndef CORE_H_
# define CORE_H_

#include <list>
#include <SFML/Audio.hpp>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "QuadTree.hh"
#include "../IRenderable.hh"

#ifndef __DQUADTREE_COMPLEXITY__
#define __DQUADTREE_COMPLEXITY__ 5
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
            template <unsigned int SIZEX = 1920, unsigned int SIZEY = 1080>
                void createWin(unsigned int width = 0, unsigned int height = 0, bool full = false) {
                    unsigned int style = full << 3;

                    if (width == 0 && height == 0) {
                        _win = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Death Curtain", style);
                    } else {
                        //_win = new sf::RenderWindow(sf::VideoMode(SIZEX, SIZEY), "Death Curtain", style);
                        _win = new sf::RenderWindow(sf::VideoMode::getFullscreenModes()[0], "Death Curtain", style);
                    }
                    _Rtex.create(SIZEX, SIZEY);
                    _Rtex.setSmooth(true);
                    _win->setVerticalSyncEnabled(true);
                    _win->setFramerateLimit(60);
                }
            int  getWindowStatus();
            int  getWindowSizeX();
            int  getWindowSizeY();
            sf::Music& getMusic();
            void musicPath(std::string);
            void musicPlay(int);
            int getMusicListSize();

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
            inline QuadTree<APhysics, __DQUADTREE_COMPLEXITY__>* getQuadTree() {
                return &_physicTree;
            }
        private:

            Core();
            ~Core();
            void refresh();

            static Core* __coreInstance;
            QuadTree<APhysics, __DQUADTREE_COMPLEXITY__> _physicTree;
            sf::RenderWindow* _win;
            sf::RenderTexture _Rtex;
            std::list<IRenderable*> _objects;
            bool _gameStatus;
            bool _displayFPS;
            unsigned int _numberOfBullets;
            unsigned int _Pframmes;
            unsigned int _tmpFrammes;

            sf::Clock _gameClock;
            sf::Event event;
            sf::Music _music;
            std::string _musicPath;
            std::vector<std::string> _musicList;

            void saveFolderMusic(std::string);
            bool supportedFileFormat(std::string);
    };
}

#define sCore Core::getInstance()

#endif /* !CORE_H_ */
