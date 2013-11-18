#include <random>
#include <Background.hh>
#include <Menu.hh>
#include <Core/Core.hh>
#include "DisplayManager.hh"
#include "Player.hh"
#include "ConfigFile.hh"
#include "MonsterHandler.hh"

#include "Client.h"

void runGame();

DisplayManager::DisplayManager(Client* client, int width, int height, bool fullscreen) : _alive(true), _mode(MODE_MENU), _init(false),
    _width(width), _height(height), _fullscreen(fullscreen), _client(client)
{
}

DisplayManager::~DisplayManager() {
}

void DisplayManager::menuMode() {

    std::vector<std::string> listOption;
    listOption.push_back("les juifs");
    listOption.push_back("les arabes");
    listOption.push_back("les homosexuels");

    std::vector<std::string> listOption2;
    listOption2.push_back("au McDo");
    listOption2.push_back("au MIF");
    listOption2.push_back("au Subway");

    DamnCute::Menu* m = new DamnCute::Menu("../resources/menu.png");
    m->setFontPath("../resources/font.ttf");
    m->setTextureButton("../resources/button.jpg");
    m->addButton(1500, 500, "Start game", std::bind(&DisplayManager::SwitchMode, this, MODE_GAME));
    m->addButton(1500, 600, "Ziz' in the sky!", []() {});
    m->addButton(1500, 700, "thouropd", []() {});
    m->addButton(1500, 800, "Staline we love you!", []() {});
    m->addSubMenu("Ziz' in the sky!", "Exterminer :", listOption, 1500, 700);
    m->addSubMenu("Ziz' in the sky!", "Manger :", listOption2, 1500, 800);
    m->setTextureCursor("../resources/cursor.png", -80, 0);
    _engine->addObject(m);
}

void DisplayManager::gameMode() {

    _engine->gameMusic();
    _engine->setFPSDisplay(true);
    ConfigFile *config = new ConfigFile(DEFAULT_CONFIG_FILE);
    DamnCute::Background* bg = new DamnCute::Background("../resources/decor009.jpg");
    bg->setScrollSpeed(-0.4, 0);

    DamnCute::APlayer* player_one = new Player<0>("../resources/ship_green.png", 100, 550);
    DamnCute::APlayer* player_two = new Player<1>("../resources/ship_yellow.png", 100, 750);

    MonsterHandler* mh = new MonsterHandler("zizi", 100, 3000, std::make_pair(2000, 2400), std::make_pair(0, 1000));

    config->parseConfigFile(player_one, player_two);

    _engine->addOnBg(bg);
    _engine->addObject(mh);
    _engine->addObject(player_one);
    _engine->addObject(player_two);
    _engine->switchGameStatus();
}


void DisplayManager::Start(DisplayMode mode)
{
    _mode = mode;
    run();
}

void DisplayManager::SwitchMode(DisplayMode mode)
{
    _mode = mode;
    _init = false;
}


void DisplayManager::run()
{
    //_engine->menuMusic();
    DamnCute::Core::getInstance()->createWin(_width, _height, _fullscreen);
    _engine = DamnCute::Core::getInstance();

    init();
    while (_alive) {
        if (!_init)
            init();
        _engine->flushScene();
        if (!_init)
            continue;
        _engine->flushEvent();
        _alive = DamnCute::Core::getInstance()->getWindowStatus();
    }
}

void DisplayManager::init()
{
    if (_init)
        return;

    _engine->freeAll();

    switch (_mode)
    {
        case MODE_MENU:
            {
                menuMode();
                break;
            }
        case MODE_GAME:
            {
                gameMode();
                break;
            }
    }
    _init = true;
}
