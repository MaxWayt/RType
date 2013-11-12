#include <iostream>
#include <fstream>
#include <sstream>
#include <APlayer.hh>

#define DEFAULT_CONFIG_FILE "../etc/rtype-client.conf"

class ConfigFile {

    private:
        std::string _file;

        // input variables
        bool _hasKey1;
        bool _hasKey2;
        bool _hasStick;
        bool _hasButton;
        int _key1 = 0;
        int _key2 = 0;
        int _stick = 0;
        int _button = 0;
        std::string _action;

        // music
        bool _hasMusicPath = false;
        std::string _musicPath;
        
        // functions
        void parseArguments(DamnCute::APlayer*, std::string&);
        void saveKeys(std::string);
        void saveStick(std::string);
        void saveButton(std::string);

        void saveMusicPath(std::string, size_t);
        
    public:
        ConfigFile(std::string configFile = std::string(DEFAULT_CONFIG_FILE)) : _file(configFile) {}
        ~ConfigFile() = default;

        void parseConfigFile(DamnCute::APlayer *, DamnCute::APlayer *);
        bool hasMusicPath();
        std::string getMusicPath();

};
