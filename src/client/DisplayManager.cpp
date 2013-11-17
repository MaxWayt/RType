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

    listOption.push_back("Option 1");
    listOption.push_back("Option 2");
    listOption.push_back("Option 3");
    DamnCute::Menu* m = new DamnCute::Menu("../resources/menu.jpg"); // Instanciation
    m->setFontPath("../resources/font.ttf");
    _engine->addObject(m);
    m->setTextureButton("../resources/button1.png");//Set texture
    m->addButton(50, 100, "start", &runGame); //Pose la texture sur le screen
    m->addButton(50, 400, "Test2", []() {}); //Pose la texture sur le screen
    m->addButton(500, 100, "Test3", []() {}); //Pose la texture sur le screen
    m->addButton(500, 400, "Test4", []() {}); //Pose la texture sur le screen
    m->addSubMenu("Test2", "Sous Menu:", listOption, 50, 50);
    m->addSubMenu("Test2", "Sous Menu2:", listOption, 50, 150);
    m->setTextureCursor("../resources/cursor.png", -50, 100);
}

void DisplayManager::run() {
    _engine = DamnCute::Core::getInstance();

    /*
    sf::Music music;
    music.setLoop(true);
    if (music.openFromFile("../resources/music/01-sound_of_science.flac"))
        music.play();
    */

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

    engine->setFPSDisplay(true);
    ConfigFile *config = new ConfigFile(DEFAULT_CONFIG_FILE);
    DamnCute::Background* bg = new DamnCute::Background("../resources/decor009.jpg");
    bg->setScrollSpeed(-0.4, 0);

    DamnCute::APlayer* player_one = new Player<0>("../resources/ship_blue.png", 100, 550);
    DamnCute::APlayer* player_two = new Player<1>("../resources/player_focus.tga", 100, 650);

    MonsterHandler* mh = new MonsterHandler("zizi", 20, 1000, std::make_pair(2000, 2500), std::make_pair(10, 1000));

    config->parseConfigFile(player_one, player_two);
    
    engine->addOnBg(bg);
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
