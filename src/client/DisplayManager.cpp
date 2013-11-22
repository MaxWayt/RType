#include "Background.hh"
#include "Menu.hh"
#include "Core/Core.hh"
#include "DisplayManager.hh"
#include "ConfigFile.hh"
#include "Client.h"
#include <random>

void runGame();

DisplayManager::DisplayManager(Client* client, int width, int height, bool fullscreen) : _engine(NULL), _alive(true), _mode(MODE_MENU), _init(false),
    _width(width), _height(height), _fullscreen(fullscreen), _client(client),
    _players()
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

    /*
    DamnCute::APlayer* player_one = new Player<0>("../resources/ship_red.png", 100, 550);
    DamnCute::APlayer* player_two = new Player<1>("../resources/ship_blue.png", 100, 750);

    */
    //MonsterHandler* mh = new MonsterHandler("zizi", 100, 3000, std::make_pair(2000, 2400), std::make_pair(0, 1000));

    //config->parseConfigFile(player_one, player_two);

    _engine->addOnBg(bg);
    //_engine->addObject(mh);
    //_engine->addObject(player_one);
    //_engine->addObject(player_two);
    _engine->switchGameStatus();
}

void DisplayManager::SwitchMode(DisplayMode mode)
{
    _mode = mode;
    _init = false;
}

void DisplayManager::Init()
{
    if (_init)
        return;
    bool created = false;
    if (!_engine)
    {
        _engine = DamnCute::Core::getInstance();
        _engine->createWin<__DWIDTH, __DHEIGHT>(_width, _height, _fullscreen);
        created = true;
    }

    if (!created)
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

void DisplayManager::UpdateFirePosition()
{
    for (auto itr = _players.begin(); itr != _players.end(); ++itr)
        itr->second->UpdateFirePosition();

    for (auto itr = _monsters.begin(); itr != _monsters.end(); ++itr)
        itr->second->UpdateFirePosition();
}

void DisplayManager::AddPlayer(Player* player)
{
    _players[player->getNumPlayer()] = player;
    _engine->addObject(player);
}

void DisplayManager::RemovePlayer(Player* player)
{
    _players.erase(player->getNumPlayer());
    _engine->delObject(player);
}

Player* DisplayManager::GetPlayer(uint32 id)
{
    auto itr = _players.find(id);
    if (itr != _players.end())
        return itr->second;
    return NULL;
}

Player const* DisplayManager::GetPlayer(uint32 id) const
{
    auto itr = _players.find(id);
    if (itr != _players.end())
        return itr->second;
    return NULL;
}


std::string const& DisplayManager::GetFileForClientId(uint32 id)
{
    static std::string file[] = {
        "../resources/ship_red.png",
        "../resources/ship_blue.png",
        "../resources/ship_green.png",
        "../resources/ship_yellow.png"
    };
    return file[id];
}

void DisplayManager::AddMonster(Monster* monster)
{
    _monsters[monster->GetId()] = monster;
    _engine->addObject(monster);
}

void DisplayManager::RemoveMonster(Monster* monster)
{
    _monsters.erase(monster->GetId());
    _engine->delObject(monster);
}

Monster* DisplayManager::GetMonster(uint32 id)
{
    auto itr = _monsters.find(id);
    if (itr != _monsters.end())
        return itr->second;
    return NULL;
}

Monster const* DisplayManager::GetMonster(uint32 id) const
{
    auto itr = _monsters.find(id);
    if (itr != _monsters.end())
        return itr->second;
    return NULL;
}
