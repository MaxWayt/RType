#include "APlayer.hh"
#include <iostream>
#include <fstream>
#include <sstream>

#define DEFAULT_CONFIG_FILE "../etc/rtype-client.conf"

class ConfigFile {

    private:
        std::string _file;

        // input variables
        bool _hasKey1;
        bool _hasKey2;
        bool _hasStick;
        bool _hasButton;
        int _key1;
        int _key2;
        int _stick;
        int _button;
        std::string _action;

        // music
        bool _hasMusicPath;
        std::string _musicPath;
        
        // functions
        void parseArguments(DamnCute::APlayer*, std::string&);
        void saveKeys(std::string);
        void saveStick(std::string);
        void saveButton(std::string);

        void saveMusicPath(std::string, size_t);
        
    public:
		ConfigFile(std::string configFile = std::string(DEFAULT_CONFIG_FILE)) : _file(configFile), _key1(0), _key2(0),
			_stick(0), _button(0), _hasMusicPath(false)
		{}
        ~ConfigFile();

        void parseConfigFile(DamnCute::APlayer *);
        bool hasMusicPath();
        std::string getMusicPath();

};
