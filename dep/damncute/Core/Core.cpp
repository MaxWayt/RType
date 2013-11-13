#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Core.hh"

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
        font.loadFromFile("../resources/font.ttf");
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

DamnCute::Core::Core() : _physicTree(), _gameStatus(false), _displayFPS(false) {
}

DamnCute::Core::~Core() {
    freeAll();
    delete _win;
}
