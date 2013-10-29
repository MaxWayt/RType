/*
 * RType
 *
 */

#include "Singleton.hpp"

#include <map>

#define DEFAULT_CONFIG_FILE "rtype-server.conf"

class ConfigMgr : public Singleton<ConfigMgr>
{
public:
    explicit ConfigMgr();

    void SetConfigFile(std::string const& configFile) { _configFile = configFile; }
    bool LoadConfig(bool reload = false);
    void DumpConfig();

    bool GetBoolDefault(std::string const& key, bool def);
    int GetIntDefault(std::string const& key, int def);
    std::string const& GetStringDefault(std::string const& key, std::string const& def);

private:
    std::string _configFile;
    std::map<std::string, std::string> _stringConfigs;
};

#define sConfig ConfigMgr::instance()
