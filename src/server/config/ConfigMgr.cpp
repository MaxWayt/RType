/*
 * RType
 *
 */

#include "ConfigMgr.h"
#include "Utils.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

ConfigMgr::ConfigMgr() : _stringConfigs()
{ }

bool ConfigMgr::LoadConfig(bool reload)
{
    std::ifstream file(_configFile);
    if (!file.is_open())
        return false;

    _stringConfigs.clear();

    std::string line;
    while (std::getline(file, line))
    {
        if (line[0] == '#') // Skip comment
            continue;

        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '='))
        {
            std::string value;
            if (std::getline(is_line, value))
            {
                value = trim(value);
                trim_quote(value);
                _stringConfigs[trim(key)] = value;
            }
        }
    }

    file.close();
    return true;
}

void ConfigMgr::DumpConfig()
{
    std::cout << "Config :" << std::endl;
    for (auto itr = _stringConfigs.begin(); itr != _stringConfigs.end(); ++itr)
        std::cout << "\t" << itr->first << " => " << itr->second << std::endl;
}

bool ConfigMgr::GetBoolDefault(std::string const& key, bool def)
{
    auto itr = _stringConfigs.find(key);
    if (itr == _stringConfigs.end())
        return def;

    std::string str = itr->second;
    std::transform(str.begin(), str.end(),str.begin(), ::toupper);
    if (str == "TRUE")
        return true;
    return (bool)to<int>(itr->second);
}

int ConfigMgr::GetIntDefault(std::string const& key, int def)
{
    auto itr = _stringConfigs.find(key);
    if (itr == _stringConfigs.end())
        return def;
    return to<int>(itr->second);
}

std::string const& ConfigMgr::GetStringDefault(std::string const& key, std::string const& def)
{
    auto itr = _stringConfigs.find(key);
    if (itr == _stringConfigs.end())
        return def;
    return itr->second;
}
