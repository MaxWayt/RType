#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Core.hh"
#include "../src/macBundle.hh"

namespace DamnCute {
    Core* Core::__coreInstance = NULL;
}

DamnCute::Core* DamnCute::Core::getInstance() {
    if (!__coreInstance) {
        __coreInstance = new DamnCute::Core;
    }
    return __coreInstance;
}

void DamnCute::Core::freeAll() {
    for (std::list<IRenderable*>::iterator it = _objects.begin() ; it != _objects.end(); ++it) {
        delete (*it);
    }
    _objects.clear();
}

void DamnCute::Core::reset() {
    delete __coreInstance;
    __coreInstance = NULL;
}

void DamnCute::Core::refresh() {
    for (std::list<IRenderable*>::iterator it = _objects.begin() ; it != _objects.end(); ++it) {
        (*it)->update(&_Rtex);
    }
}

void DamnCute::Core::flushEvent() {
    while (_win->pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::F12)
                _win->close();
    }
}

void DamnCute::Core::flushScene() {
    _numberOfBullets = 0;
    sf::Font font;
    sf::Text t;
    _win->clear();
    _Rtex.clear();
    refresh();

    if (_displayFPS) {
        std::stringstream ss;
        ss << _tmpFrammes;
        ss << " fps for ";
        ss << _numberOfBullets;
        ss << " bullets";
<<<<<<< HEAD
        macBundlePath g;
        font.loadFromFile(g.getPath() + "resources/font.ttf");
=======
        font.loadFromFile("../resources/font.ttf");
>>>>>>> 0d7123179e88bdce7d090df6d0fb4f0569170587
        t = sf::Text(ss.str(), font);
        t.setCharacterSize(24);
        t.setColor(sf::Color::Green);
        t.setPosition(900, 10);
        _Rtex.draw(t);
    }
    if (_gameClock.getElapsedTime().asSeconds() >= 1) {
        _gameClock.restart();
        _tmpFrammes = _Pframmes;
        _Pframmes = 0;
    }
    ++_Pframmes;

    _Rtex.display();
    sf::Sprite Rsp(_Rtex.getTexture());
    _win->draw(Rsp);
    _win->display();
}

void DamnCute::Core::addObject(IRenderable* a) {
    _objects.push_back(a);
}
void DamnCute::Core::addOnBg(IRenderable* a) {
    _objects.push_front(a);
}

void DamnCute::Core::delObject(IRenderable* a) {
    for (std::list<IRenderable*>::iterator it = _objects.begin() ; it != _objects.end(); ++it) {
        if ((*it) == a) {
            _objects.erase(it);
            delete a;
            return;
        }
    }
}

int  DamnCute::Core::getWindowStatus() {
    return _win->isOpen();
}

int  DamnCute::Core::getWindowSizeX() {
    return _win->getSize().x;
}

int  DamnCute::Core::getWindowSizeY() {
    return _win->getSize().y;
}

sf::Music& DamnCute::Core::getMusic() {
    return _music;
}

bool DamnCute::Core::supportedFileFormat(std::string file) {
    if ( (file.find(".ogg") != std::string::npos) || (file.find(".wav") != std::string::npos) ||
            (file.find(".flac") != std::string::npos) || (file.find(".aiff") != std::string::npos) )
        return true;
    return false;
}

void DamnCute::Core::saveFolderMusic(std::string path) {

    DIR *dp;
    struct stat statbuf;

    if ((dp = opendir(path.c_str())) == NULL)
        std::cerr << "cannot open directory" << std::endl;
    dirent *de;
    if (dp) {
        while ((de = readdir(dp))) {
            std::string file = std::string(de->d_name);
            if (file != "." && file != "..") {
                stat((path + "/" + file).c_str(), &statbuf);
                if (S_ISDIR(statbuf.st_mode))
                    saveFolderMusic((path + "/" + file));
                else if (supportedFileFormat(file)) {
                    std::cout << path + "/" + file << std::endl;
                    _musicList.push_back(path + "/" + file);
                }
            }
        }
        closedir(dp);
    }
}

void DamnCute::Core::musicPath(std::string path) {

    _musicList.clear();
    saveFolderMusic(path);
    _musicPath = path + "/";
}

int DamnCute::Core::getMusicListSize() {
    return _musicList.size();
}

void DamnCute::Core::musicPlay(int index) {
    if (_music.openFromFile(_musicList[index]))
        _music.play();
}

DamnCute::Core::Core() : _physicTree(), _gameStatus(false), _displayFPS(false), _musicPath("./") {
}

DamnCute::Core::~Core() {
    freeAll();
    delete _win;
}
