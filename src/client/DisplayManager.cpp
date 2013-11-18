#include <random>
#include <Background.hh>
#include <Menu.hh>
#include <Core/Core.hh>
#include "DisplayManager.hh"
#include "Player.hh"
#include "ConfigFile.hh"
#include "MonsterHandler.hh"

void runGame();

DisplayManager::DisplayManager(int width, int height, bool fullscreen) : _alive(true) {
    DamnCute::Core::getInstance()->createWin(width, height, fullscreen);
}

DisplayManager::~DisplayManager() {
}

void DisplayManager::update() {
    _alive = DamnCute::Core::getInstance()->getWindowStatus();
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
    _engine->addObject(m);
    m->setTextureButton("../resources/button.jpg");
    m->addButton(1500, 500, "Start game", &runGame);
    m->addButton(1500, 600, "Ziz' in the sky!", []() {});
    m->addButton(1500, 700, "thouropd", []() {});
    m->addButton(1500, 800, "Staline we love you!", []() {});
    m->addSubMenu("Ziz' in the sky!", "Exterminer :", listOption, 1500, 700);
    m->addSubMenu("Ziz' in the sky!", "Manger :", listOption2, 1500, 800);
    m->setTextureCursor("../resources/cursor.png", -80, 0);
}

void DisplayManager::run() {
    _engine = DamnCute::Core::getInstance();

    _engine->menuMusic();
    
    menuMode();
    while (_alive) {
        update();
        _engine->flushScene();
        _engine->flushEvent();
    }
    /*_engine->freeAll();
      _engine->createWin(1920, 1080, false);
      GameMode();
      update();
      while (_alive) {
      update();
      _engine->flushScene();
      _engine->flushEvent();
      }*/
}

bool update() {
    return (DamnCute::Core::getInstance()->getWindowStatus());
}

void gameMode(DamnCute::Core* engine) {

    engine->gameMusic();
    engine->setFPSDisplay(true);
    ConfigFile *config = new ConfigFile(DEFAULT_CONFIG_FILE);
    DamnCute::Background* bg = new DamnCute::Background("../resources/decor009.jpg");
    bg->setScrollSpeed(-0.4, 0);

    DamnCute::APlayer* player_one = new Player<0>("../resources/ship_green.png", 100, 550);
    DamnCute::APlayer* player_two = new Player<1>("../resources/ship_yellow.png", 100, 750);

    MonsterHandler* mh = new MonsterHandler("zizi", 100, 3000, std::make_pair(2000, 2400), std::make_pair(0, 1000));

    config->parseConfigFile(player_one, player_two);

    engine->addOnBg(bg);
    engine->addObject(mh);
    engine->addObject(player_one);
    engine->addObject(player_two);
    engine->switchGameStatus();
}


void runGame()
{
    DamnCute::Core* engine;

    engine = DamnCute::Core::getInstance();
    engine->freeAll();
    //engine->createWin(1440, 900, false);
    gameMode(engine);
    while (update()) {
        engine->flushScene();
        engine->flushEvent();
    }
    //  exit(1);
}
